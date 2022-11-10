#pragma once

struct vec2s_t
{
public:
    float x;
    float y;
};

struct vec3s_t
{
public:
    float x;
    float y;
    float z;
};


class game_actor_u
{
public:
    char pad_0010[24];                                  //0x0000
    class game_physics_vehicle_u* game_physics_vehicle; //0x0018
    class visual_interior_u* visual_interior;           //0x0020
    class game_actor_hud_u* game_actor_hud;             //0x0028
    char pad_0030[128];                                 //0x0030
    class game_trailer_actor_u* game_trailer_actor;     //0x00B0
    char pad_00B8[64];                                  //0x00B8
    uint32_t current_camera;
    //0x00F8 2 = int, 1 = chase, 7 = top, 5 = roof, 4 = side_back, 3 = hood, 6 = side_front, 9 = cinematic, 0 = dev
    char pad_00FC[8];                 //0x00FC
    uint32_t engine_state;            //0x0104 0 = engine off, 1 = starting, 2 = running, 3 = shutting down
    char pad_0108[72];                //0x0108
    float speed_limiter;              //0x0150
    float road_speed_limit;           //0x0154
    char pad_0158[80];                //0x0158
    uint16_t light_state;             //0x01A8 (flags) 6 = parking, 8 = low, 7 = high, 5 = beacons
    char pad_01AA[2];                 //0x01AA
    uint16_t additional_illumination; //0x01AC (flags) 3 = front, 4 = roof
    char pad_01AE[14];                //0x01AE
    float wipers_intermittent_time;   //0x01BC Countdown before wipers move again when in intermittent setting
    float wipers_position;            //0x01C0 0 = down start, 1 = down end ???
    float rpm;                        //0x01C4
    float air_pressure;               //0x01C8
    float brake_pressure;             //0x01CC
    float max_air_pressure;           //0x01D0
    char pad_01D4[8];                 //0x01D4
    float oil_temp;                   //0x01DC
    char pad_01E0[4];                 //0x01E0
    float water_temp;                 //0x01E4
    char pad_01E8[4];                 //0x01E8
    float battery_voltage;            //0x01EC
    char pad_01F0[8];                 //0x01F0
    float turbo_pressure;             //0x01F8 ?
    char pad_01FC[12];                //0x01FC
    float light_switch;               //0x0208 0 = off, 0.5 = parking, 1 = low beam
    float light_switch_state;         //0x020C 0 = off, 0.5 = parking, 1 = low beam (instant)
    float high_beam_stick;            //0x0210 0 = off, 1 = on
    float high_beam_state;            //0x0214 0 = off, 1 = on (instant)
    float light_horn_stick;           //0x0218 0 = off, 1 = on
    float light_horn_state;           //0x021C 0 = off, 1 = on (instant)
    float indicator_stick;            //0x0220 0 = left indicator, 0.5 = none, 1 = right
    float indicator_state;            //0x0224 0 = left indicator, 0.5 = none, 1 = right (instant)
    float hazard_warning_btn;         //0x0228 0 = off, 1 = on
    float hazard_warning_state;       //0x022C 0 = off, 1 = on (instant)
    float beacon_switch;              //0x0230 0 = off, 1 = on
    float beacon_state;               //0x0234 0 = off, 1 = on (instant)
    char pad_0238[8];                 //0x0238
    float handbrake_handle;           //0x0240 0 = off, 1 = on
    float handbrake_state;            //0x0244 0 = off, 1 = on (instant)
    char pad_0248[8];                 //0x0248
    float engine_brake_stick;         //0x0250 0 = off, 1 = full; steps dependant on engine data
    float engine_brake_state;         //0x0254 0 = off, 1 = full (instant); steps dependant on engine data
    char pad_0258[20];                //0x0258
    float wipers_stick;               //0x026C 0 = off, 0.333 = intermittent, 0.666 = slow, 1 = fast
    float wipers_state;               //0x0270 0 = off, 0.333 = intermittent, 0.666 = slow, 1 = fast (instant)


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

class unk_cabin_t
{
    char pad_0000[24];  //0x0000
    float cabin_out;    //0x0018
    char pad_001C[108]; //0x001C

public:
    float get_cabin_out() const
    {
        return cabin_out;
    }
};

class unk_interior // still need to figure out what this actually is
{
    char pad_0000[184]; //0x0000
    bool interior_camera; //0x00B8 1 when camera is set to interior even when head out the window
    bool is_camera_inside; //0x00B9 1 if camera is inside, 0 when head through window
    char pad_00BA[2]; //0x00BA
    float camera_rotation_in_cabin; //0x00BC 0 = head straight, left is -, right is +, maybe different for UK??
    char pad_00C0[24]; //0x00C0
    unk_cabin_t* unk_cabin_ptr; //0x00D8
    vec2s_t window_state; //0x00E0 0 = closed, 1 = open
    char pad_00E8[1752]; //0x00E8
    class navigation_sound_events_arr* navigation_sound_events; //0x07C0
    int64_t navigation_sound_events_count; //0x07C8
    char pad_07D0[5152]; //0x07D0
    bool should_have_echo; //0x1BF0


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

    unk_cabin_t* get_unk_cabin() const
    {
        return unk_cabin_ptr;
    }
};

class game_ctrl_u
{
    char pad_0000[176];       //0x0000
    char* current_timezone;   //0x00B0
    char pad_00B8[4192];      //0x00B8
    game_actor_u* game_actor; //0x1118

public:
    game_actor_u* get_game_actor() const
    {
        return game_actor;
    }
};


class economy_base_t
{
    unk_interior* unk_interior_parent; //0x0000
    game_ctrl_u* game_ctrl;            //0x0008

public:
    unk_interior* get_unk_interior_parent() const
    {
        return unk_interior_parent;
    }

    game_ctrl_u* get_game_ctrl() const
    {
        return game_ctrl;
    }
};
