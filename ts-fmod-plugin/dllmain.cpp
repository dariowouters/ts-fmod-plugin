// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include "sdk_stores.h"
#include "telemetry_data.h"
#include "memory_structure.h"
#include "memory.h"

namespace fs = std::filesystem;

std::string sound_mod_name = "";

telemetry_data_t telemetry_data;

scs_log_t scs_log;
FMOD::Studio::System* fmod_system = NULL;
FMOD::Studio::Bank* sound_bank = nullptr;

fmod_event_manager* event_manager = nullptr;

uintptr_t economy_base_offset = NULL;
uintptr_t game_base = NULL;
DWORD image_size = 0;

uint32_t stored_engine_state = 0;
bool was_indicator_on = false;
bool was_indicator_light_on = false;
bool was_park_brake_on = false;
uint32_t prev_retarder_level = 0;

scs_telemetry_register_for_channel_t register_for_channel = nullptr;
scs_telemetry_unregister_from_channel_t unregister_from_channel = nullptr;
#define register_channel(name, index, type, field) register_for_channel(SCS_TELEMETRY_##name, index, SCS_VALUE_TYPE_##type, SCS_TELEMETRY_CHANNEL_FLAG_no_value, telemetry_store_##type, &telemetry_data.field);

SCSAPI_VOID telemetry_pause(const scs_event_t event, const void* const event_info, scs_context_t context)
{
    event_manager->set_paused(event == SCS_TELEMETRY_EVENT_paused);
}

SCSAPI_VOID telemetry_tick(const scs_event_t event, const void* const event_info, scs_context_t context)
{
    auto engine_fmod_event = event_manager->get_event("engine/engine");
    auto exhaust_fmod_event = event_manager->get_event("engine/exhaust");

    engine_fmod_event->set_parameter_by_name("rpm", telemetry_data.rpm);
    exhaust_fmod_event->set_parameter_by_name("rpm", telemetry_data.rpm);
    engine_fmod_event->set_parameter_by_name("load", telemetry_data.effective_throttle); // The game might use some other value, but this seems close enough
    exhaust_fmod_event->set_parameter_by_name("load", telemetry_data.effective_throttle);
    engine_fmod_event->set_parameter_by_name("brake", telemetry_data.engine_brake ? 1.0f : 0.0f);

    if (reinterpret_cast<economy_base_t*>(economy_base_offset) != nullptr && economy_base_offset != NULL)
    {
        const auto economy_base = reinterpret_cast<economy_base_t*>(economy_base_offset);
        const auto unk = economy_base->get_unk();
        if (unk != nullptr)
        {
            const auto some_arr = unk->get_some_arr_ptr();
            if (some_arr != nullptr)
            {
                const auto some_truck_telem_parent = some_arr->get_some_truck_telem_data_parent();
                if (some_truck_telem_parent != nullptr)
                {
                    const auto truck_telem_data = some_truck_telem_parent->get_some_truck_telem_data();
                    if (truck_telem_data != nullptr)
                    {
                        const auto turbo_pressure = truck_telem_data->get_turbo_pressure();
                        if (turbo_pressure >= 0 && turbo_pressure <= 1) engine_fmod_event->set_parameter_by_name("turbo", turbo_pressure);

                        const auto engine_state = truck_telem_data->get_engine_state();
                        if (engine_state != stored_engine_state) // engine state changed
                        {
                            if (engine_state > 0 && stored_engine_state == 0) { // engine is starting/running
                                engine_fmod_event->set_parameter_by_name("play", 1);
                                exhaust_fmod_event->set_parameter_by_name("play", 1);
                                engine_fmod_event->start();
                                exhaust_fmod_event->start();
                            }
                            else if (engine_state == 0 || engine_state == 3) // engine is no longer running
                            {
                                engine_fmod_event->set_parameter_by_name("play", 0);
                                exhaust_fmod_event->set_parameter_by_name("play", 0);
                            }
                            stored_engine_state = engine_state;
                        }
                    }
                }
            }
        }

        const auto unk_window_parent = economy_base->get_unk_window_parent();
        if (unk_window_parent != nullptr)
        {
            auto window_pos = unk_window_parent->get_window_state();
            if (window_pos.x >= 0 && window_pos.x <= 1) fmod_system->setParameterByName("wnd_left", window_pos.x);
            if (window_pos.y >= 0 && window_pos.y <= 1) fmod_system->setParameterByName("wnd_right", window_pos.y);
            if (window_pos.x == 0 && window_pos.y == 0) { // not sure what to to with this (sound levels when windows close(d)) yet / maybe fade audio the more it closes/opens
                engine_fmod_event->set_volume(0.15f);
                exhaust_fmod_event->set_volume(0.15f);
            }
            else {
                engine_fmod_event->set_volume(0.3f);
                exhaust_fmod_event->set_volume(0.3f);
            }

            fmod_system->setParameterByName("surr_type", unk_window_parent->get_has_echo());
        }
    }

#pragma region interior
    auto air_warning_fmod_event = event_manager->get_event("interior/air_warning");
    auto stick_park_brake_off_event = event_manager->get_event("interior/stick_park_brake_off");
    auto stick_park_brake_event = event_manager->get_event("interior/stick_park_brake");

    if (air_warning_fmod_event != nullptr && telemetry_data.brake_air_pressure_warning && telemetry_data.engine_enabled)
    {
        FMOD_STUDIO_PLAYBACK_STATE state;
        air_warning_fmod_event->get_playback_state(&state);
        if (state == FMOD_STUDIO_PLAYBACK_STOPPED) air_warning_fmod_event->start();
    }

    if ((telemetry_data.light_lblinker || telemetry_data.light_rblinker) && !was_indicator_light_on)
    {
        auto blinker_on_event = event_manager->get_event("interior/blinker_on");
        if (blinker_on_event != nullptr) blinker_on_event->start();
        was_indicator_light_on = true;
    }
    else if (!telemetry_data.light_lblinker && !telemetry_data.light_rblinker && was_indicator_light_on)
    {
        auto blinker_off_event = event_manager->get_event("interior/blinker_off");
        if (blinker_off_event != nullptr) blinker_off_event->start();
        was_indicator_light_on = false;
    }

    if (stick_park_brake_off_event != nullptr && stick_park_brake_event != nullptr && telemetry_data.park_brake_on != was_park_brake_on)
    {
        was_park_brake_on = telemetry_data.park_brake_on;
        if (was_park_brake_on) stick_park_brake_off_event->start();
        else stick_park_brake_event->start();
    }

    if ((telemetry_data.lblinker || telemetry_data.rblinker) && !was_indicator_on)
    {
        auto stick_blinker_event = event_manager->get_event("interior/stick_blinker");
        if (stick_blinker_event != nullptr) stick_blinker_event->start();
        was_indicator_on = true;
    }
    else if (!telemetry_data.lblinker && !telemetry_data.rblinker && was_indicator_on)
    {
        auto stick_blinker_off_event = event_manager->get_event("interior/stick_blinker_off");
        if (stick_blinker_off_event != nullptr) stick_blinker_off_event->start();
        was_indicator_on = false;
    }

    if (telemetry_data.retarder_level != prev_retarder_level)
    {
        auto stick_retarder_event = event_manager->get_event("interior/stick_retarder");
        if (stick_retarder_event != nullptr) stick_retarder_event->start();
        prev_retarder_level = telemetry_data.retarder_level;
    }
#pragma endregion
    fmod_system->update();
}

