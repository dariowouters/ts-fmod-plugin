#pragma once
#include "./array.h"
#include <cstdint>

#pragma pack( push, 1 )
namespace ts_fmod_plugin::prism
{
    template < class T, uint64_t S >
    class array_local_t : public array_t< T >
    {
    public:
        uint64_t capacity;

    private:
        T _items[ S ];
    };

    static_assert( sizeof( array_local_t< void*, 5 > ) == 0x48, "array_local_t is incorrect in size" );
}
#pragma pack( pop )
