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

bool fmod_manager::load_selected_bank(const std::filesystem::path& plugin_files_dir)
{
    auto selected_bank_file_path = plugin_files_dir;
    selected_bank_file_path.append("selected.bank.txt");

    if (!exists(selected_bank_file_path))
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

    FMOD::Studio::Bank* bank;
    int i = 0;
    while (selected_bank_file >> bank_name)
    {
        auto bank_file_path = plugin_files_dir;
        bank_file_path.append(bank_name).concat(".bank");

        const auto res = system_->loadBankFile(
            bank_file_path.generic_u8string().c_str(),
            FMOD_STUDIO_LOAD_BANK_NORMAL,
            &bank);
        if (res != FMOD_OK)
        {
            std::stringstream ss;
            ss << "[ts-fmod-plugin] Could not load the bank file '" << bank_name << "' in 'selected.bank.txt' file, " <<
                FMOD_ErrorString(res);
            scs_log_(SCS_LOG_TYPE_error, ss.str().c_str());
            return false;
        }
        selected_bank_names_.push_back(bank_name);
        std::stringstream ss;
        ss << "[ts-fmod-plugin] Using sound bank[" << i++ << "]: '" << bank_name << "'";
        scs_log_(SCS_LOG_TYPE_message, ss.str().c_str());
    }
    return true;
}

bool fmod_manager::init()
{
    const auto co_init_res = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

    if (co_init_res != S_OK && co_init_res != S_FALSE)
    {
        scs_log_(SCS_LOG_TYPE_error, "[ts-fmod-plugin] CoInitializeEx Failed");
        return false;
    }
    const auto plugin_files_dir = fs::current_path().append("plugins/ts-fmod-plugin");
    auto res = FMOD::Studio::System::create(&system_);
    if (res != FMOD_OK)
    {
        scs_log_(SCS_LOG_TYPE_error,
                 (std::string("[ts-fmod-plugin] Could not create FMOD system, ") + FMOD_ErrorString(res)).c_str());
        return false;
    }
    res = system_->initialize(64, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr);
    if (res != FMOD_OK)
    {
        scs_log_(SCS_LOG_TYPE_error,
                 (std::string("[ts-fmod-plugin] Could not initialize FMOD, ") + FMOD_ErrorString(res)).c_str());
        return false;
    }
    res = system_->getCoreSystem(&core_system_);
    if (res != FMOD_OK)
    {
        scs_log_(SCS_LOG_TYPE_error,
                 (std::string("[ts-fmod-plugin] Could not load FMOD core system, ") + FMOD_ErrorString(res)).c_str());
        return false;
    }
    int driver_count;
    core_system_->getNumDrivers(&driver_count);
    if (res != FMOD_OK)
    {
        scs_log_(SCS_LOG_TYPE_error,
                 (std::string("[ts-fmod-plugin] Could not get FMOD driver count, ") + FMOD_ErrorString(res)).c_str());
        return false;
    }

    for (int i = 0; i < driver_count; ++i)
    {
        char device_name[256];
        res = core_system_->getDriverInfo(i, device_name, 256, nullptr, nullptr, nullptr, nullptr);
        if (res != FMOD_OK)
        {
            scs_log_(SCS_LOG_TYPE_error,
                     (std::string("[ts-fmod-plugin] Could not get FMOD driver[") + std::to_string(i) + "] " +
                         FMOD_ErrorString(res)).c_str());
            if (i == 0) return false; // Only fail if not able to get the default device
        }
        scs_log_(SCS_LOG_TYPE_message,
                 (std::string("[ts-fmod-plugin] Found output device[") + std::to_string(i) + "] " + device_name).
                 c_str());
    }
    scs_log_(SCS_LOG_TYPE_message, std::string("[ts-fmod-plugin] Selecting default output device (0)").c_str());

    FMOD::Studio::Bank* bank;

    auto master_bank_path = plugin_files_dir;
    master_bank_path.append("master.bank");

    res = system_->loadBankFile(master_bank_path.generic_u8string().c_str(),
                                FMOD_STUDIO_LOAD_BANK_NORMAL,
                                &bank);

    if (res != FMOD_OK)
    {
        std::stringstream ss;
        ss << "[ts-fmod-plugin] Could not load the bank file 'master.bank', " <<
            FMOD_ErrorString(res);
        scs_log_(SCS_LOG_TYPE_error, ss.str().c_str());
        return false;
    }

    if (!load_selected_bank(plugin_files_dir))
    {
        return false;
    }

    if (!init_channels(plugin_files_dir))
    {
        return false;
    }

    if (fmod_events_map_.find("engine/engine") == fmod_events_map_.end())
    {
        scs_log_(SCS_LOG_TYPE_warning,
                 "Did not find an 'event:/engine/engine' event. You will not have engine sounds.");
    }
    if (fmod_events_map_.find("engine/exhaust") == fmod_events_map_.end())
    {
        scs_log_(SCS_LOG_TYPE_warning,
                 "Did not find an 'event:/engine/exhaust' event. You will not have exhaust sounds.");
    }
    if (fmod_events_map_.find("engine/turbo") == fmod_events_map_.end())
    {
        scs_log_(SCS_LOG_TYPE_warning,
                 "Did not find an 'event:/engine/turbo' event. You will not have turbo sounds.");
    }

    //check navigation vocies was loaded 
    {
        std::stringstream navi_event_error_ss;
        size_t navigation_event_error_count = 0;

        const size_t navigation_events_count = 38;
        const char* navigation_events[]{
            "and_then_exit_left",
            "and_then_exit_right",
            "and_then_go_straight",
            "and_then_keep_left",
            "and_then_keep_right",
            "and_then_turn_left",
            "and_then_turn_right",
            "compound_exit_left",
            "compound_exit_right",
            "compound_go_straight",
            "compound_keep_left",
            "compound_keep_right",
            "compound_turn_left",
            "compound_turn_right",
            "exit_left",
            "exit_now",
            "exit_right",
            "finish",
            "go_straight",
            "keep_left",
            "keep_right",
            "prepare_exit_left",
            "prepare_exit_right",
            "prepare_turn_left",
            "prepare_turn_right",
            "recomputing",
            "roundabout_1",
            "roundabout_2",
            "roundabout_3",
            "roundabout_4",
            "roundabout_5",
            "roundabout_6",
            "speed_signal",
            "speed_warning",
            "start",
            "turn_left",
            "turn_right",
            "u_turn" };

        for (int i = 0; i < navigation_events_count; i++)
        {
            if (fmod_events_map_.find(navigation_events[i]) == fmod_events_map_.end())
            {
                navi_event_error_ss << navigation_events[i] << ",";
                navigation_event_error_count++;
            }
        }
        auto log = navi_event_error_ss.str();

        if (navigation_event_error_count == navigation_events_count)
        {
            scs_log_(SCS_LOG_TYPE_warning,
                "Did not find any navigation event. You will not have navigation voices.");
        } else if (log.length() > 1)
        {
            log = log.erase(log.length() - 1);
            std::string err = "Did not find an navigation event. You will not have ( " + log + " ) vocies. ";
            scs_log_(SCS_LOG_TYPE_warning,
                err.c_str());
        }
    }

    load_sound_levels(plugin_files_dir);

    set_bus_volume("", sound_levels.master);
    set_bus_volume("outside/exterior/truck_engine", sound_levels.engine);
    set_bus_volume("outside/exterior/truck_exhaust", sound_levels.exhaust);
    set_bus_volume("outside/exterior/truck_turbo", sound_levels.turbo);
    set_bus_volume("cabin/interior", sound_levels.interior);

    set_bus_volume("outside", sound_levels.windows_closed);
    set_bus_volume("exterior", sound_levels.windows_closed); // backward compatibility for 1.37 sound mods
    set_bus_volume("game/navigation", sound_levels.navigation);

    return true;
}