bool init_fmod_events(std::string main_bank_dir)
{
    auto guids_file_path = main_bank_dir + sound_mod_name + ".bank.guids";
    if (!fs::exists(guids_file_path))
    {
        scs_log(SCS_LOG_TYPE_error, "[ts-fmod-plugin] Could not find the '*.bank.guids' file");
        return false;
    }

    std::ifstream guids_file(guids_file_path);
    std::string guid, event_path;
    if (!guids_file.is_open())
    {
        scs_log(SCS_LOG_TYPE_error, "[ts-fmod-plugin] Could not read the '*.bank.guids' file");
        return false;
    }

    while (guids_file >> guid >> event_path)
    {
        if (event_path.find("event:/") != std::string::npos) {
            auto event = fmod_event(fmod_system, guid);
            if (event.create_event_instance() != FMOD_OK) {
                std::stringstream ss;
                ss << "[ts-fmod-plugin] Could not load event'" + event_path + "'";
                scs_log(SCS_LOG_TYPE_error, ss.str().c_str());
            }
            event_manager->add_event(event_path.substr(7, event_path.size() - 7), event);
        }
    }
    guids_file.close();

    return true;
}

bool init_fmod()
{
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    event_manager = new fmod_event_manager();

    auto main_bank_dir = fs::current_path().generic_u8string() + "/plugins/ts-fmod-plugin/";
    auto res = FMOD::Studio::System::create(&fmod_system);
    if (res != FMOD_OK)
    {
        scs_log(SCS_LOG_TYPE_error, (std::string("[ts-fmod-plugin] Could not create FMOD system, ") + FMOD_ErrorString(res)).c_str());
        return false;
    }
    res = fmod_system->initialize(64, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL);
    if (res != FMOD_OK)
    {
        scs_log(SCS_LOG_TYPE_error, (std::string("[ts-fmod-plugin] Could not initialize FMOD, ") + FMOD_ErrorString(res)).c_str());
        return false;
    }

    FMOD::Studio::Bank* bank;
    fmod_system->loadBankFile((main_bank_dir + "master.bank").c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank);

    auto selected_bank_file_path = main_bank_dir + "selected.bank.txt";

    if (!fs::exists(selected_bank_file_path))
    {
        scs_log(SCS_LOG_TYPE_error, "[ts-fmod-plugin] Could not find the 'selected.bank.txt' file");
        return false;
    }

    std::ifstream selected_bank_file(selected_bank_file_path);
    std::string bank_name;
    if (!selected_bank_file.is_open())
    {
        scs_log(SCS_LOG_TYPE_error, "[ts-fmod-plugin] Could not read the 'selected.bank.txt' file");
        return false;
    }

    while (selected_bank_file >> bank_name)
    {
        sound_mod_name = bank_name;
    }

    res = fmod_system->loadBankFile((main_bank_dir + sound_mod_name + ".bank").c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &sound_bank);
    if (res != FMOD_OK)
    {
        scs_log(SCS_LOG_TYPE_error, (std::string("[ts-fmod-plugin] Could not load the bank file in 'selected.bank.txt' file, ") + FMOD_ErrorString(res)).c_str());
        return false;
    }

    if (!init_fmod_events(main_bank_dir))
    {
        return false;
    }
    event_manager->get_event("engine/engine")->set_volume(0.3f);
    event_manager->get_event("engine/exhaust")->set_volume(0.3f);

    return true;
}

