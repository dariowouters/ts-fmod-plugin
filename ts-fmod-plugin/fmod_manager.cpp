#include "pch.h"
#include "fmod_manager.h"

namespace fs = std::filesystem;

fmod_manager::fmod_manager(const scs_log_t scs_log) : scs_log_(scs_log)
{

}

fmod_manager::~fmod_manager()
{
    system_->release();
    CoUninitialize();
}

bool fmod_manager::load_selected_bank(const std::string& plugin_files_dir)
{
    const auto selected_bank_file_path = plugin_files_dir + "selected.bank.txt";

    if (!fs::exists(selected_bank_file_path))
    {
        scs_log_(SCS_LOG_TYPE_error, "[ts-fmod-plugin] Could not find the 'selected.bank.txt' file");
        return false;
    }

    std::ifstream selected_bank_file(selected_bank_file_path);
    std::string bank_name;
    if (!selected_bank_file.is_open())
    {
        scs_log_(SCS_LOG_TYPE_error, "[ts-fmod-plugin] Could not read the 'selected.bank.txt' file");
        return false;
    }

    while (selected_bank_file >> bank_name)
    {
        selected_bank_name_ = bank_name;
    }

    const auto res = system_->loadBankFile((plugin_files_dir + selected_bank_name_ + ".bank").c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &sound_bank_);
    if (res != FMOD_OK)
    {
        scs_log_(SCS_LOG_TYPE_error, (std::string("[ts-fmod-plugin] Could not load the bank file in 'selected.bank.txt' file, ") + FMOD_ErrorString(res)).c_str());
        return false;
    }

    return true;
}

bool fmod_manager::init()
{
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

    auto plugin_files_dir = fs::current_path().generic_u8string() + "/plugins/ts-fmod-plugin/";
    auto res = FMOD::Studio::System::create(&system_);
    if (res != FMOD_OK)
    {
        scs_log_(SCS_LOG_TYPE_error, (std::string("[ts-fmod-plugin] Could not create FMOD system, ") + FMOD_ErrorString(res)).c_str());
        return false;
    }
    res = system_->initialize(64, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr);
    if (res != FMOD_OK)
    {
        scs_log_(SCS_LOG_TYPE_error, (std::string("[ts-fmod-plugin] Could not initialize FMOD, ") + FMOD_ErrorString(res)).c_str());
        return false;
    }

    FMOD::Studio::Bank* bank;
    system_->loadBankFile((plugin_files_dir + "master.bank").c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank);

    if (!load_selected_bank(plugin_files_dir))
    {
        return false;
    }

    if (!init_channels(plugin_files_dir))
    {
        return false;
    }

    load_sound_levels(plugin_files_dir);

    set_bus_volume("", sound_levels.master);
    set_bus_volume("outside/exterior/truck_engine", sound_levels.engine);
    set_bus_volume("outside/exterior/truck_exhaust", sound_levels.exhaust);
    set_bus_volume("outside/exterior/truck_turbo", sound_levels.turbo);
    set_bus_volume("cabin/interior", sound_levels.interior);

    set_bus_volume("outside", sound_levels.windows_closed);
    set_bus_volume("exterior", sound_levels.windows_closed); // backward compatibility for 1.37 sound mods

    return true;
}

bool fmod_manager::init_channels(const std::string& plugin_files_dir)
{
    auto guids_file_path = plugin_files_dir + selected_bank_name_ + ".bank.guids";
    if (!fs::exists(guids_file_path))
    {
        scs_log_(SCS_LOG_TYPE_error, "[ts-fmod-plugin] Could not find the '*.bank.guids' file");
        return false;
    }

    std::ifstream guids_file(guids_file_path);
    std::string s_guid, channel_path;
    if (!guids_file.is_open())
    {
        scs_log_(SCS_LOG_TYPE_error, "[ts-fmod-plugin] Could not read the '*.bank.guids' file");
        return false;
    }

    while (guids_file >> s_guid >> channel_path)
    {
        if (channel_path.find("event:/") != std::string::npos)
        {
            auto event = fmod_event(system_, s_guid);
            if (event.create_event_instance() != FMOD_OK)
            {
                std::stringstream ss;
                ss << "[ts-fmod-plugin] Could not load event '" + channel_path + "'";
                scs_log_(SCS_LOG_TYPE_error, ss.str().c_str());
            }
            add_event(channel_path.substr(7, channel_path.size() - 7).c_str(), event);
        }
        else if (channel_path.find("bus:/") != std::string::npos)
        {
            auto guid = common::get_guid(s_guid);
            FMOD::Studio::Bus* bus;
            system_->getBusByID(&guid, &bus);
            add_bus(channel_path.substr(5, channel_path.size() - 5).c_str(), bus);
        }
    }
    guids_file.close();

    return true;
}

