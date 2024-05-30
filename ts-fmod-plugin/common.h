#pragma once

namespace common
{
    inline const char* plugin_version = "1.50";
    constexpr uint32_t supported_game_version = 50;

    inline FMOD_GUID get_guid(const std::string& s_guid)
    {
        FMOD_GUID guid;
        sscanf_s(s_guid.c_str(),
                 "{%8x-%4hx-%4hx-%2hhx%2hhx-%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx}",
                 &guid.Data1,
                 &guid.Data2,
                 &guid.Data3,
                 &guid.Data4[0],
                 &guid.Data4[1],
                 &guid.Data4[2],
                 &guid.Data4[3],
                 &guid.Data4[4],
                 &guid.Data4[5],
                 &guid.Data4[6],
                 &guid.Data4[7]);

        return guid;
    }

    inline bool cmpf(const float a, const float b, const float epsilon = 0.005f)
    {
        return (fabs(a - b) < epsilon);
    }
}
