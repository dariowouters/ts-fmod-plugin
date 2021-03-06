#pragma once


struct telemetry_data_t
{
    bool engine_enabled;
    float rpm;

    int gear;

    float effective_throttle;
    float effective_clutch;
    bool engine_brake;
    bool park_brake_on;
    bool brake_air_pressure_warning;
    uint32_t retarder_level;

    bool lblinker;
    bool rblinker;
    bool light_lblinker;
    bool light_rblinker;

    bool high_beam;
    bool wipers;

    scs_value_fplacement_t head_offset;
};