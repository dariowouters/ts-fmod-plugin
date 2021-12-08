// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include "sdk_stores.h"
#include "telemetry_data.h"
#include "memory_structure.h"
#include "memory.h"

fmod_manager* fmod_manager_instance = nullptr;

telemetry_data_t telemetry_data;

scs_log_t scs_log;

uintptr_t economy_base_offset = NULL;
uintptr_t game_base = NULL;
DWORD image_size = 0;

uint32_t stored_engine_state = 0;
byte indicator_stick_state = false;
bool was_indicator_light_on = false;
bool was_park_brake_on = false;
uint32_t prev_retarder_level = 0;
bool high_beams_enabled = false;
bool wipers_enabled = false;
float hazard_warning_state = 0.0f;
float light_horn_state = 0.0f;
float light_stick_state = 0.0f;
float wipers_stick_state = 0.0f;

scs_telemetry_register_for_channel_t register_for_channel = nullptr;
scs_telemetry_unregister_from_channel_t unregister_from_channel = nullptr;
#define register_channel(name, index, type, field) register_for_channel(SCS_TELEMETRY_##name, index, SCS_VALUE_TYPE_##type, SCS_TELEMETRY_CHANNEL_FLAG_no_value, telemetry_store_##type, &telemetry_data.field);

SCSAPI_VOID telemetry_pause(const scs_event_t event, const void* const event_info, scs_context_t context)
{
    fmod_manager_instance->set_paused(event == SCS_TELEMETRY_EVENT_paused);
}

bool should_engine_brake_sound_play()
{
    return telemetry_data.engine_brake && telemetry_data.effective_throttle < 0.05f && telemetry_data.gear != 0 && telemetry_data.effective_clutch < 0.05f;
}