float fmod_manager::get_sound_level_from_json(json j, const char* key, float defaultValue = 1.0f)
{

    std::stringstream ss;

    float val = defaultValue;
    if (j.contains(key) && j[key].is_number())
    {
        val = j[key].get<float>();
        if (val < 0.0f)
        {
            ss << "[ts-fmod-plugin] Invalid value for sound level '" << key << "', value should be more than 0. Defaulting to " << defaultValue;
            scs_log_(SCS_LOG_TYPE_error, ss.str().c_str());
            val = defaultValue;
        }
    }
    else
    {
        ss.clear();
        ss << "[ts-fmod-plugin] Could not read sound level '" << key << "', defaulting to " << defaultValue;
        scs_log_(SCS_LOG_TYPE_error, ss.str().c_str());
    }

    return val / 2;
}

bool fmod_manager::load_sound_levels(const std::string& plugin_files_dir)
{
    const auto sound_levels_file_path = plugin_files_dir + "sound_levels.txt";

    if (!fs::exists(sound_levels_file_path))
    {
        scs_log_(SCS_LOG_TYPE_error, "[ts-fmod-plugin] Could not find the 'sound_levels.txt' file");
        return false;
    }

    std::ifstream sound_levels_file(sound_levels_file_path);
    std::string line;

    if (!sound_levels_file.is_open())
    {
        scs_log_(SCS_LOG_TYPE_error, "[ts-fmod-plugin] Could not read the 'sound_levels.txt' file");
        return false;
    }

    json j;

    try {
        sound_levels_file >> j;
    }
    catch (json::parse_error& e)
    {
        scs_log_(SCS_LOG_TYPE_error, "[ts-fmod-plugin] Could not parse JSON from 'sound_levels.txt' ");
        return false;
    }


    sound_levels.master = get_sound_level_from_json(j, "master");
    sound_levels.engine = get_sound_level_from_json(j, "engine");
    sound_levels.exhaust = get_sound_level_from_json(j, "exhaust");
    sound_levels.turbo = get_sound_level_from_json(j, "turbo");
    sound_levels.interior = get_sound_level_from_json(j, "interior");
    sound_levels.windows_closed = get_sound_level_from_json(j, "exterior_when_windows_closed", 0.7f);

    return true;
}

void fmod_manager::set_paused(const bool state)
{
    pause_bus("", state); // pause/unpause the main bus ('bus:/')
}

FMOD::Studio::Bus* fmod_manager::get_bus(const char* name)
{
    const auto res = fmod_busses_map_.find(name);
    if (res == fmod_busses_map_.end())
    {
        return nullptr;
    }
    return res->second;
}

std::unique_ptr<fmod_event> fmod_manager::get_event(const char* name)
{
    auto res = fmod_events_map_.find(name);
    if (res == fmod_events_map_.end())
    {
        return nullptr;
    }
    return std::make_unique<fmod_event>(res->second);
}

void fmod_manager::add_event(const char* name, fmod_event event)
{
    fmod_events_map_.insert(std::make_pair(name, event));
}

void fmod_manager::add_bus(const char* name, FMOD::Studio::Bus* bus)
{
    fmod_busses_map_.insert(std::make_pair(name, bus));
}

FMOD_RESULT fmod_manager::update() const
{
    return system_->update();
}

FMOD_RESULT fmod_manager::set_global_parameter(const char* param_name, const float value) const
{
    return system_->setParameterByName(param_name, value);
}

FMOD_RESULT fmod_manager::set_event_parameter(const char* event_name, const char* param_name, const float value)
{
    const auto event = get_event(event_name);
    if (event == nullptr) return FMOD_ERR_EVENT_NOTFOUND;

    return event->set_parameter_by_name(param_name, value);
}

FMOD_RESULT fmod_manager::set_event_state(const char* event_name, const bool state, const bool only_when_event_stopped)
{
    const auto event = get_event(event_name);
    if (event == nullptr) return FMOD_ERR_EVENT_NOTFOUND;

    FMOD_STUDIO_PLAYBACK_STATE playback_state;
    event->get_playback_state(&playback_state);
    if (playback_state != FMOD_STUDIO_PLAYBACK_STOPPED && only_when_event_stopped) return FMOD_ERR_EVENT_ALREADY_LOADED;

    return state ? event->start() : event->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
}

FMOD_RESULT fmod_manager::set_bus_volume(const char* bus_name, const float value)
{
    auto* const bus = get_bus(bus_name);
    if (bus == nullptr) return FMOD_ERR_EVENT_NOTFOUND;

    return bus->setVolume(value);
}

FMOD_RESULT fmod_manager::pause_bus(const char* bus_name, const bool state)
{
    auto* const bus = get_bus(bus_name);
    if (bus == nullptr) return FMOD_ERR_EVENT_NOTFOUND;

    return bus->setPaused(state);
}