#pragma once
#include "./array_dyn.h"
#include <cstdint>

namespace ts_fmod_plugin::prism
{
#pragma pack( push, 1 )

    // Some of this is a pure guess, but it does seem to work (as long as T is a ptr)

    template < class T > class list_dyn_node_t
    {
    public:
        list_dyn_node_t< T >* next;
        list_dyn_node_t< T >* prev;
        T item;
    };

    // Size: W 0x0070, L|A 0x0058 1.60
    template < class T > class list_dyn_t
    {
    public:
        uint64_t size;               // 0x0008 (0x08)
        list_dyn_node_t< T >* begin; // 0x0010 (0x08)
        list_dyn_node_t< T >* end;   // 0x0018 (0x08)
#if defined( _WIN32 )
        void* allocator1; // W 0x0020 (W 0x08)
        void* allocator2; // W 0x0028 (W 0x08)
#endif
        T empty_item;                                           // W 0x0030, L|A 0x0020 (W|L|A 0x08)
        uint64_t capacity;                                      // W 0x0038, L|A 0x0028 (W|L|A 0x08)
        char pad_0030[ 8 ];                                     // W 0x0040, L|A 0x0030 (W|L|A 0x08)
        array_dyn_t< class allocator_node_t* > allocator_nodes; // W 0x0048, L|A 0x0038 (W 0x28, L|A 0x20)

        virtual void destructor();
    };

#if defined( _WIN32 )
    static_assert( sizeof( list_dyn_t< void* > ) == 0x70, "list_dyn_t is incorrect in size" ); // W
#elif defined( __linux__ ) || defined( __APPLE__ )
    static_assert( sizeof( list_dyn_t< void* > ) == 0x58, "list_dyn_t is incorrect in size" ); // L|A
#endif
#pragma pack( pop )
} // namespace ets2la_plugin::prism
