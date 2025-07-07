#pragma once
#include <cstdint>

#pragma pack( push, 1 )
namespace ts_fmod_plugin::prism
{
    // Some of this is a pure guess, but it does seem to work

    template < class T > class list_dyn_node_t
    {
    public:
        list_dyn_node_t< T >* next;
        list_dyn_node_t< T >* prev;
        T item;
    };

    template < class T > class list_dyn_t // Size: 0x0038
    {
    public:
        uint64_t size;                                          // 0x0008 (0x08)
        list_dyn_node_t< T >* begin;                            // 0x0010 (0x08)
        list_dyn_node_t< T >* end;                              // 0x0018 (0x08)
        T* empty_item;                                          // 0x0020 (0x08)
        uint64_t capacity;                                      // 0x0028 (0x08)
        char pad_0030[ 8 ];                                     // 0x0030 (0x08)
        array_dyn_t< class allocator_node_t* > allocator_nodes; // 0x0038 (0x20)

        virtual void destructor();
    };
    static_assert( sizeof( list_dyn_t< void* > ) == 0x58 );
}
#pragma pack( pop )
