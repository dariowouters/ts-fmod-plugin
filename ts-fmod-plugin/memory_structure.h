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
    char pad_0000[228]; //0x0000
    int32_t current_camera; //0x00E4 ?? 2 = int, 1 = chase, 7 = top, 5 = roof, 4 = side_back, 3 = hood, 6 = side_front, 9 = cinematic, 0 = dev
    char pad_00E8[8]; //0x00E8
    uint32_t engine_state; //0x00F0 0 = engine off, 1 = starting, 2 = running, 3 = shutting down
    char pad_00F4[116]; //0x00F4
    uint16_t light_state; //0x0168 6 = parking, 8 = low, 7 = high, 5 = beacons
    char pad_016A[2]; //0x016A
    uint16_t additional_illumination; //0x016C 3 = front, 4 = roof
    char pad_016E[6]; //0x016E
    float N000009E5; //0x0174
    char pad_0178[4]; //0x0178
    float wipers_intermittent_time; //0x017C Countdown before wipers move again when in intermittent setting
    float wipers_position; //0x0180 ?? 0 = down start, 1 = down end ???
    float rpm; //0x0184
    float air_pressure; //0x0188
    float brake_pressure; //0x018C
    float max_air_pressure; //0x0190
    char pad_0194[8]; //0x0194
    float oil_temp; //0x019C
    char pad_01A0[4]; //0x01A0
    float water_temp; //0x01A4
    char pad_01A8[4]; //0x01A8
    float battery_voltage; //0x01AC
    char pad_01B0[8]; //0x01B0
    float turbo_pressure; //0x01B8
    char pad_01BC[12]; //0x01BC
    float light_switch; //0x01C8 0 = off, 0.5 = parking, 1 = low beam
    float light_switch_state; //0x01CC 0 = off, 0.5 = parking, 1 = low beam (instant)
    float high_beam_stick; //0x01D0 1 = on, 0 = off
    float high_beam; //0x01D4 1 = on, 0 = off (instant)
    float light_horn_stick; //0x01D8 0 = off, 1 = on
    float light_horn_state; //0x01DC 0 = off, 1 = on (instant)
    float indicator_stick; //0x01E0 0 = left indicator, 0.5 = none, 1 = right
    float indicator; //0x01E4 0 = left indicator, 0.5 = none, 1 = right (instant)
    float hazard_warning_btn; //0x01E8 1 = on, 0 = off
    float hazard_warning_state; //0x01EC 1 = on, 0 = off (instant)
    char pad_01F0[16]; //0x01F0
    float handbrake_handle; //0x0200 1 = handbrake on, 0 = off
    float handbrake; //0x0204 1 = handbrake on, 0 = off (instant)
    char pad_0208[8]; //0x0208
    float engine_brake_stick; //0x0210 0 = off, 1 = full; steps dependant on engine data
    float engine_brake; //0x0214 0 = off, 1 = full (instant); steps dependant on engine data
    char pad_0218[20]; //0x0218
    float wipers_stick_state; //0x022C 0 = off, 0.333 = intermittent, 0.666 = slow, 1 = fast
    float wipers_state; //0x0230 0 = off, 0.333 = intermittent, 0.666 = slow, 1 = fast (instant)
    char pad_0234[1824]; //0x0234
    float rpm2_old; //0x0954
    float turbo_pressure2_old; //0x0958
    char pad_095C[16]; //0x095C
    float effective_brake; //0x096C 0 = none, 1 = max
    char pad_0970[4]; //0x0970
    float effective_steering; //0x0974 1 = left, -1 = right
    char pad_0978[68]; //0x0978
    uint32_t steering_wheel; //0x09BC 0 = steering wheel = left, 512 = center, 1023 = right


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

class unk_interior // still need to figure out what this actually is
{
    char pad_0000[184]; //0x0000
    bool interior_camera; //0x00B8 1 when camera is set to interior even when head out the window
    bool is_camera_inside; //0x00B9 1 if camera is inside, 0 when head through window
    char pad_00BA[2]; //0x00BA
    float camera_rotation_in_cabin; //0x00BC 0 = head straight, left is -, right is +, maybe different for UK??
    int32_t should_have_echo_old; //0x00C0
    char pad_00C4[12]; //0x00C4
    class N00000C84 *N0000432E; //0x00D0
    vec2s_t window_state; //0x00D8 0 = closed, 1 = open
    char pad_00E0[6920]; //0x00E0
    uint8_t should_have_echo; //0x1BE8

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
};

class truck_telem_data_parent_t
{
    char pad_0000[4336]; //0x0000
    some_truck_telem_data_t *some_truck_telem_data; //0x10F0
public:
    some_truck_telem_data_t* get_truck_telem_data() const
    {
        return some_truck_telem_data;
    }
};

class truck_telem_data_parent_parent_t
{
    char pad_0000[2512]; //0x0000
    truck_telem_data_parent_t *truck_telem_data_parent_ptr; //0x09D0
public:
    truck_telem_data_parent_t* get_truck_telem_parent() const
    {
        return truck_telem_data_parent_ptr;
    }
};


class economy_base_t
{
    unk_interior *unk_interior_parent; //0x0000
    char pad_0008[32]; //0x0008
    truck_telem_data_parent_parent_t *truck_telem_data_parent_parent_ptr; //0x0028


public:
    unk_interior* get_unk_interior_parent() const
    {
        return unk_interior_parent;
    }
    truck_telem_data_parent_parent_t* get_truck_telem_parent_parent() const
    {
        return truck_telem_data_parent_parent_ptr;
    }
};

