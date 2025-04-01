#pragma once
#include <cstdint>

#pragma pack( push, 1 )
namespace ts_fmod_plugin::prism
{
    template < class T > class array_t
    {
    public:
        T* value;
        uint64_t size;

    public:
        T& at( uint64_t index ) { return value[ index ]; }

        T& operator[]( const uint64_t index ) { return value[ index ]; }

        T* begin() { return &value[ 0 ]; }
        T* end() { return &value[ size ]; }

    private:
        virtual void destructor();
    };

    static_assert( sizeof( array_t< uint64_t > ) == 0x18, "array_t is incorrect in size" );
}

#pragma pack( pop )
