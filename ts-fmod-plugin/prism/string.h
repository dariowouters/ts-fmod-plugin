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

    // Size: W 0x0020, L|A 0x0018 1.60
    class string_dyn_t
    {
    public:
        string str;        // W|L|A 0x0008 (W|L|A 0x08)
        uint32_t size;     // W|L|A 0x0010 (W|L|A 0x04)
        uint32_t capacity; // W|L|A 0x0014 (W|L|A 0x04)

#if defined( _WIN32 )
        void* allocator; // W 0x0018 (W 0x08)
#endif

        virtual void destructor();
    };

#if defined( _WIN32 )
    static_assert( sizeof( string_dyn_t ) == 0x020, "string_dyn_t is incorrect in size" );
#elif defined( __linux__ ) || defined( __APPLE__ )
    static_assert( sizeof( string_dyn_t ) == 0x018, "string_dyn_t is incorrect in size" );
#endif
}
#pragma pack( pop )