bool fmod_manager::init_channels(const std::filesystem::path& plugin_files_dir)
{
    for (const std::string& bank_name : selected_bank_names_)
    {
        std::stringstream ss;
        ss << "[ts-fmod-plugin] Loading the events and busses for '" << bank_name << "'";
        scs_log_(SCS_LOG_TYPE_message, ss.str().c_str());

        auto guids_file_path = plugin_files_dir;
        guids_file_path.append(bank_name).concat(".bank.guids");

        if (!exists(guids_file_path))
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
                const auto channel_name = channel_path.substr(7, channel_path.size() - 7);
                if (fmod_events_map_.count(channel_name))
                {
                    std::stringstream ss;
                    ss << "[ts-fmod-plugin] The event '" << channel_name << "' is already loaded.";
                    scs_log_(SCS_LOG_TYPE_warning, ss.str().c_str());
                    continue;
                }

                auto event = fmod_event(system_, s_guid);
                if (event.create_event_instance() != FMOD_OK)
                {
                    std::stringstream ss;
                    ss << "[ts-fmod-plugin] Could not load event '" << channel_name << "'";
                    scs_log_(SCS_LOG_TYPE_error, ss.str().c_str());
                    continue;
                }
                std::stringstream ss;
                ss << "[ts-fmod-plugin] Loading event '" << channel_name << "'";
                scs_log_(SCS_LOG_TYPE_message, ss.str().c_str());
                add_event(channel_name.c_str(), event);
            }
            else if (channel_path.find("bus:/") != std::string::npos)
            {
                const auto bus_name = channel_path.substr(5, channel_path.size() - 5);
                if (fmod_busses_map_.count(bus_name))
                {
                    continue;
                }

                auto guid = common::get_guid(s_guid);
                FMOD::Studio::Bus* bus;
                system_->getBusByID(&guid, &bus);
                add_bus(bus_name.c_str(), bus);
            }
        }
        guids_file.close();
    }
    return true;
}

float fmod_manager::get_sound_level_from_json(json j, const char* key, float default_value = 1.0f)
{
    float val = default_value;
    if (j.contains(key) && j[key].is_number())
    {
        val = j[key].get<float>();
        if (val < 0.0f)
        {
            std::stringstream ss;
            ss << "[ts-fmod-plugin] Invalid value for sound level '" << key <<
                "', value should be more than 0. Defaulting to " << default_value;
            scs_log_(SCS_LOG_TYPE_error, ss.str().c_str());
            val = default_value;
        }
    }
    else
    {
        std::stringstream ss;
        ss << "[ts-fmod-plugin] Could not read sound level '" << key << "', defaulting to " << default_value;
        scs_log_(SCS_LOG_TYPE_error, ss.str().c_str());
    }
    std::stringstream ss;
    ss << "[ts-fmod-plugin] Setting sound level for '" << key << "' to " << val;
    scs_log_(SCS_LOG_TYPE_message, ss.str().c_str());

    return val / 2;
}

bool fmod_manager::load_sound_levels(std::filesystem::path plugin_files_dir)
{
    const auto sound_levels_file_path = plugin_files_dir.append("sound_levels.txt");

    if (!exists(sound_levels_file_path))
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

    try
    {
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
    sound_levels.navigation = get_sound_level_from_json(j, "navigation", 0.5f);



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
