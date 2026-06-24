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

struct vec4s_t // Size: 0x0010
{
public:
    float w; // 0x0000 (0x04)
    float x; // 0x0004 (0x04)
    float y; // 0x0008 (0x04)
    float z; // 0x000C (0x04)
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

class placement_t // Size: 0x0020
{
public:
    vec3s_t pos;  // 0x0000 (0x0c)
    int16_t cx;   // 0x000C (0x02)
    int16_t cz;   // 0x000E (0x02)
    vec4s_t rot;  // 0x0010 (0x10)
};
static_assert( sizeof( placement_t ) == 0x20 );


// Size: W|L|A 0x1EBC0
class game_actor_u : public /* [W|L|A 0x10] @ W|L|A 0x00 */ unit_t
{
public:
    char pad_WLA_0x0010[ 8 ];                           // W|L|A 0x0010 (W|L|A 0x08)
    class game_physics_vehicle_u* game_physics_vehicle; // W|L|A 0x0018 (W|L|A 0x08)
    class visual_interior_u* visual_interior;           // W|L|A 0x0020 (W|L|A 0x08)
    char pad_WLA_0x0028[ 8 ];                           // W|L|A 0x0028 (W|L|A 0x08)
    class game_actor_hud_u* game_actor_hud;             // W|L|A 0x0030 (W|L|A 0x08)
    char pad_WLA_0x0038[ 112 ];                         // W|L|A 0x0038 (W|L|A 0x70)
    class history_stream_set_u* history_stream_set_u;   // W|L|A 0x00A8 (W|L|A 0x08)
    char pad_WLA_0x00B0[ 16 ];                          // W|L|A 0x00B0 (W|L|A 0x10)
    class history_manager_u* history_manager_u;         // W|L|A 0x00C0 (W|L|A 0x08)
    class game_trailer_actor_u* game_trailer_actor;     // W|L|A 0x00C8 (W|L|A 0x08)
    char pad_WLA_0x00D0[ 116 ];                         // W|L|A 0x00D0 (W|L|A 0x74)
    uint32_t current_camera;     // W|L|A 0x0144 (W|L|A 0x04) 2 = int, 1 = chase, 7 = top, 5 = roof, 4 = side_back, 3 = hood, 6 = side_front, 9 = cinematic, 0 = dev
    char pad_WLA_0x0148[ 8 ];    // W|L|A 0x0148 (W|L|A 0x08)
    uint32_t engine_state;       // W|L|A 0x0150 (W|L|A 0x04)
    bool ignition;               // W|L|A 0x0154 (W|L|A 0x01)
    char pad_WLA_0x0155[ 7 ];    // W|L|A 0x0155 (W|L|A 0x07)
    bool parking_brake;          // W|L|A 0x015C (W|L|A 0x01)
    char pad_WLA_0x015D[ 9 ];    // W|L|A 0x015D (W|L|A 0x09)
    bool engine_brake_enabled;   // W|L|A 0x0166 (W|L|A 0x01)
    char pad_WLA_0x0167[ 25 ];   // W|L|A 0x0167 (W|L|A 0x19)
    uint32_t retarder_i_level;   // W|L|A 0x0180 (W|L|A 0x04)
    float retarder_f_level;      // W|L|A 0x0184 (W|L|A 0x04)
    char pad_WLA_0x0188[ 4 ];    // W|L|A 0x0188 (W|L|A 0x04)
    bool diff_locked;            // W|L|A 0x018C (W|L|A 0x01)
    char pad_WLA_0x018D[ 12 ];   // W|L|A 0x018D (W|L|A 0x0c)
    bool cruise_control_enabled; // W|L|A 0x0199 (W|L|A 0x01)
    char pad_WLA_0x019A[ 2 ];    // W|L|A 0x019A (W|L|A 0x02)
    float cruise_control_speed;  // W|L|A 0x019C (W|L|A 0x04)
    char pad_WLA_0x01A0[ 32 ];   // W|L|A 0x01A0 (W|L|A 0x20)
    uint32_t wiper_setting;      // W|L|A 0x01C0 (W|L|A 0x04)
    char pad_WLA_0x01C4[ 12 ];   // W|L|A 0x01C4 (W|L|A 0x0c)
    uint16_t flags; // W|L|A 0x01D0 (W|L|A 0x02) 6 = parking lights, 8 = low beam, 7 = high beam, 5 = beacons, 0 = truck axle lifted, 1 = trailer axle lifted
    char pad_WLA_0x01D2[ 4 ];            // W|L|A 0x01D2 (W|L|A 0x04)
    uint16_t additional_illumination;    // W|L|A 0x01D6 (W|L|A 0x02) (flags) 3 = front, 4 = roof
    char pad_WLA_0x01D8[ 12 ];           // W|L|A 0x01D8 (W|L|A 0x0c)
    float wipers_intermittent_time;      // W|L|A 0x01E4 (W|L|A 0x04)
    float wipers_position;               // W|L|A 0x01E8 (W|L|A 0x04)
    char pad_WLA_0x01EC[ 4 ];            // W|L|A 0x01EC (W|L|A 0x04)
    array_local_t< float, 7 > N0000956F; // W|L|A 0x01F0 (W|L|A 0x3c)
    char pad_WLA_0x022C[ 4 ];            // W|L|A 0x022C (W|L|A 0x04)
    array_local_t< float, 7 > N00009577; // W|L|A 0x0230 (W|L|A 0x3c)
    char pad_WLA_0x026C[ 4 ];            // W|L|A 0x026C (W|L|A 0x04)
    array_local_t< float, 3 > N0000957F; // W|L|A 0x0270 (W|L|A 0x2c)
    char pad_WLA_0x029C[ 4 ];            // W|L|A 0x029C (W|L|A 0x04)
    array_local_t< float, 3 > N00009585; // W|L|A 0x02A0 (W|L|A 0x2c)
    char pad_WLA_0x02CC[ 8 ];            // W|L|A 0x02CC (W|L|A 0x08)
    float rpm;                           // W|L|A 0x02D4 (W|L|A 0x04)
    float air_pressure;                  // W|L|A 0x02D8 (W|L|A 0x04)
    float brake_pressure;                // W|L|A 0x02DC (W|L|A 0x04)
    float max_air_pressure;              // W|L|A 0x02E0 (W|L|A 0x04)
    char pad_WLA_0x02E4[ 8 ];            // W|L|A 0x02E4 (W|L|A 0x08)
    float oil_temp;                      // W|L|A 0x02EC (W|L|A 0x04)
    char pad_WLA_0x02F0[ 4 ];            // W|L|A 0x02F0 (W|L|A 0x04)
    float water_temp;                    // W|L|A 0x02F4 (W|L|A 0x04)
    char pad_WLA_0x02F8[ 4 ];            // W|L|A 0x02F8 (W|L|A 0x04)
    float battery_voltage;               // W|L|A 0x02FC (W|L|A 0x04)
    char pad_WLA_0x0300[ 8 ];            // W|L|A 0x0300 (W|L|A 0x08)
    float turbo_pressure;                // W|L|A 0x0308 (W|L|A 0x04)
    char pad_WLA_0x030C[ 16 ];           // W|L|A 0x030C (W|L|A 0x10)
    float light_switch;                  // W|L|A 0x031C (W|L|A 0x04) 0 = off, 0.5 = parking, 1 = low beam
    float light_switch_state;            // W|L|A 0x0320 (W|L|A 0x04) 0 = off, 0.5 = parking, 1 = low beam (instant)
    float high_beam_stick;               // W|L|A 0x0324 (W|L|A 0x04) 0 = off, 1 = on
    float high_beam_state;               // W|L|A 0x0328 (W|L|A 0x04)
    float light_horn_stick;              // W|L|A 0x032C (W|L|A 0x04) 0 = off, 1 = on
    float light_horn_state;              // W|L|A 0x0330 (W|L|A 0x04) 0 = off, 1 = on (instant)
    float indicator_stick;               // W|L|A 0x0334 (W|L|A 0x04) 0 = left indicator, 0.5 = none, 1 = right
    float indicator_state;      // W|L|A 0x0338 (W|L|A 0x04) 0 = left indicator, 0.5 = none, 1 = right (instant)
    float hazard_warning_btn;   // W|L|A 0x033C (W|L|A 0x04) 0 = off, 1 = on (instant)
    float hazard_warning_state; // W|L|A 0x0340 (W|L|A 0x04) 0 = off, 1 = on
    float beacon_switch;        // W|L|A 0x0344 (W|L|A 0x04) 0 = off, 1 = on (instant)
    float beacon_state;         // W|L|A 0x0348 (W|L|A 0x04) 0 = off, 1 = on
    char pad_WLA_0x034C[ 8 ];   // W|L|A 0x034C (W|L|A 0x08)
    float handbrake_handle;     // W|L|A 0x0354 (W|L|A 0x04) 0 = off, 1 = on
    float handbrake_state;      // W|L|A 0x0358 (W|L|A 0x04) 0 = off, 1 = on (instant)
    char pad_WLA_0x035C[ 24 ];  // W|L|A 0x035C (W|L|A 0x18)
    float engine_brake_stick;   // W|L|A 0x0374 (W|L|A 0x04) 0 = off, 1 = full; steps dependant on engine data
    float engine_brake_state;   // W|L|A 0x0378 (W|L|A 0x04) 0 = off, 1 = full (instant); steps dependant on engine data
    char pad_WLA_0x037C[ 20 ];  // W|L|A 0x037C (W|L|A 0x14)
    float wipers_stick;         // W|L|A 0x0390 (W|L|A 0x04) 0 = off, 0.333 = intermittent, 0.666 = slow, 1 = fast
    float wipers_state; // W|L|A 0x0394 (W|L|A 0x04) 0 = off, 0.333 = intermittent, 0.666 = slow, 1 = fast (instant)
    char pad_WLA_0x0398[ 20 ];            // W|L|A 0x0398 (W|L|A 0x14)
    uint8_t left_window_moving_direction; // W|L|A 0x03AC (W|L|A 0x01) 1 = got to end down; 2 = got to end up; 16 = down; 32 = up
    uint8_t is_left_window_moving; // W|L|A 0x03AD (W|L|A 0x01) 1 = down auto; 16 = down holding btn; 2 = auto up; 32 = up holding button
    char pad_WLA_0x03AE[ 2 ];      // W|L|A 0x03AE (W|L|A 0x02)
    float left_window_state;       // W|L|A 0x03B0 (W|L|A 0x04) 0 = up; 1 = down
    float left_window_btn;         // W|L|A 0x03B4 (W|L|A 0x04) 0 = up; 0.5 off; 1 = down
    float left_window_btn_state;   // W|L|A 0x03B8 (W|L|A 0x04) 0 = up; 0.5 off; 1 = down (instant)
    char pad_WLA_0x03BC[ 8 ];      // W|L|A 0x03BC (W|L|A 0x08)
    uint8_t right_window_moving_direction; // W|L|A 0x03C4 (W|L|A 0x01) 1 = got to end down; 2 = got to end up; 16 = down; 32 = up
    uint8_t is_right_window_moving; // W|L|A 0x03C5 (W|L|A 0x01) 1 = down auto; 16 = down holding btn; 2 = auto up; 32 = up holding button
    char pad_WLA_0x03C6[ 2 ];       // W|L|A 0x03C6 (W|L|A 0x02)
    float right_window_state;       // W|L|A 0x03C8 (W|L|A 0x04) 0 = up; 1 = down
    float right_window_btn;         // W|L|A 0x03CC (W|L|A 0x04) 0 = up; 0.5 off; 1 = down
    float right_window_btn_state;   // W|L|A 0x03D0 (W|L|A 0x04) 0 = up; 0.5 off; 1 = down (instant)
    char pad_WLA_0x03D4[ 6300 ];    // W|L|A 0x03D4 (W|L|A 0x189c)
    class sound_player_truck_t* sound_player_truck;                   // W|L|A 0x1C70 (W|L|A 0x08)
    char pad_WLA_0x1C78[ 52 ];                                        // W|L|A 0x1C78 (W|L|A 0x34)
    float rpm2;                                                       // W|L|A 0x1CAC (W|L|A 0x04)
    float some_throttle;                                              // W|L|A 0x1CB0 (W|L|A 0x04)
    char pad_WLA_0x1CB4[ 12 ];                                        // W|L|A 0x1CB4 (W|L|A 0x0c)
    float throttle_input;                                             // W|L|A 0x1CC0 (W|L|A 0x04) truck.input.throttle
    float brake_input;                                                // W|L|A 0x1CC4 (W|L|A 0x04) truck.input.brake
    float clutch_input;                                               // W|L|A 0x1CC8 (W|L|A 0x04) truck.input.clutch
    char pad_WLA_0x1CCC[ 4 ];                                         // W|L|A 0x1CCC (W|L|A 0x04)
    float steering_input;                                             // W|L|A 0x1CD0 (W|L|A 0x04)
    char pad_WLA_0x1CD4[ 48 ];                                        // W|L|A 0x1CD4 (W|L|A 0x30)
    placement_t placement;                                            // W|L|A 0x1D04 (W|L|A 0x20)
    char pad_WLA_0x1D24[ 12 ];                                        // W|L|A 0x1D24 (W|L|A 0x0c)
    class model_object_u* driver_model;                               // W|L|A 0x1D30 (W|L|A 0x08)
    char pad_WLA_0x1D38[ 40 ];                                        // W|L|A 0x1D38 (W|L|A 0x28)
    class physics_gearbox_sequential_u* physics_gearbox_sequential_u; // W|L|A 0x1D60 (W|L|A 0x08)
    class physics_gearbox_automatic_u* physics_gearbox_automatic_u;   // W|L|A 0x1D68 (W|L|A 0x08)
    class physics_gearbox_direct_u* physics_gearbox_direct_u;         // W|L|A 0x1D70 (W|L|A 0x08)
    char pad_WLA_0x1D78[ 8 ];                                         // W|L|A 0x1D78 (W|L|A 0x08)
    class accessory_head_lights_data_u* accessory_head_lights_data_u; // W|L|A 0x1D80 (W|L|A 0x08)
    class head_lights_render_state_t* head_lights_render_state;       // W|L|A 0x1D88 (W|L|A 0x08)
    char pad_WLA_0x1D90[ 24 ];                                        // W|L|A 0x1D90 (W|L|A 0x18)
    array_local_t< char[ 24 ] /* actor_damage_cache_t */, 3 > N000098B2; // W|L|A 0x1DA8 (W|L|A 0x68)
    char pad_WLA_0x1E10[ 8 ];                                         // W|L|A 0x1E10 (W|L|A 0x08)
    array_local_t< vec3s_t, 3 > N000098C0;                            // W|L|A 0x1E18 (W|L|A 0x44)
    char pad_WLA_0x1E5C[ 36 ];                                        // W|L|A 0x1E5C (W|L|A 0x24)
    array_local_t< char[ 24 ] /* pct_vertex_t */, 4852 > N000098CD;   // W|L|A 0x1E80 (W|L|A 0x1c700)
    char pad_WLA_0x1E580[ 1600 ];                                     // W|L|A 0x1E580 (W|L|A 0x640)


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

static_assert( sizeof( game_actor_u ) == 0x1EBC0 ); // W|L|A

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

// Size: 0x1FC8 1.60
class sound_library_t
{
public:
    char pad_0008[ 8 ]; // 0x0008 (0x08)
    array_local_t< class sound_event_t*, 30ul > ui_sound_events; // 0x0010 (0x110)
    char pad_0120[ 12 ]; // 0x0120 (0x0c)
    uint32_t state; // 0x012C (0x04) 1 = on; 2 = off
    bool interior_camera; // 0x0130 (0x01)
    bool is_camera_inside; // 0x0131 (0x01)
    char pad_0132[ 2 ]; // 0x0132 (0x02)
    float camera_rotation_in_cabin; // 0x0134 (0x04)
    float cabin_out; // 0x0138 (0x04)
    char pad_013C[ 4 ]; // 0x013C (0x04)
    class fmod_parameter_t* cabin_type_param; // 0x0140 (0x08)
    class fmod_parameter_t* cabin_rot_param; // 0x0148 (0x08)
    class fmod_parameter_t* cabin_out_param; // 0x0150 (0x08)
    vec2s_t window_state; // 0x0158 (0x08)
    class fmod_parameter_t* wnd_left_param; // 0x0160 (0x08)
    class fmod_parameter_t* wnd_right_param; // 0x0168 (0x08)
    float daytime; // 0x0170 (0x04)
    char pad_0174[ 4 ]; // 0x0174 (0x04)
    class fmod_parameter_t* daytime_param; // 0x0178 (0x08)
    char pad_0180[ 48 ]; // 0x0180 (0x30)
    array_local_t< class voice_navigation_sound_t, 38ul > navigation_sounds; // 0x01B0 (0x610)
    string_dyn_t current_navigation_bank_path; // 0x07C0 (0x18)
    voice_navigation_sound_t* now_playing_navigation_sound; // 0x07D8 (0x08)
    list_dyn_t< class voice_navigation_sound_t* > N0000433C; // 0x07E0 (0x58)
    array_dyn_t< class voice_navigation_sound_t* > navigation_sound_events; // 0x0838 (0x20)
    char pad_0858[ 5144 ]; // 0x0858 (0x1418)
    bool should_have_echo; // 0x1C70 (0x01)
    char pad_1C71[ 223 ]; // 0x1C71 (0xdf)
    array_local_t< class sound_event_t*, 20ul > N0000D549; // 0x1D50 (0xc0)
    char pad_1E10[ 8 ]; // 0x1E10 (0x08)
    array_local_t< sound::sound_stream_t, 1ul > N0000D565; // 0x1E18 (0x30)
    array_local_t< bool, 1ul > N0001ADE2; // 0x1E48 (0x21)
    char pad_1E69[ 7 ]; // 0x1E69 (0x07)
    sound_event_t cb_radio_start; // 0x1E70 (0x10)
    sound_event_t cb_radio_stop; // 0x1E80 (0x10)
    sound_event_t cb_radio_noise; // 0x1E90 (0x10)
    array_dyn_t< class cbradio_beep_item_t* > N0000D574; // 0x1EA0 (0x20)
    char pad_1EC0[ 16 ]; // 0x1EC0 (0x10)
    array_local_t< string_dyn_t, 3ul > ambient_sounds; // 0x1ED0 (0x68)
    string_dyn_t current_reverb; // 0x1F38 (0x18)
    string_dyn_t current_ambient_sfx; // 0x1F50 (0x18)
    char pad_1F68[ 8 ]; // 0x1F68 (0x08)

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
static_assert( sizeof( sound_library_t ) == 0x1FC8 );

#pragma pack( pop )
