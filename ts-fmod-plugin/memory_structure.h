#pragma once

#include "prism/collections/array_dyn.h"
#include "prism/collections/list_dyn.h"
#include "prism/collections/array_local.h"
#include "prism/string.h"

using namespace ts_fmod_plugin::prism;

#pragma pack( push, 1 )

struct vec2s_t // Size: 0x0008
{
public:
    float x; // 0x0000 (0x04)
    float y; // 0x0004 (0x04)
};

struct vec3s_t // Size: 0x000C
{
public:
    float x; // 0x0000 (0x04)
    float y; // 0x0004 (0x04)
    float z; // 0x0008 (0x04)
};

struct token_t // Size: 0x0008
{
    uint64_t token; // 0x0000 (0x08)
};

class unit_t // Size: 0x0010
{
public:
    void* vtable;   // 0x0000 (0x08)
    uint32_t unk;   // 0x0008 (0x04)
    uint32_t unk_2; // 0x000C (0x04)
};

static_assert(sizeof(unit_t) == 0x10);

class game_actor_u : public unit_t // Size: 0x21E8
{
public:
    char pad_0010[ 8 ]; // 0x0010 (0x08)
    class game_physics_vehicle_u* game_physics_vehicle; // 0x0018 (0x08)
    class visual_interior_u* visual_interior; // 0x0020 (0x08)
    class game_actor_hud_u* game_actor_hud; // 0x0028 (0x08)
    char pad_0030[ 24 ]; // 0x0030 (0x18)
    bool stored_show_weigh; // 0x0048 (0x01)
    bool stored_need_to_weigh; // 0x0049 (0x01)
    char pad_004A[ 86 ]; // 0x004A (0x56)
    class history_stream_set_u* history_stream_set; // 0x00A0 (0x08)
    char pad_00A8[ 16 ]; // 0x00A8 (0x10)
    class history_manager_u* history_manager; // 0x00B8 (0x08)
    class game_trailer_actor_u* game_trailer_actor; // 0x00C0 (0x08)
    char pad_00C8[ 88 ]; // 0x00C8 (0x58)
    uint32_t current_camera; // 0x0120 (0x04) 2 = int, 1 = chase, 7 = top, 5 = roof, 4 = side_back, 3 = hood, 6 = side_front, 9 = cinematic, 0 = dev
    char pad_0124[ 8 ]; // 0x0124 (0x08)
    uint32_t engine_state; // 0x012C (0x04) 0 = engine off, 1 = starting, 2 = running, 3 = shutting down
    bool ignition; // 0x0130 (0x01)
    char pad_0131[ 7 ]; // 0x0131 (0x07)
    uint8_t parking_brake; // 0x0138 (0x01)
    char pad_0139[ 9 ]; // 0x0139 (0x09)
    bool engine_brake_enabled; // 0x0142 (0x01)
    char pad_0143[ 5 ]; // 0x0143 (0x05)
    float N00002AFA; // 0x0148 (0x04)
    char pad_014C[ 16 ]; // 0x014C (0x10)
    uint32_t retarder_i_level; // 0x015C (0x04)
    float retarder_f_level; // 0x0160 (0x04)
    char pad_0164[ 4 ]; // 0x0164 (0x04)
    bool diff_locked; // 0x0168 (0x01)
    char pad_0169[ 12 ]; // 0x0169 (0x0c)
    bool cruise_control_enabled; // 0x0175 (0x01)
    char pad_0176[ 2 ]; // 0x0176 (0x02)
    float cruise_control_speed; // 0x0178 (0x04)
    float road_speed_limit; // 0x017C (0x04)
    char pad_0180[ 24 ]; // 0x0180 (0x18)
    uint32_t wiper_setting; // 0x0198 (0x04)
    char pad_019C[ 24 ]; // 0x019C (0x18)
    uint16_t flags; // 0x01B4 (0x02) 6 = parking lights, 8 = low beam, 7 = high beam, 5 = beacons, 0 = truck axle lifted, 1 = trailer axle lifted
    char pad_01B6[ 2 ]; // 0x01B6 (0x02)
    uint16_t additional_illumination; // 0x01B8 (0x02) (flags) 3 = front, 4 = roof
    char pad_01BA[ 14 ]; // 0x01BA (0x0e)
    float wipers_intermittent_time; // 0x01C8 (0x04) Countdown before wipers move again when in intermittent setting
    float wipers_position; // 0x01CC (0x04) 0 = down start, 1 = down end ???
    float rpm; // 0x01D0 (0x04)
    float air_pressure; // 0x01D4 (0x04)
    float brake_pressure; // 0x01D8 (0x04)
    float max_air_pressure; // 0x01DC (0x04)
    char pad_01E0[ 8 ]; // 0x01E0 (0x08)
    float oil_temp; // 0x01E8 (0x04)
    char pad_01EC[ 4 ]; // 0x01EC (0x04)
    float water_temp; // 0x01F0 (0x04)
    char pad_01F4[ 4 ]; // 0x01F4 (0x04)
    float battery_voltage; // 0x01F8 (0x04)
    char pad_01FC[ 8 ]; // 0x01FC (0x08)
    float turbo_pressure; // 0x0204 (0x04) ?
    char pad_0208[ 16 ]; // 0x0208 (0x10)
    float light_switch; // 0x0218 (0x04) 0 = off, 0.5 = parking, 1 = low beam
    float light_switch_state; // 0x021C (0x04) 0 = off, 0.5 = parking, 1 = low beam (instant)
    float high_beam_stick; // 0x0220 (0x04) 0 = off, 1 = on
    float high_beam_state; // 0x0224 (0x04) 0 = off, 1 = on (instant)
    float light_horn_stick; // 0x0228 (0x04) 0 = off, 1 = on
    float light_horn_state; // 0x022C (0x04) 0 = off, 1 = on (instant)
    float indicator_stick; // 0x0230 (0x04) 0 = left indicator, 0.5 = none, 1 = right
    float indicator_state; // 0x0234 (0x04) 0 = left indicator, 0.5 = none, 1 = right (instant)
    float hazard_warning_btn; // 0x0238 (0x04) 0 = off, 1 = on
    float hazard_warning_state; // 0x023C (0x04) 0 = off, 1 = on (instant)
    float beacon_switch; // 0x0240 (0x04) 0 = off, 1 = on
    float beacon_state; // 0x0244 (0x04) 0 = off, 1 = on (instant)
    char pad_0248[ 8 ]; // 0x0248 (0x08)
    float handbrake_handle; // 0x0250 (0x04) 0 = off, 1 = on
    float handbrake_state; // 0x0254 (0x04) 0 = off, 1 = on (instant)
    char pad_0258[ 16 ]; // 0x0258 (0x10)
    float engine_brake_stick; // 0x0268 (0x04) 0 = off, 1 = full; steps dependant on engine data
    float engine_brake_state; // 0x026C (0x04) 0 = off, 1 = full (instant); steps dependant on engine data
    char pad_0270[ 20 ]; // 0x0270 (0x14)
    float wipers_stick; // 0x0284 (0x04) 0 = off, 0.333 = intermittent, 0.666 = slow, 1 = fast
    float wipers_state; // 0x0288 (0x04) 0 = off, 0.333 = intermittent, 0.666 = slow, 1 = fast (instant)
    char pad_028C[ 20 ]; // 0x028C (0x14)
    uint8_t left_window_moving_direction; // 0x02A0 (0x01) 1 = got to end down; 2 = got to end up; 16 = down; 32 = up
    uint8_t is_left_window_moving; // 0x02A1 (0x01) 1 = down auto; 16 = down holding btn; 2 = auto up; 32 = up holding button
    char pad_02A2[ 2 ]; // 0x02A2 (0x02)
    float left_window_state; // 0x02A4 (0x04) 0 = up; 1 = down
    float left_window_btn; // 0x02A8 (0x04) 0 = up; 0.5 off; 1 = down
    float left_window_btn_state; // 0x02AC (0x04) 0 = up; 0.5 off; 1 = down (instant)
    float N00002B28; // 0x02B0 (0x04)
    char pad_02B4[ 4 ]; // 0x02B4 (0x04)
    uint8_t right_window_moving_direction; // 0x02B8 (0x01) 1 = got to end down; 2 = got to end up; 16 = down; 32 = up
    uint8_t is_right_window_moving; // 0x02B9 (0x01) 1 = down auto; 16 = down holding btn; 2 = auto up; 32 = up holding button
    char pad_02BA[ 2 ]; // 0x02BA (0x02)
    float right_window_state; // 0x02BC (0x04) 0 = up; 1 = down
    float right_window_btn; // 0x02C0 (0x04) 0 = up; 0.5 off; 1 = down
    float right_window_btn_state; // 0x02C4 (0x04) 0 = up; 0.5 off; 1 = down (instant)
    char pad_02C8[ 1880 ]; // 0x02C8 (0x758)
    class game_actor_sounds_t* sound_events; // 0x0A20 (0x08)
    char pad_0A28[ 60 ]; // 0x0A28 (0x3c)
    float throttle_input; // 0x0A64 (0x04)
    float brake_input; // 0x0A68 (0x04)
    float clutch_input; // 0x0A6C (0x04)
    char pad_0A70[ 64 ]; // 0x0A70 (0x40)
    class model_object_u* driver_model; // 0x0AB0 (0x08)
    char pad_0AB8[ 16 ]; // 0x0AB8 (0x10)
    class physics_gearbox_sequential_u* physics_gearbox_sequential; // 0x0AC8 (0x08)
    class physics_gearbox_automatic_u* physics_gearbox_automatic; // 0x0AD0 (0x08)
    class physics_gearbox_direct_u* physics_gearbox_direct; // 0x0AD8 (0x08)
    char pad_0AE0[ 8 ]; // 0x0AE0 (0x08)
    class accessory_head_lights_data_u* accessory_head_lights_data; // 0x0AE8 (0x08)
    char pad_0AF0[ 1232 ]; // 0x0AF0 (0x4d0)
    token_t N00002CB4; // 0x0FC0 (0x08)
    char pad_0FC8[ 4640 ]; // 0x0FC8 (0x1220)


public:
    float get_light_switch_state() const
    {
        return light_switch_state;
    }

