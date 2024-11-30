#pragma once
#pragma pack(1)

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

class game_actor_u : public unit_t // Size: 0x10D8
{
public:
    char pad_0010[8]; //0x0010 (0x08)
    class game_physics_vehicle_u* game_physics_vehicle; //0x0018 (0x08)
    class visual_interior_u* visual_interior; //0x0020 (0x08)
    class game_actor_hud_u* game_actor_hud; //0x0028 (0x08)
    char pad_0030[104]; //0x0030 (0x68)
    class history_stream_set_u* history_stream_set; //0x0098 (0x08)
    char pad_00A0[16]; //0x00A0 (0x10)
    class history_manager_u* history_manager; //0x00B0 (0x08)
    class game_trailer_actor_u* game_trailer_actor; //0x00B8 (0x08)
    char pad_00C0[88]; //0x00C0 (0x58)
    uint32_t current_camera; //0x0118 (0x04) 2 = int, 1 = chase, 7 = top, 5 = roof, 4 = side_back, 3 = hood, 6 = side_front, 9 = cinematic, 0 = dev
    char pad_011C[8]; //0x011C (0x08)
    uint32_t engine_state; //0x0124 (0x04) 0 = engine off, 1 = starting, 2 = running, 3 = shutting down
    char pad_0128[8]; //0x0128 (0x08)
    uint8_t parking_brake; //0x0130 (0x01)
    char pad_0131[63]; //0x0131 (0x3f)
    float speed_limiter; //0x0170 (0x04)
    float road_speed_limit; //0x0174 (0x04)
    char pad_0178[52]; //0x0178 (0x34)
    uint16_t light_state; //0x01AC (0x02) (flags) 6 = parking, 8 = low, 7 = high, 5 = beacons
    char pad_01AE[2]; //0x01AE (0x02)
    uint16_t additional_illumination; //0x01B0 (0x02) (flags) 3 = front, 4 = roof
    char pad_01B2[14]; //0x01B2 (0x0e)
    float wipers_intermittent_time; //0x01C0 (0x04) Countdown before wipers move again when in intermittent setting
    float wipers_position; //0x01C4 (0x04) 0 = down start, 1 = down end ???
    float rpm; //0x01C8 (0x04)
    float air_pressure; //0x01CC (0x04)
    float brake_pressure; //0x01D0 (0x04)
    float max_air_pressure; //0x01D4 (0x04)
    char pad_01D8[8]; //0x01D8 (0x08)
    float oil_temp; //0x01E0 (0x04)
    char pad_01E4[4]; //0x01E4 (0x04)
    float water_temp; //0x01E8 (0x04)
    char pad_01EC[4]; //0x01EC (0x04)
    float battery_voltage; //0x01F0 (0x04)
    char pad_01F4[8]; //0x01F4 (0x08)
    float turbo_pressure; //0x01FC (0x04) ?
    char pad_0200[16]; //0x0200 (0x10)
    float light_switch; //0x0210 (0x04) 0 = off, 0.5 = parking, 1 = low beam
    float light_switch_state; //0x0214 (0x04) 0 = off, 0.5 = parking, 1 = low beam (instant)
    float high_beam_stick; //0x0218 (0x04) 0 = off, 1 = on
    float high_beam_state; //0x021C (0x04) 0 = off, 1 = on (instant)
    float light_horn_stick; //0x0220 (0x04) 0 = off, 1 = on
    float light_horn_state; //0x0224 (0x04) 0 = off, 1 = on (instant)
    float indicator_stick; //0x0228 (0x04) 0 = left indicator, 0.5 = none, 1 = right
    float indicator_state; //0x022C (0x04) 0 = left indicator, 0.5 = none, 1 = right (instant)
    float hazard_warning_btn; //0x0230 (0x04) 0 = off, 1 = on
    float hazard_warning_state; //0x0234 (0x04) 0 = off, 1 = on (instant)
    float beacon_switch; //0x0238 (0x04) 0 = off, 1 = on
    float beacon_state; //0x023C (0x04) 0 = off, 1 = on (instant)
    char pad_0240[8]; //0x0240 (0x08)
    float handbrake_handle; //0x0248 (0x04) 0 = off, 1 = on
    float handbrake_state; //0x024C (0x04) 0 = off, 1 = on (instant)
    char pad_0250[16]; //0x0250 (0x10)
    float engine_brake_stick; //0x0260 (0x04) 0 = off, 1 = full; steps dependant on engine data
    float engine_brake_state; //0x0264 (0x04) 0 = off, 1 = full (instant); steps dependant on engine data
    char pad_0268[20]; //0x0268 (0x14)
    float wipers_stick; //0x027C (0x04) 0 = off, 0.333 = intermittent, 0.666 = slow, 1 = fast
    float wipers_state; //0x0280 (0x04) 0 = off, 0.333 = intermittent, 0.666 = slow, 1 = fast (instant)
    char pad_0284[20]; //0x0284 (0x14)
    uint8_t left_window_moving_direction; //0x0298 (0x01) 1 = got to end down; 2 = got to end up; 16 = down; 32 = up
    uint8_t is_left_window_moving; //0x0299 (0x01) 1 = down auto; 16 = down holding btn; 2 = auto up; 32 = up holding button
    char pad_029A[2]; //0x029A (0x02)
    float left_window_state; //0x029C (0x04) 0 = up; 1 = down
    float left_window_btn; //0x02A0 (0x04) 0 = up; 0.5 off; 1 = down
    float left_window_btn_state; //0x02A4 (0x04) 0 = up; 0.5 off; 1 = down (instant)
    float N00002B28; //0x02A8 (0x04)
    char pad_02AC[4]; //0x02AC (0x04)
    uint8_t right_window_moving_direction; //0x02B0 (0x01) 1 = got to end down; 2 = got to end up; 16 = down; 32 = up
    uint8_t is_right_window_moving; //0x02B1 (0x01) 1 = down auto; 16 = down holding btn; 2 = auto up; 32 = up holding button
    char pad_02B2[2]; //0x02B2 (0x02)
    float right_window_state; //0x02B4 (0x04) 0 = up; 1 = down
    float right_window_btn; //0x02B8 (0x04) 0 = up; 0.5 off; 1 = down
    float right_window_btn_state; //0x02BC (0x04) 0 = up; 0.5 off; 1 = down (instant)
    char pad_02C0[1880]; //0x02C0 (0x758)
    class N00009B3C* N00002C10; //0x0A18 (0x08)
    char pad_0A20[136]; //0x0A20 (0x88)
    class model_object_u* model_object; //0x0AA8 (0x08)
    char pad_0AB0[16]; //0x0AB0 (0x10)
    class physics_gearbox_sequential_u* physics_gearbox_sequential; //0x0AC0 (0x08)
    class physics_gearbox_automatic_u* physics_gearbox_automatic; //0x0AC8 (0x08)
    class physics_gearbox_direct_u* physics_gearbox_direct; //0x0AD0 (0x08)
    char pad_0AD8[8]; //0x0AD8 (0x08)
    class accessory_head_lights_data_u* accessory_head_lights_data; //0x0AE0 (0x08)
    char pad_0AE8[1232]; //0x0AE8 (0x4d0)
    token_t N00002CB4; //0x0FB8 (0x08)
    char pad_0FC0[280]; //0x0FC0 (0x118)


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

static_assert(sizeof(game_actor_u) == 0x10D8);

class sound_t
{
    class sound_player* sound_instance;   // 0x0000 (0x08)
    char pad_0008[0x28];                  // 0x0008 (0x28)
    uint32_t is_playing;                  // 0x0030 (0x04)  1:playing, 4:stop? maybe?
    uint32_t something;                   // 0x0034 (0x04)
    class gl* glsl;                       // 0x0038 (0x08)
    char pad_003c[0x18];                  // 0x0040 (0x18)
    class gl* glsl2;                      // 0x0058 (0x08)
    char* sound_event_name_with_filename; // 0x0060 (0x08)
    char pad_0068[0x50];                  // 0x0068 (0x50)

public:
    uint32_t get_is_playing() const
    {
        return is_playing;
    }

