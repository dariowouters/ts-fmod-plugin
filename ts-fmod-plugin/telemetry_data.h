#pragma once


struct telemetry_data_t
{
    bool engine_enabled;
    float rpm;

    float effective_throttle;
    bool engine_brake;
    bool park_brake_on;
    bool brake_air_pressure_warning;
    uint32_t retarder_level;

    bool lblinker;
    bool rblinker;
    bool light_lblinker;
    bool light_rblinker;

    scs_value_fplacement_t head_offset;
};