    float get_light_horn_state() const
    {
        return light_horn_state;
    }

    float get_hazard_warning_state() const
    {
        return hazard_warning_state;
    }

    float get_wipers_state() const
    {
        return wipers_state;
    }

    float get_turbo_pressure() const
    {
        return turbo_pressure;
    }

    uint32_t get_engine_state() const
    {
        return engine_state;
    }

    float get_wiper_position() const
    {
        return wipers_position;
    }

    float get_engine_brake_state() const
    {
        return engine_brake_state;
    }
};
static_assert( sizeof( game_actor_u ) == 0x21E8 );

// Size: 0x0010
class sound_event_t
{
public:
    class fmod_event_t* fmod_sound_event; // 0x0008 (0x08)

    virtual void destructor();
};
static_assert(sizeof(sound_event_t) == 0x10);

class voice_navigation_sound_t
{
    uint32_t pad_0000;   // 0x0000 (0x04)
    uint32_t pad_0004;   // 0x0004 (0x04)
    char* event_name;    // 0x0008 (0x08)
    uint32_t pad_0010;   // 0x0010 (0x04)
    uint32_t pad_0014;   // 0x0014 (0x04)
    sound_event_t event; // 0x0018 (0x10)

public:

    const char* get_event_name() const
    {
        return event_name;
    }
};

