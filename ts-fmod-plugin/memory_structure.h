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

class some_truck_telem_data_t
{
    char pad_0000[248]; //0x0000
    int32_t current_camera;
    //0x00F8 ?? 2 = int, 1 = chase, 7 = top, 5 = roof, 4 = side_back, 3 = hood, 6 = side_front, 9 = cinematic, 0 = dev
    char pad_00FC[8]; //0x00FC
    uint32_t engine_state; //0x0104 0 = engine off, 1 = starting, 2 = running, 3 = shutting down
    char pad_0108[152]; //0x0108
    uint16_t light_state; //0x01A0 6 = parking, 8 = low, 7 = high, 5 = beacons
    char pad_01A2[2]; //0x01A2
    uint16_t additional_illumination; //0x01A4 3 = front, 4 = roof
    char pad_01A6[6]; //0x01A6
    float N000009E5; //0x01AC
    char pad_01B0[4]; //0x01B0
    float wipers_intermittent_time; //0x01B4 Countdown before wipers move again when in intermittent setting
    float wipers_position; //0x01B8 ?? 0 = down start, 1 = down end ???
    float rpm; //0x01BC
    float air_pressure; //0x01C0
    float brake_pressure; //0x01C4
    float max_air_pressure; //0x01C8
    char pad_01CC[8]; //0x01CC
    float oil_temp; //0x01D4
    char pad_01D8[4]; //0x01D8
    float water_temp; //0x01DC
    char pad_01E0[4]; //0x01E0
    float battery_voltage; //0x01E4
    char pad_01E8[8]; //0x01E8
    float turbo_pressure; //0x01F0
    char pad_01F4[12]; //0x01F4
    float light_switch; //0x0200 0 = off, 0.5 = parking, 1 = low beam
    float light_switch_state; //0x0204 0 = off, 0.5 = parking, 1 = low beam (instant)
    float high_beam_stick; //0x0208 1 = on, 0 = off
    float high_beam; //0x020C 1 = on, 0 = off (instant)
    float light_horn_stick; //0x0210 0 = off, 1 = on
    float light_horn_state; //0x0214 0 = off, 1 = on (instant)
    float indicator_stick; //0x0218 0 = left indicator, 0.5 = none, 1 = right
    float indicator; //0x021C 0 = left indicator, 0.5 = none, 1 = right (instant)
    float hazard_warning_btn; //0x0220 1 = on, 0 = off
    float hazard_warning_state; //0x0224 1 = on, 0 = off (instant)
    float beacon_switch; //0x0228 0 = off, 1 = on
    float beacon_state; //0x022C 0 = off, 1 = on (instant)
    char pad_0230[8]; //0x0230
    float handbrake_handle; //0x0238 1 = handbrake on, 0 = off
    float handbrake; //0x023C 1 = handbrake on, 0 = off (instant)
    char pad_0240[8]; //0x0240
    float engine_brake_stick; //0x0248 0 = off, 1 = full; steps dependant on engine data
    float engine_brake; //0x024C 0 = off, 1 = full (instant); steps dependant on engine data
    char pad_0250[20]; //0x0250
    float wipers_stick_state; //0x0264 0 = off, 0.333 = intermittent, 0.666 = slow, 1 = fast
    float wipers_state; //0x0268 0 = off, 0.333 = intermittent, 0.666 = slow, 1 = fast (instant)
    char pad_026C[1956]; //0x026C
    float effective_brake; //0x0A10 0 = none, 1 = max
    char pad_0A14[8]; //0x0A14
    float effective_steering; //0x0A1C 1 = left, -1 = right
    char pad_0A20[64]; //0x0A20
    uint32_t steering_wheel; //0x0A60 0 = steering wheel = left, 512 = center, 1023 = right

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
        return engine_brake;
    }
};

class unk_cabin_t
{
    char pad_0000[24]; //0x0000
    float cabin_out; //0x0018
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

class truck_telem_data_parent_t
{
    char pad_0000[176]; //0x0000
    char* current_timezone; //0x00B0
    char pad_00B8[4120]; //0x00B8
    some_truck_telem_data_t* some_truck_telem_data; //0x10D0

public:
    some_truck_telem_data_t* get_truck_telem_data() const
    {
        return some_truck_telem_data;
    }
};


class economy_base_t
{
    unk_interior* unk_interior_parent; //0x0000
    truck_telem_data_parent_t* truck_telem_data_parent_ptr; //0x0008

public:
    unk_interior* get_unk_interior_parent() const
    {
        return unk_interior_parent;
    }

    truck_telem_data_parent_t* get_truck_telem_parent() const
    {
        return truck_telem_data_parent_ptr;
    }
};