    const char* get_sound_event_name_with_file_name() const
    {
        return sound_event_name_with_filename;
    }
};

class navigation_voice_event
{
    uint32_t pad_0000;               // 0x0000 (0x04)
    uint32_t pad_0004;               // 0x0004 (0x04)
    char* event_name;                // 0x0008 (0x08)
    uint32_t pad_0010;               // 0x0010 (0x04)
    uint32_t pad_0014;               // 0x0014 (0x04)
    class navigation* navi_instance; // 0x0018 (0x08)
    sound_t* sound_instance;         // 0x0020 (0x08)

public:
    sound_t* get_sound_instance() const
    {
        return sound_instance;
    }

    const char* get_event_name() const
    {
        return event_name;
    }
};

class unk_interior // still need to figure out what this actually is
{
    char pad_0000[16]; //0x0000 (0x10)
    char pad_0010[24]; //0x0010 (0x18)
    char pad_0028[208]; //0x0028 (0xd0)
    bool interior_camera; //0x00F8 (0x01) 1 when camera is set to interior even when head out the window
    bool is_camera_inside; //0x00F9 (0x01) 1 if camera is inside, 0 when head through window
    char pad_00FA[2]; //0x00FA (0x02)
    float camera_rotation_in_cabin; //0x00FC (0x04) 0 = head straight, left is -, right is +, maybe different for UK??
    float cabin_out; //0x0100 (0x04)
    char pad_0104[4]; //0x0104 (0x04)
    class fmod_parameter_t* fp_cabin_type; //0x0108 (0x08)
    class fmod_parameter_t* fp_cabin_rot; //0x0110 (0x08)
    class fmod_parameter_t* fp_cabin_out; //0x0118 (0x08)
    vec2s_t window_state; //0x0120 (0x08) 0 = closed, 1 = open
    class fmod_parameter_t* fp_wnd_left; //0x0128 (0x08)
    class fmod_parameter_t* fp_wnd_right; //0x0130 (0x08)
    float daytime; //0x0138 (0x04)
    char pad_013C[4]; //0x013C (0x04)
    class fmod_parameter_t* fp_daytime; //0x0140 (0x08)
    char pad_0148[1624]; //0x0148 (0x658)
    class navigation_voice_event* now_playing_navigation_sound; //0x07A0 (0x08)
    char pad_07A8[88]; //0x07A8 (0x58)
    char pad_0800[32]; //0x0800 (0x20)
    char pad_0820[5144]; //0x0820 (0x1418)
    bool should_have_echo; //0x1C38 (0x01)


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

    navigation_voice_event* get_now_playing_navigation_sound() const
    {
        return now_playing_navigation_sound;
    }
};
#pragma pop
