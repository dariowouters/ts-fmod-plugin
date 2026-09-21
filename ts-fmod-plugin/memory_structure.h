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


// Size: W 0x1ED10, L|A 0x1ED08 1.61
class game_actor_u : public /* [W|L|A 0x10] @ W|L|A 0x00 */ unit_t
{
public:
    char pad_WLA_0x0010[ 8 ]; // W|L|A 0x0010 (W|L|A 0x08)
    class game_physics_vehicle_u *game_physics_vehicle; // W|L|A 0x0018 (W|L|A 0x08)
    class visual_interior_u *visual_interior; // W|L|A 0x0020 (W|L|A 0x08)
    char pad_WLA_0x0028[ 8 ]; // W|L|A 0x0028 (W|L|A 0x08)
    class game_actor_hud_u *game_actor_hud; // W|L|A 0x0030 (W|L|A 0x08)
    char pad_WLA_0x0038[ 112 ]; // W|L|A 0x0038 (W|L|A 0x70)
    class history_stream_set_u *history_stream_set_u; // W|L|A 0x00A8 (W|L|A 0x08)
    char pad_WLA_0x00B0[ 16 ]; // W|L|A 0x00B0 (W|L|A 0x10)
    class history_manager_u *history_manager_u; // W|L|A 0x00C0 (W|L|A 0x08)
    class game_trailer_actor_u *game_trailer_actor; // W|L|A 0x00C8 (W|L|A 0x08)
    char pad_WLA_0x00D0[ 8 ]; // W|L|A 0x00D0 (W|L|A 0x08)
    array_dyn_t< class kdop_item_t* > N0000954A; // W|L|A 0x00D8 (W 0x28, L|A 0x20)
    char pad_W_0x0100__LA_0x00F8[ 172 ]; // W 0x0100, L|A 0x00F8 (W|L|A 0xac)
    uint32_t current_camera; // W 0x01AC, L|A 0x01A4 (W|L|A 0x04) 2 = int, 1 = chase, 7 = top, 5 = roof, 4 = side_back, 3 = hood, 6 = side_front, 9 = cinematic, 0 = dev
    char pad_W_0x01B0__LA_0x01A8[ 8 ]; // W 0x01B0, L|A 0x01A8 (W|L|A 0x08)
    uint32_t engine_state; // W 0x01B8, L|A 0x01B0 (W|L|A 0x04)
    bool ignition; // W 0x01BC, L|A 0x01B4 (W|L|A 0x01)
    char pad_W_0x01BD__LA_0x01B5[ 7 ]; // W 0x01BD, L|A 0x01B5 (W|L|A 0x07)
    bool parking_brake; // W 0x01C4, L|A 0x01BC (W|L|A 0x01)
    char pad_W_0x01C5__LA_0x01BD[ 9 ]; // W 0x01C5, L|A 0x01BD (W|L|A 0x09)
    bool engine_brake_enabled; // W 0x01CE, L|A 0x01C6 (W|L|A 0x01)
    char pad_W_0x01CF__LA_0x01C7[ 25 ]; // W 0x01CF, L|A 0x01C7 (W|L|A 0x19)
    uint32_t retarder_i_level; // W 0x01E8, L|A 0x01E0 (W|L|A 0x04)
    float retarder_f_level; // W 0x01EC, L|A 0x01E4 (W|L|A 0x04)
    char pad_W_0x01F0__LA_0x01E8[ 4 ]; // W 0x01F0, L|A 0x01E8 (W|L|A 0x04)
    bool diff_locked; // W 0x01F4, L|A 0x01EC (W|L|A 0x01)
    char pad_W_0x01F5__LA_0x01ED[ 15 ]; // W 0x01F5, L|A 0x01ED (W|L|A 0x0f)
    bool cruise_control_enabled; // W 0x0204, L|A 0x01FC (W|L|A 0x01)
    char pad_W_0x0205__LA_0x01FD[ 3 ]; // W 0x0205, L|A 0x01FD (W|L|A 0x03)
    float cruise_control_speed; // W 0x0208, L|A 0x0200 (W|L|A 0x04)
    char pad_W_0x020C__LA_0x0204[ 36 ]; // W 0x020C, L|A 0x0204 (W|L|A 0x24)
    uint32_t wiper_setting; // W 0x0230, L|A 0x0228 (W|L|A 0x04)
    char pad_W_0x0234__LA_0x022C[ 16 ]; // W 0x0234, L|A 0x022C (W|L|A 0x10)
    uint16_t flags; // W 0x0244, L|A 0x023C (W|L|A 0x02) 6 = parking lights, 8 = low beam, 7 = high beam, 5 = beacons, 0 = truck axle lifted, 1 = trailer axle lifted
    char pad_W_0x0246__LA_0x023E[ 4 ]; // W 0x0246, L|A 0x023E (W|L|A 0x04)
    uint16_t additional_illumination; // W 0x024A, L|A 0x0242 (W|L|A 0x02) (flags) 3 = front, 4 = roof
    char pad_W_0x024C__LA_0x0244[ 12 ]; // W 0x024C, L|A 0x0244 (W|L|A 0x0c)
    float wipers_intermittent_time; // W 0x0258, L|A 0x0250 (W|L|A 0x04)
    float wipers_position; // W 0x025C, L|A 0x0254 (W|L|A 0x04)
    char pad_W_0x0260__LA_0x0258[ 8 ]; // W 0x0260, L|A 0x0258 (W|L|A 0x08)
    array_local_t< float, 7 > N0000956F; // W 0x0268, L|A 0x0260 (W|L|A 0x3c)
    char pad_W_0x02A4__LA_0x029C[ 4 ]; // W 0x02A4, L|A 0x029C (W|L|A 0x04)
    array_local_t< float, 7 > N00009577; // W 0x02A8, L|A 0x02A0 (W|L|A 0x3c)
    char pad_W_0x02E4__LA_0x02DC[ 4 ]; // W 0x02E4, L|A 0x02DC (W|L|A 0x04)
    array_local_t< float, 3 > N0000957F; // W 0x02E8, L|A 0x02E0 (W|L|A 0x2c)
    char pad_W_0x0314__LA_0x030C[ 4 ]; // W 0x0314, L|A 0x030C (W|L|A 0x04)
    array_local_t< float, 3 > N0002C1B7; // W 0x0318, L|A 0x0310 (W|L|A 0x2c)
    char pad_W_0x0344__LA_0x033C[ 8 ]; // W 0x0344, L|A 0x033C (W|L|A 0x08)
    float rpm; // W 0x034C, L|A 0x0344 (W|L|A 0x04)
    float air_pressure; // W 0x0350, L|A 0x0348 (W|L|A 0x04)
    float brake_pressure; // W 0x0354, L|A 0x034C (W|L|A 0x04)
    float max_air_pressure; // W 0x0358, L|A 0x0350 (W|L|A 0x04)
    char pad_W_0x035C__LA_0x0354[ 8 ]; // W 0x035C, L|A 0x0354 (W|L|A 0x08)
    float oil_temp; // W 0x0364, L|A 0x035C (W|L|A 0x04)
    char pad_W_0x0368__LA_0x0360[ 4 ]; // W 0x0368, L|A 0x0360 (W|L|A 0x04)
    float water_temp; // W 0x036C, L|A 0x0364 (W|L|A 0x04)
    char pad_W_0x0370__LA_0x0368[ 4 ]; // W 0x0370, L|A 0x0368 (W|L|A 0x04)
    float battery_voltage; // W 0x0374, L|A 0x036C (W|L|A 0x04)
    char pad_W_0x0378__LA_0x0370[ 8 ]; // W 0x0378, L|A 0x0370 (W|L|A 0x08)
    float turbo_pressure; // W 0x0380, L|A 0x0378 (W|L|A 0x04)
    char pad_W_0x0384__LA_0x037C[ 16 ]; // W 0x0384, L|A 0x037C (W|L|A 0x10)
    float light_switch; // W 0x0394, L|A 0x038C (W|L|A 0x04) 0 = off, 0.5 = parking, 1 = low beam
    float light_switch_state; // W 0x0398, L|A 0x0390 (W|L|A 0x04) 0 = off, 0.5 = parking, 1 = low beam (instant)
    float high_beam_stick; // W 0x039C, L|A 0x0394 (W|L|A 0x04) 0 = off, 1 = on
    float high_beam_state; // W 0x03A0, L|A 0x0398 (W|L|A 0x04)
    float light_horn_stick; // W 0x03A4, L|A 0x039C (W|L|A 0x04) 0 = off, 1 = on
    float light_horn_state; // W 0x03A8, L|A 0x03A0 (W|L|A 0x04) 0 = off, 1 = on (instant)
    float indicator_stick; // W 0x03AC, L|A 0x03A4 (W|L|A 0x04) 0 = left indicator, 0.5 = none, 1 = right
    float indicator_state; // W 0x03B0, L|A 0x03A8 (W|L|A 0x04) 0 = left indicator, 0.5 = none, 1 = right (instant)
    float hazard_warning_btn; // W 0x03B4, L|A 0x03AC (W|L|A 0x04) 0 = off, 1 = on (instant)
    float hazard_warning_state; // W 0x03B8, L|A 0x03B0 (W|L|A 0x04) 0 = off, 1 = on
    float beacon_switch; // W 0x03BC, L|A 0x03B4 (W|L|A 0x04) 0 = off, 1 = on (instant)
    float beacon_state; // W 0x03C0, L|A 0x03B8 (W|L|A 0x04) 0 = off, 1 = on
    char pad_W_0x03C4__LA_0x03BC[ 8 ]; // W 0x03C4, L|A 0x03BC (W|L|A 0x08)
    float handbrake_handle; // W 0x03CC, L|A 0x03C4 (W|L|A 0x04) 0 = off, 1 = on
    float handbrake_state; // W 0x03D0, L|A 0x03C8 (W|L|A 0x04) 0 = off, 1 = on (instant)
    char pad_W_0x03D4__LA_0x03CC[ 24 ]; // W 0x03D4, L|A 0x03CC (W|L|A 0x18)
    float engine_brake_stick; // W 0x03EC, L|A 0x03E4 (W|L|A 0x04) 0 = off, 1 = full; steps dependant on engine data
    float engine_brake_state; // W 0x03F0, L|A 0x03E8 (W|L|A 0x04) 0 = off, 1 = full (instant); steps dependant on engine data
    char pad_W_0x03F4__LA_0x03EC[ 20 ]; // W 0x03F4, L|A 0x03EC (W|L|A 0x14)
    float wipers_stick; // W 0x0408, L|A 0x0400 (W|L|A 0x04) 0 = off, 0.333 = intermittent, 0.666 = slow, 1 = fast
    float wipers_state; // W 0x040C, L|A 0x0404 (W|L|A 0x04) 0 = off, 0.333 = intermittent, 0.666 = slow, 1 = fast (instant)
    char pad_W_0x0410__LA_0x0408[ 36 ]; // W 0x0410, L|A 0x0408 (W|L|A 0x24)
    uint8_t left_window_moving_direction; // W 0x0434, L|A 0x042C (W|L|A 0x01) 1 = got to end down; 2 = got to end up; 16 = down; 32 = up
    uint8_t is_left_window_moving; // W 0x0435, L|A 0x042D (W|L|A 0x01) 1 = down auto; 16 = down holding btn; 2 = auto up; 32 = up holding button
    char pad_W_0x0436__LA_0x042E[ 2 ]; // W 0x0436, L|A 0x042E (W|L|A 0x02)
    float left_window_state; // W 0x0438, L|A 0x0430 (W|L|A 0x04) 0 = up; 1 = down
    float left_window_btn; // W 0x043C, L|A 0x0434 (W|L|A 0x04) 0 = up; 0.5 off; 1 = down
    float left_window_btn_state; // W 0x0440, L|A 0x0438 (W|L|A 0x04) 0 = up; 0.5 off; 1 = down (instant)
    char pad_W_0x0444__LA_0x043C[ 8 ]; // W 0x0444, L|A 0x043C (W|L|A 0x08)
    uint8_t right_window_moving_direction; // W 0x044C, L|A 0x0444 (W|L|A 0x01) 1 = got to end down; 2 = got to end up; 16 = down; 32 = up
    uint8_t is_right_window_moving; // W 0x044D, L|A 0x0445 (W|L|A 0x01) 1 = down auto; 16 = down holding btn; 2 = auto up; 32 = up holding button
    char pad_W_0x044E__LA_0x0446[ 2 ]; // W 0x044E, L|A 0x0446 (W|L|A 0x02)
    float right_window_state; // W 0x0450, L|A 0x0448 (W|L|A 0x04) 0 = up; 1 = down
    float right_window_btn; // W 0x0454, L|A 0x044C (W|L|A 0x04) 0 = up; 0.5 off; 1 = down
    float right_window_btn_state; // W 0x0458, L|A 0x0450 (W|L|A 0x04) 0 = up; 0.5 off; 1 = down (instant)
    char pad_W_0x045C__LA_0x0454[ 6364 ]; // W 0x045C, L|A 0x0454 (W|L|A 0x18dc)
    class sound_player_truck_t *sound_player_truck; // W 0x1D38, L|A 0x1D30 (W|L|A 0x08)
    char pad_W_0x1D40__LA_0x1D38[ 52 ]; // W 0x1D40, L|A 0x1D38 (W|L|A 0x34)
    float rpm2; // W 0x1D74, L|A 0x1D6C (W|L|A 0x04)
    float some_throttle; // W 0x1D78, L|A 0x1D70 (W|L|A 0x04)
    char pad_W_0x1D7C__LA_0x1D74[ 16 ]; // W 0x1D7C, L|A 0x1D74 (W|L|A 0x10)
    float throttle_input; // W 0x1D8C, L|A 0x1D84 (W|L|A 0x04) truck.input.throttle
    float brake_input; // W 0x1D90, L|A 0x1D88 (W|L|A 0x04) truck.input.brake
    float clutch_input; // W 0x1D94, L|A 0x1D8C (W|L|A 0x04) truck.input.clutch
    char pad_W_0x1D98__LA_0x1D90[ 4 ]; // W 0x1D98, L|A 0x1D90 (W|L|A 0x04)
    float steering_input; // W 0x1D9C, L|A 0x1D94 (W|L|A 0x04)
    char pad_W_0x1DA0__LA_0x1D98[ 48 ]; // W 0x1DA0, L|A 0x1D98 (W|L|A 0x30)
    placement_t placement; // W 0x1DD0, L|A 0x1DC8 (W|L|A 0x20)
    char pad_W_0x1DF0__LA_0x1DE8[ 8 ]; // W 0x1DF0, L|A 0x1DE8 (W|L|A 0x08)
    class model_object_u *driver_model; // W 0x1DF8, L|A 0x1DF0 (W|L|A 0x08)
    char pad_W_0x1E00__LA_0x1DF8[ 40 ]; // W 0x1E00, L|A 0x1DF8 (W|L|A 0x28)
    class physics_gearbox_sequential_u *physics_gearbox_sequential_u; // W 0x1E28, L|A 0x1E20 (W|L|A 0x08)
    class physics_gearbox_automatic_u *physics_gearbox_automatic_u; // W 0x1E30, L|A 0x1E28 (W|L|A 0x08)
    class physics_gearbox_direct_u *physics_gearbox_direct_u; // W 0x1E38, L|A 0x1E30 (W|L|A 0x08)
    char pad_W_0x1E40__LA_0x1E38[ 8 ]; // W 0x1E40, L|A 0x1E38 (W|L|A 0x08)
    class accessory_head_lights_data_u *accessory_head_lights_data_u; // W 0x1E48, L|A 0x1E40 (W|L|A 0x08)
    class head_lights_render_state_t *head_lights_render_state; // W 0x1E50, L|A 0x1E48 (W|L|A 0x08)
    char pad_W_0x1E58__LA_0x1E50[ 24 ]; // W 0x1E58, L|A 0x1E50 (W|L|A 0x18)
    array_local_t< char[ 24 ] /* actor_damage_cache_t */, 3 > N000098B2; // W 0x1E70, L|A 0x1E68 (W|L|A 0x68)
    char pad_W_0x1ED8__LA_0x1ED0[ 48 ]; // W 0x1ED8, L|A 0x1ED0 (W|L|A 0x30)
    array_local_t< vec3s_t, 3 > N000098C0; // W 0x1F08, L|A 0x1F00 (W|L|A 0x44)
    char pad_W_0x1F4C__LA_0x1F44[ 36 ]; // W 0x1F4C, L|A 0x1F44 (W|L|A 0x24)
    array_local_t< char[ 24 ] /* pct_vertex_t */, 4852 > N000098CD; // W 0x1F70, L|A 0x1F68 (W|L|A 0x1c700)
    char pad_W_0x1E670__LA_0x1E668[ 1696 ]; // W 0x1E670, L|A 0x1E668 (W|L|A 0x6a0)

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
static_assert( sizeof( game_actor_u ) == 0x1ED10 );


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

// Size: W 0x1FF0, L|A 0x1F98 1.61
class sound_library_t
{
public:
    char pad_WLA_0x0008[ 8 ]; // W|L|A 0x0008 (W|L|A 0x08)
    array_local_t< class sound_event_t*, 33 > ui_sound_events; // W|L|A 0x0010 (W|L|A 0x128)
    char pad_WLA_0x0138[ 12 ]; // W|L|A 0x0138 (W|L|A 0x0c)
    uint32_t state; // W|L|A 0x0144 (W|L|A 0x04) 1 = on; 2 = off
    bool interior_camera; // W|L|A 0x0148 (W|L|A 0x01)
    bool is_camera_inside; // W|L|A 0x0149 (W|L|A 0x01)
    char pad_WLA_0x014A[ 2 ]; // W|L|A 0x014A (W|L|A 0x02)
    float camera_rotation_in_cabin; // W|L|A 0x014C (W|L|A 0x04)
    float cabin_out; // W|L|A 0x0150 (W|L|A 0x04)
    char pad_WLA_0x0154[ 4 ]; // W|L|A 0x0154 (W|L|A 0x04)
    class fmod_parameter_t *cabin_type_param; // W|L|A 0x0158 (W|L|A 0x08)
    class fmod_parameter_t *cabin_rot_param; // W|L|A 0x0160 (W|L|A 0x08)
    class fmod_parameter_t *cabin_out_param; // W|L|A 0x0168 (W|L|A 0x08)
    vec2s_t window_state; // W|L|A 0x0170 (W|L|A 0x08)
    class fmod_parameter_t *wnd_left_param; // W|L|A 0x0178 (W|L|A 0x08)
    class fmod_parameter_t *wnd_right_param; // W|L|A 0x0180 (W|L|A 0x08)
    class fmod_parameter_t *wetness_param; // W|L|A 0x0188 (W|L|A 0x08)
    float daytime; // W|L|A 0x0190 (W|L|A 0x04)
    char pad_WLA_0x0194[ 12 ]; // W|L|A 0x0194 (W|L|A 0x0c)
    class fmod_parameter_t *daytime_param; // W|L|A 0x01A0 (W|L|A 0x08)
    char pad_WLA_0x01A8[ 48 ]; // W|L|A 0x01A8 (W|L|A 0x30)
    array_local_t< voice_navigation_sound_t, 38 > navigation_sounds; // W|L|A 0x01D8 (W|L|A 0x610)
    string_dyn_t current_navigation_bank_path; // W|L|A 0x07E8 (W 0x20, L|A 0x18)
    class voice_navigation_sound_t *now_playing_navigation_sound; // W 0x0808, L|A 0x0800 (W|L|A 0x08)
    list_dyn_t< class voice_navigation_sound_t* > N0000433C; // W 0x0810, L|A 0x0808 (W 0x70, L|A 0x58)
    array_dyn_t< class voice_navigation_sound_t* > navigation_sound_events; // W 0x0880, L|A 0x0860 (W 0x28, L|A 0x20)
    char pad_W_0x08A8__LA_0x0880[ 5144 ]; // W 0x08A8, L|A 0x0880 (W|L|A 0x1418)
    bool should_have_echo; // W 0x1CC0, L|A 0x1C98 (W|L|A 0x01)
    char pad_W_0x1CC1__LA_0x1C99[ 223 ]; // W 0x1CC1, L|A 0x1C99 (W|L|A 0xdf)
    array_local_t< class sound_event_t*, 20 > N0000D549; // W 0x1DA0, L|A 0x1D78 (W|L|A 0xc0)
    char pad_W_0x1E60__LA_0x1E38[ 8 ]; // W 0x1E60, L|A 0x1E38 (W|L|A 0x08)
    array_local_t< sound::sound_stream_t, 1 > N0000D565; // W 0x1E68, L|A 0x1E40 (W|L|A 0x30)
    array_local_t< bool, 1 > N0001ADE2; // W 0x1E98, L|A 0x1E70 (W|L|A 0x21)
    char pad_W_0x1EB9__LA_0x1E91[ 7 ]; // W 0x1EB9, L|A 0x1E91 (W|L|A 0x07)
    sound_event_t cb_radio_start; // W 0x1EC0, L|A 0x1E98 (W|L|A 0x10)
    sound_event_t cb_radio_stop; // W 0x1ED0, L|A 0x1EA8 (W|L|A 0x10)
    sound_event_t cb_radio_noise; // W 0x1EE0, L|A 0x1EB8 (W|L|A 0x10)
    array_dyn_t< class cbradio_beep_item_t* > N0000D574; // W 0x1EF0, L|A 0x1EC8 (W 0x28, L|A 0x20)
    char pad_W_0x1F18__LA_0x1EE8[ 16 ]; // W 0x1F18, L|A 0x1EE8 (W|L|A 0x10)
    array_local_t< string_dyn_t, 3 > ambient_sounds; // W 0x1F28, L|A 0x1EF8 (W 0x80, L|A 0x68)
    string_dyn_t current_reverb; // W 0x1FA8, L|A 0x1F60 (W 0x20, L|A 0x18)
    string_dyn_t current_ambient_sfx; // W 0x1FC8, L|A 0x1F78 (W 0x20, L|A 0x18)
    char pad_W_0x1FE8__LA_0x1F90[ 8 ]; // W 0x1FE8, L|A 0x1F90 (W|L|A 0x08)

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
static_assert( sizeof( sound_library_t ) == 0x1FF0 );

#pragma pack( pop )
