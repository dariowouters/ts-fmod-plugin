#pragma once
#include <cstdint>

#pragma pack( push, 1 )
namespace ts_fmod_plugin::prism
{
    struct string
    {
        explicit string( const char* const s ) : m_string( s ) {}

        const char* m_string = nullptr;
    };

    static_assert( sizeof( string ) == 0x08, "string is incorrect in size" );

    class string_dyn_t
    {
    public:
        string str;
        uint32_t size;
        uint32_t capacity;

        virtual void destructor();
    };

    static_assert( sizeof( string_dyn_t ) == 0x018, "string_dyn_t is incorrect in size" );
}
#pragma pack( pop )