SCSAPI_VOID telemetry_tick(const scs_event_t event, const void* const event_info, scs_context_t context)
{
    fmod_manager_instance->set_event_parameter("engine/engine", "rpm", telemetry_data.rpm);
    fmod_manager_instance->set_event_parameter("engine/exhaust", "rpm", telemetry_data.rpm);
    fmod_manager_instance->set_event_parameter("engine/engine", "load", telemetry_data.effective_throttle); // The game might use some other value, but this seems close enough
    fmod_manager_instance->set_event_parameter("engine/exhaust", "load", telemetry_data.effective_throttle);

    if (reinterpret_cast<economy_base_t*>(economy_base_offset) != nullptr && economy_base_offset != NULL)
    {
        auto* const economy_base = reinterpret_cast<economy_base_t*>(economy_base_offset);

        auto* const some_truck_telem_parent = economy_base->get_truck_telem_parent();
        if (some_truck_telem_parent != nullptr)
        {
            auto* const truck_telem_data = some_truck_telem_parent->get_truck_telem_data();
            if (truck_telem_data != nullptr)
            {
                const auto turbo_pressure = truck_telem_data->get_turbo_pressure();
                if (turbo_pressure >= 0 && turbo_pressure <= 1)
                {
                    fmod_manager_instance->set_event_parameter("engine/turbo", "turbo", turbo_pressure);
                }

                const auto engine_state = truck_telem_data->get_engine_state();
                if (engine_state != stored_engine_state) // engine state changed TODO: Find start_bad
                {
                    if (engine_state > 0 && stored_engine_state == 0) { // engine is starting/running
                        fmod_manager_instance->set_event_parameter("engine/engine", "play", 1);
                        fmod_manager_instance->set_event_parameter("engine/exhaust", "play", 1);
                        fmod_manager_instance->set_event_state("engine/engine", true);
                        fmod_manager_instance->set_event_state("engine/exhaust", true);

                        fmod_manager_instance->set_event_parameter("engine/turbo", "play", 1);
                        fmod_manager_instance->set_event_state("engine/turbo", true);
                    }
                    else if (engine_state == 0 || engine_state == 3) // engine is no longer running
                    {
                        fmod_manager_instance->set_event_parameter("engine/engine", "play", 0);
                        fmod_manager_instance->set_event_parameter("engine/exhaust", "play", 0);
                        fmod_manager_instance->set_event_parameter("engine/turbo", "play", 0);
                    }
                    stored_engine_state = engine_state;
                }

                fmod_manager_instance->set_event_parameter("engine/engine", "brake", should_engine_brake_sound_play() ? truck_telem_data->get_engine_brake_state() : 0.0f);

                const auto hazard_warning = truck_telem_data->get_hazard_warning_state();
                if (!common::cmpf(hazard_warning, hazard_warning_state))
                {
                    fmod_manager_instance->set_event_state("interior/stick_hazard_warning", true);
                    hazard_warning_state = hazard_warning;
                }

                const auto light_horn = truck_telem_data->get_light_horn_state();
                if (!common::cmpf(light_horn, light_horn_state))
                {
                    fmod_manager_instance->set_event_state("interior/stick_light_horn", true);
                    light_horn_state = light_horn;
                }

                const auto stick_lights = truck_telem_data->get_light_switch_state();
                if (!common::cmpf(stick_lights, light_stick_state))
                {
                    fmod_manager_instance->set_event_state("interior/stick_lights", true);
                    light_stick_state = stick_lights;
                }

                const auto wipers_stick = truck_telem_data->get_wipers_state();
                if (!common::cmpf(wipers_stick, wipers_stick_state))
                {
                    fmod_manager_instance->set_event_state("interior/stick_wipers", true);
                    wipers_stick_state = wipers_stick;
                }
            }
        }

        auto* const unk_interior_parent = economy_base->get_unk_interior_parent();
        if (unk_interior_parent != nullptr)
        {
            const auto window_pos = unk_interior_parent->get_window_state();
            if (window_pos.x >= 0 && window_pos.x <= 1) fmod_manager_instance->set_global_parameter("wnd_left", window_pos.x);
            if (window_pos.y >= 0 && window_pos.y <= 1) fmod_manager_instance->set_global_parameter("wnd_right", window_pos.y);
            if (common::cmpf(window_pos.x, 0) && common::cmpf(window_pos.y, 0) && unk_interior_parent->get_is_camera_inside())
            {
                fmod_manager_instance->set_bus_volume("outside", fmod_manager_instance->sound_levels.windows_closed);
                fmod_manager_instance->set_bus_volume("exterior", fmod_manager_instance->sound_levels.windows_closed); // backward compatibility
            }
            else
            {
                fmod_manager_instance->set_bus_volume("outside", 1);
                fmod_manager_instance->set_bus_volume("exterior", 1); // backward compatibility
            }

            if (unk_interior_parent->get_is_on_interior_cam())
            {
                fmod_manager_instance->set_bus_volume("cabin/interior", fmod_manager_instance->sound_levels.interior);
            }
            else
            {
                fmod_manager_instance->set_bus_volume("cabin/interior", 0);
            }

            auto* const unk_cabin = unk_interior_parent->get_unk_cabin();
            if (unk_cabin != nullptr)
            {
                fmod_manager_instance->set_global_parameter("cabin_out", unk_cabin->get_cabin_out());
            }

            fmod_manager_instance->set_global_parameter("cabin_rot", unk_interior_parent->get_camera_rotation_in_cabin());
            fmod_manager_instance->set_global_parameter("surr_type", unk_interior_parent->get_has_echo());
        }
    }

#pragma region interior
    if (telemetry_data.brake_air_pressure_warning && telemetry_data.engine_enabled)
    {
        fmod_manager_instance->set_event_state("interior/air_warning", true, true);
    }

    if ((telemetry_data.light_lblinker || telemetry_data.light_rblinker) && !was_indicator_light_on)
    {
        fmod_manager_instance->set_event_state("interior/blinker_on", true);
        was_indicator_light_on = true;
    }
    else if (!telemetry_data.light_lblinker && !telemetry_data.light_rblinker && was_indicator_light_on)
    {
        fmod_manager_instance->set_event_state("interior/blinker_off", true);
        was_indicator_light_on = false;
    }

    if (telemetry_data.park_brake_on != was_park_brake_on)
    {
        if (was_park_brake_on) fmod_manager_instance->set_event_state("interior/stick_park_brake_off", true);
        else fmod_manager_instance->set_event_state("interior/stick_park_brake", true);
        was_park_brake_on = telemetry_data.park_brake_on;
    }

    const byte current_blinker_stick = telemetry_data.lblinker ? 1 : telemetry_data.rblinker ? 2 : 0; // 1 if lblinker, 2 if rblinker, 0 if off
    if (current_blinker_stick != indicator_stick_state && current_blinker_stick != 0)
    {
        fmod_manager_instance->set_event_state("interior/stick_blinker", true);
        indicator_stick_state = current_blinker_stick;
    }
    else if (current_blinker_stick == 0 && indicator_stick_state != 0)
    {
        fmod_manager_instance->set_event_state("interior/stick_blinker_off", true);
        indicator_stick_state = 0;
    }

    if (telemetry_data.retarder_level != prev_retarder_level)
    {
        fmod_manager_instance->set_event_state("interior/stick_retarder", true);
        prev_retarder_level = telemetry_data.retarder_level;
    }

    if (telemetry_data.high_beam != high_beams_enabled)
    {
        fmod_manager_instance->set_event_state("interior/stick_high_beam", true);
        high_beams_enabled = telemetry_data.high_beam;
    }
#pragma endregion
    fmod_manager_instance->update();
}

