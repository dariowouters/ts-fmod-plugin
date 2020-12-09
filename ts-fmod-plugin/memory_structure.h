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
    char pad_0000[224]; //0x0000
    uint32_t engine_state; //0x00E0 0 = engine off, 1 = starting, 2 = running, 3 = shutting down
    char pad_00E4[104]; //0x00E4
    uint16_t light_state; //0x014C 6 = parking, 8 = low, 7 = high, 5 = beacons
    char pad_014E[2]; //0x014E
    uint16_t additional_illumination; //0x0150 3 = front, 4 = roof
    char pad_0152[22]; //0x0152
    float rpm; //0x0168
    float air_pressure; //0x016C
    float brake_pressure; //0x0170
    float max_air_pressure; //0x0174
    char pad_0178[8]; //0x0178
    float oil_temp; //0x0180
    char pad_0184[4]; //0x0184
    float water_temp; //0x0188
    char pad_018C[4]; //0x018C
    float battery_voltage; //0x0190
    char pad_0194[8]; //0x0194
    float turbo_pressure; //0x019C
    char pad_01A0[12]; //0x01A0
    float light_switch; //0x01AC 0 = off, 0.5 = parking, 1 = low beam
    float light_switch_state; //0x01B0 0 = off, 0.5 = parking, 1 = low beam (instant)
    float high_beam_stick; //0x01B4 1 = on, 0 = off
    float high_beam; //0x01B8 1 = on, 0 = off (instant)
    float light_horn_stick; //0x01BC 0 = off, 1 = on
    float light_horn_state; //0x01C0 0 = off, 1 = on (instant)
    float indicator_stick; //0x01C4 0 = left indicator, 0.5 = none, 1 = right
    float indicator; //0x01C8 0 = left indicator, 0.5 = none, 1 = right (instant)
    float hazard_warning_btn; //0x01CC 1 = on, 0 = off
    float hazard_warning_state; //0x01D0 1 = on, 0 = off (instant)
    char pad_01D4[16]; //0x01D4
    float handbrake_handle; //0x01E4 1 = handbrake on, 0 = off
    float handbrake; //0x01E8 1 = handbrake on, 0 = off (instant)
    char pad_01EC[36]; //0x01EC
    float wipers_stick_state; //0x0210 0 = off, 0.333 = intermittent, 0.666 = slow, 1 = fast
    float wipers_state; //0x0214 0 = off, 0.333 = intermittent, 0.666 = slow, 1 = fast (instant)
    char pad_0218[1816]; //0x0218
    float rpm2; //0x0930
    float turbo_pressure2; //0x0934
    char pad_0938[16]; //0x0938
    float effective_brake; //0x0948 0 = none, 1 = max
    char pad_094C[4]; //0x094C
    float effective_steering; //0x0950 1 = left, -1 = right
    char pad_0954[68]; //0x0954
    uint32_t steering_wheel; //0x0998 0 = steering wheel = left, 512 = center, 1024 = right

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
};

class some_truck_telem_data_parent_t
{
    char pad_0000[0x170]; //0x0000
    some_truck_telem_data_t* some_truck_telem_data; // 0x00170
public:
    some_truck_telem_data_t* get_some_truck_telem_data() const
    {
        return some_truck_telem_data;
    }
};

class some_arr_ptr_t
{
// actually an array but whatever, hopefully it's always the first element
    some_truck_telem_data_parent_t* some_truck_telem_data_parent;
public:
    some_truck_telem_data_parent_t* get_some_truck_telem_data_parent() const
    {
        return some_truck_telem_data_parent;
    }
};

class unk_t
{
    char pad_0000[0x38]; //0x0000
    some_arr_ptr_t* some_arr_ptr; // 0x0038
    uint64_t arr_size; // 0x0040
public:
    some_arr_ptr_t* get_some_arr_ptr() const
    {
        if (arr_size == 0) return nullptr;
        return some_arr_ptr;
    }
};

class unk_window // still need to figure out what this actually is
{
    char pad_0000[176]; //0x0000
    bool interior_camera; //0x00B0 1 when camera is set to interior even when head out the window??
    bool is_camera_inside; //0x00B1 1 if camera is inside, 0 when head through window??
    char pad_00B2[2]; //0x00B2
    float camera_rotation_in_cabin; //0x00B4 0 = head straight, left is -, right is +, maybe different for UK??
    bool should_have_echo; //0x00B8
    char pad_00BC[28]; //0x00BC
    class N00000C84 *N0000432E; //0x00D8
    vec2s_t window_state; //0x00E0 0 = closed, 1 = open

public:
    bool get_has_echo() const
    {
        return should_have_echo;
    }
    vec2s_t get_window_state() const
    {
        return window_state;
    }
};

class economy_base_t
{
    char pad_0000[0x8]; //0x0008
    unk_window* unk_window_parent; //0x008
    char pad_0010[0x208]; //0x0010
    unk_t* unk; // 0x00218 Seems to change every (major?) version, TODO: Find a better/more consistent way
public:
    unk_t* get_unk() const
    {
        return unk;
    }
    unk_window* get_unk_window_parent() const
    {
        return unk_window_parent;
    }
};