void register_telem_channels()
{
    register_channel(TRUCK_CHANNEL_engine_rpm, SCS_U32_NIL, float, rpm);
    register_channel(TRUCK_CHANNEL_effective_throttle, SCS_U32_NIL, float, effective_throttle);
    register_channel(TRUCK_CHANNEL_motor_brake, SCS_U32_NIL, bool, engine_brake);
    register_channel(TRUCK_CHANNEL_brake_air_pressure_warning, SCS_U32_NIL, bool, brake_air_pressure_warning);
    register_channel(TRUCK_CHANNEL_engine_enabled, SCS_U32_NIL, bool, engine_enabled);
    register_channel(TRUCK_CHANNEL_lblinker, SCS_U32_NIL, bool, lblinker);
    register_channel(TRUCK_CHANNEL_rblinker, SCS_U32_NIL, bool, rblinker);
    register_channel(TRUCK_CHANNEL_light_lblinker, SCS_U32_NIL, bool, light_lblinker);
    register_channel(TRUCK_CHANNEL_light_rblinker, SCS_U32_NIL, bool, light_rblinker);
    register_channel(TRUCK_CHANNEL_head_offset, SCS_U32_NIL, fplacement, head_offset);
    register_channel(TRUCK_CHANNEL_parking_brake, SCS_U32_NIL, bool, park_brake_on);
    register_channel(TRUCK_CHANNEL_retarder_level, SCS_U32_NIL, u32, retarder_level);
}

SCSAPI_RESULT scs_telemetry_init(const scs_u32_t version, const scs_telemetry_init_params_t* const params)
{
    const auto version_params = reinterpret_cast<const scs_telemetry_init_params_v101_t*>(params);

    scs_log = version_params->common.log;

    scs_log(0, "[ts-fmod-plugin] Searching for economy offset... If this is the last message in the log after a crash, try disabling this plugin.");

    auto addr = pattern::scan("48 8B 05 ? ? ? ? 48 8B D9 8B 90 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B 88 ? ? ? ? E8", game_base, image_size);
    economy_base_offset = addr + *reinterpret_cast<uint32_t*>(addr + 3) + 7;

    std::stringstream ss;
    ss << "[ts-fmod-plugin] Found economy offset &" << std::hex << (economy_base_offset - game_base);
    scs_log(0, ss.str().c_str());

    const auto events_registered =
        (version_params->register_for_event(SCS_TELEMETRY_EVENT_paused, telemetry_pause, nullptr) == SCS_RESULT_ok) &&
        (version_params->register_for_event(SCS_TELEMETRY_EVENT_started, telemetry_pause, nullptr) == SCS_RESULT_ok) &&
        (version_params->register_for_event(SCS_TELEMETRY_EVENT_frame_end, telemetry_tick, nullptr) == SCS_RESULT_ok);

    if (!events_registered)
    {
        version_params->common.log(SCS_LOG_TYPE_error, "[ts-fmod-plugin] Unable to register event callbacks");
        return SCS_RESULT_generic_error;
    }
    register_for_channel = version_params->register_for_channel;

    if (!init_fmod())
    {
        scs_log(SCS_LOG_TYPE_error, "[ts-fmod-plugin] Could not load plugin");
        return SCS_RESULT_generic_error;
    }

    if (economy_base_offset == NULL)
    {
        version_params->common.log(SCS_LOG_TYPE_error, "[ts-fmod-plugin] Unable to find economy base");
        return SCS_RESULT_generic_error;
    }

    register_telem_channels();

    scs_log(0, "[ts-fmod-plugin] Plugin loaded");

    return SCS_RESULT_ok;
}

void shutdown()
{
    if (event_manager != nullptr) delete event_manager;
    fmod_system->release();
    CoUninitialize();
}

SCSAPI_VOID scs_telemetry_shutdown(void)
{
    shutdown();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        game_base = reinterpret_cast<uintptr_t>(GetModuleHandleA(NULL));
        const auto header = reinterpret_cast<const IMAGE_DOS_HEADER*>(game_base);
        const auto nt_header = reinterpret_cast<const IMAGE_NT_HEADERS64*>(reinterpret_cast<const uint8_t*>(header) + header->e_lfanew);
        image_size = nt_header->OptionalHeader.SizeOfImage;
    }
    return TRUE;
}

