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
    char pad_0000[0xE0]; //0x0000
    uint32_t engine_state; //0x00E0 0 = engine off, 1 = starting, 2 = running, 3 = shutting down
    char pad_00E4[0xB8]; //0x00E4
    float turbo_pressure; // 0x0019C
public:
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
