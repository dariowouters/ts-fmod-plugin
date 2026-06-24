#pragma once
#include "./array.h"
#include <cstdint>

#pragma pack( push, 1 )
namespace ts_fmod_plugin::prism
{
    // Size: W 0x0028, L|A 0x0020 1.60
    template < class T > class array_dyn_t : public array_t< T >
    {
    public:
        uint64_t capacity; // W|L|A 0x0018 (W|L|A 0x08)
#if defined( _WIN32 )
        void* allocator; // W 0x0020 (W 0x08)
#endif
    };

#if defined( _WIN32 )
    static_assert( sizeof( array_dyn_t< uint32_t > ) == 0x28 ); // W
#elif defined( __linux__ ) || defined( __APPLE__ )
    static_assert( sizeof( array_dyn_t< uint32_t > ) == 0x20 ); // L|A
#endif
}
#pragma pack( pop )
