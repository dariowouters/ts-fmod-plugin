#pragma once
#include "./array.h"
#include <cstdint>

#pragma pack( push, 1 )
namespace ts_fmod_plugin::prism
{
    template < class T > class array_dyn_t : public array_t< T >
    {
    public:
        uint64_t capacity;
    };

    static_assert( sizeof( array_dyn_t< void* > ) == 0x20, "array_dyn_t is incorrect in size" );
}
#pragma pack( pop )
