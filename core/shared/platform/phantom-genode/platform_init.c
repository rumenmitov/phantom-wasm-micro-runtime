#include <ph_malloc.h>
#include <vm/object.h>
#include <vm/internal_da.h>
#include <vm/alloc.h>      // ref_dec
#include <ph_string.h>     // memcpy
#include <kernel/config.h> // NULL

int
bh_platform_init()
{
    return 0;
}

void
bh_platform_destroy()
{
}

// ##############################
// ##########  MALLOC  ##########
// ##############################

extern void
wamr_phantom_alloc_callback(pvm_object_t obj);
extern void
wamr_phantom_free_callback(pvm_object_t obj);

// memory offset from the object beginnng to `data` in binary object. Help keep
// everything 8-byte aligned
#define MEMORY_OFFSET                             \
    ((__offsetof(struct data_area_4_binary, data) \
      + __offsetof(pvm_object_storage_t, da))     \
     % 8)

#define OBJECT_FROM_DATA(data_ptr)                                \
    pvm_da_to_object((void *)((uintptr_t)data_ptr - MEMORY_OFFSET \
                              - __offsetof(struct data_area_4_binary, data)))

void *
os_malloc(unsigned size)
{
    size += MEMORY_OFFSET; // for 8-byte alignment
    // Simplest object to create. Contents are uninitialized
    pvm_object_t object = pvm_create_binary_object(size, NULL);
    wamr_phantom_alloc_callback(object);

    return (void *)((uintptr_t)pvm_data_area(object, binary)->data
                    + MEMORY_OFFSET);
}

static inline void
os_free_internal(pvm_object_t object)
{
    assert(object->_ah.object_start_marker == PVM_OBJECT_START_MARKER);

    wamr_phantom_free_callback(object);
    ref_dec_o(object);
}

// this is pretty much only called for wasm memory enlarge
// TODO: maybe do this some other way?? idk how
void *
os_realloc(void *ptr, unsigned size)
{
    void *new_ptr = os_malloc(size);
    if (ptr == NULL)
        return new_ptr;

    pvm_object_t object = OBJECT_FROM_DATA(ptr);

    ph_memcpy(new_ptr, ptr, object->_da_size);
    os_free_internal(object);

    return new_ptr;
}

void
os_free(void *ptr)
{
    if (ptr == NULL)
        return;

    os_free_internal(OBJECT_FROM_DATA(ptr));
}