void register_telem_channels()
{
    register_channel(TRUCK_CHANNEL_engine_rpm, SCS_U32_NIL, float, rpm)
    register_channel(TRUCK_CHANNEL_effective_throttle, SCS_U32_NIL, float, effective_throttle)
    register_channel(TRUCK_CHANNEL_effective_clutch, SCS_U32_NIL, float, effective_clutch)
    register_channel(TRUCK_CHANNEL_motor_brake, SCS_U32_NIL, bool, engine_brake)
    register_channel(TRUCK_CHANNEL_brake_air_pressure_warning, SCS_U32_NIL, bool, brake_air_pressure_warning)
    register_channel(TRUCK_CHANNEL_engine_enabled, SCS_U32_NIL, bool, engine_enabled)
    register_channel(TRUCK_CHANNEL_lblinker, SCS_U32_NIL, bool, lblinker)
    register_channel(TRUCK_CHANNEL_rblinker, SCS_U32_NIL, bool, rblinker)
    register_channel(TRUCK_CHANNEL_light_lblinker, SCS_U32_NIL, bool, light_lblinker)
    register_channel(TRUCK_CHANNEL_light_rblinker, SCS_U32_NIL, bool, light_rblinker)
    register_channel(TRUCK_CHANNEL_head_offset, SCS_U32_NIL, fplacement, head_offset)
    register_channel(TRUCK_CHANNEL_parking_brake, SCS_U32_NIL, bool, park_brake_on)
    register_channel(TRUCK_CHANNEL_retarder_level, SCS_U32_NIL, u32, retarder_level)
    register_channel(TRUCK_CHANNEL_light_high_beam, SCS_U32_NIL, bool, high_beam)
    register_channel(TRUCK_CHANNEL_wipers, SCS_U32_NIL, bool, wipers)
    register_channel(TRUCK_CHANNEL_engine_gear, SCS_U32_NIL, s32, gear)
}

SCSAPI_RESULT scs_telemetry_init(const scs_u32_t version, const scs_telemetry_init_params_t* const params)
{
    const auto* const version_params = reinterpret_cast<const scs_telemetry_init_params_v101_t*>(params);

    scs_log = version_params->common.log;

    scs_log(0, "[ts-fmod-plugin V1.41] Searching for economy offset... If this is one of the last messages in the log after a crash, try disabling this plugin.");

    auto addr = pattern::scan("48 8B 05 ? ? ? ? 48 8B D9 8B 90 ? ? ? ? 48 8B 80 ? ? ? ? 48 8B 88 ? ? ? ? E8", game_base, image_size);
    economy_base_offset = addr + *reinterpret_cast<uint32_t*>(addr + 3) + 7 - 0x48;

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

    fmod_manager_instance = new fmod_manager(scs_log);

    if (!fmod_manager_instance->init())
    {
        scs_log(SCS_LOG_TYPE_error, "[ts-fmod-plugin] Could not init fmod");
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
    if (fmod_manager_instance != nullptr)
    {
        delete fmod_manager_instance;
        fmod_manager_instance = nullptr;
    }
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
        const auto* const header = reinterpret_cast<const IMAGE_DOS_HEADER*>(game_base);
        const auto* const nt_header = reinterpret_cast<const IMAGE_NT_HEADERS64*>(reinterpret_cast<const uint8_t*>(header) + header->e_lfanew);
        image_size = nt_header->OptionalHeader.SizeOfImage;
    }
    return TRUE;
}