namespace sound
{
    // Size: 0x0008
    class sound_owner_t
    {
    public:
        virtual void destructor();
    };
    static_assert( sizeof( sound_owner_t ) == 0x8 );

    // Size: 0x0008
    class sound_base_t : public /* [0x08] @ 0x00 */ sound_owner_t
    {
    public:
    };
    static_assert( sizeof( sound_base_t ) == 0x8 );

    // Size: 0x0010
    class sound_stream_t : public /* [0x08] @ 0x00 */ sound_base_t
    {
    public:
        class fmod_stream_t* stream; // 0x0008 (0x08)
    };
    static_assert( sizeof( sound_stream_t ) == 0x10 );
}

// Size: 0x1F60
class sound_library_t
{
public:
    char pad_0008[ 8 ]; // 0x0008 (0x08)
    array_local_t< class sound_event_t*, 28ul > ui_sound_events; // 0x0010 (0x100)
    char pad_0110[ 12 ]; // 0x0110 (0x0c)
    uint32_t state; // 0x011C (0x04) 1 = on; 2 = off
    bool interior_camera; // 0x0120 (0x01)
    bool is_camera_inside; // 0x0121 (0x01)
    char pad_0122[ 2 ]; // 0x0122 (0x02)
    float camera_rotation_in_cabin; // 0x0124 (0x04)
    float cabin_out; // 0x0128 (0x04)
    char pad_012C[ 4 ]; // 0x012C (0x04)
    class fmod_parameter_t* cabin_type_param; // 0x0130 (0x08)
    class fmod_parameter_t* cabin_rot_param; // 0x0138 (0x08)
    class fmod_parameter_t* cabin_out_param; // 0x0140 (0x08)
    vec2s_t window_state; // 0x0148 (0x08)
    class fmod_parameter_t* wnd_left_param; // 0x0150 (0x08)
    class fmod_parameter_t* wnd_right_param; // 0x0158 (0x08)
    float daytime; // 0x0160 (0x04)
    char pad_0164[ 4 ]; // 0x0164 (0x04)
    class fmod_parameter_t* daytime_param; // 0x0168 (0x08)
    char pad_0170[ 48 ]; // 0x0170 (0x30)
    array_local_t< voice_navigation_sound_t, 38ul > navigation_sounds; // 0x01A0 (0x610)
    string_dyn_t current_navigation_bank_path; // 0x07B0 (0x18)
    voice_navigation_sound_t* now_playing_navigation_sound; // 0x07C8 (0x08)
    list_dyn_t< class voice_navigation_sound_t* > N0000433C; // 0x07D0 (0x58)
    array_dyn_t< class voice_navigation_sound_t* > navigation_sound_events; // 0x0828 (0x20)
    char pad_0848[ 5144 ]; // 0x0848 (0x1418)
    bool should_have_echo; // 0x1C60 (0x01)
    char pad_1C61[ 223 ]; // 0x1C61 (0xdf)
    array_local_t< class sound_event_t*, 20ul > N0000D549; // 0x1D40 (0xc0)
    char pad_1E00[ 8 ]; // 0x1E00 (0x08)
    array_local_t< sound::sound_stream_t, 1ul > N0000D565; // 0x1E08 (0x30)
    array_local_t< bool, 1ul > N0001ADE2; // 0x1E38 (0x21)
    char pad_1E59[ 7 ]; // 0x1E59 (0x07)
    sound_event_t cb_radio_start; // 0x1E60 (0x10)
    sound_event_t cb_radio_stop; // 0x1E70 (0x10)
    sound_event_t cb_radio_noise; // 0x1E80 (0x10)
    array_dyn_t< class cbradio_beep_item_t* > N0000D574; // 0x1E90 (0x20)
    char pad_1EB0[ 16 ]; // 0x1EB0 (0x10)
    array_local_t< string_dyn_t, 3ul > ambient_sounds; // 0x1EC0 (0x68)
    string_dyn_t current_reverb; // 0x1F28 (0x18)
    string_dyn_t current_ambient_sfx; // 0x1F40 (0x18)
    char pad_1F58[ 8 ]; // 0x1F58 (0x08)

    virtual void destructor();

public:
    uint8_t get_has_echo() const
    {
        return should_have_echo;
    }

    vec2s_t get_window_state() const
    {
        return window_state;
    }

    bool get_is_camera_inside() const
    {
        return is_camera_inside;
    }

    bool get_is_on_interior_cam() const
    {
        return interior_camera;
    }

    float get_camera_rotation_in_cabin() const
    {
        return camera_rotation_in_cabin;
    }

    bool get_cabin_out() const
    {
        return cabin_out;
    }

    voice_navigation_sound_t* get_now_playing_navigation_sound() const
    {
        return now_playing_navigation_sound;
    }
};
static_assert( sizeof( sound_library_t ) == 0x1F60 );

#pragma pack( pop )
