/**
 * @file darray.c
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-07-09
 * 
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 * 
 */

 #include "container/darray.h"

 #include "core/nmemory.h"
 #include "core/logger.h"
 #include "core/asserts.h"

void* _darray_create(u64 length, u64 stride) 
{
    u64 header_size = DARRAY_FIELD_LENGTH * sizeof(u64);
    u64 array_size = length * stride;
    u64* new_array = nallocate(header_size + array_size, MEMORY_TAG_DARRAY);
    nset_memory(new_array, 0, header_size + array_size);

    new_array[DARRAY_CAPACITY] = length;
    new_array[DARRAY_LENGTH] = 0;
    new_array[DARRAY_STRIDE] = stride;

    return (void*)(new_array + DARRAY_FIELD_LENGTH);

}

void _darray_destroy(void* array)
{
    u64* header = (u64*)array - DARRAY_FIELD_LENGTH;
    u64 header_size = DARRAY_FIELD_LENGTH * sizeof(u64);
    u64 total_array_size = header_size + header[DARRAY_CAPACITY] * header[DARRAY_STRIDE];
    nfree(header, total_array_size, MEMORY_TAG_DARRAY);
}

u64 _darray_field_get(void* array, u64 field)
{
    NASSERT_MSG(field < DARRAY_FIELD_LENGTH, "Invalid darray field value.");
    u64* header = (u64*)array - DARRAY_FIELD_LENGTH;
    return header[field];
}

void _darray_field_set(void* array, u64 field, u64 value)
{
    NASSERT_MSG(field < DARRAY_FIELD_LENGTH, "Invalid darray field value.");
    u64* header = (u64*)array - DARRAY_FIELD_LENGTH;
    header[field] = value;
}

void* _darray_resize(void* array)
{
    u64 length = darray_length(array);
    u64 stride = darray_stride(array);

    void* new_array = _darray_create(
        (DARRAY_RESIZE_FACTOR * darray_capacity(array)), 
        stride);
    
    ncopy_memory(new_array, array, length * stride);

    darray_length_set(new_array, length);
    darray_destroy(array);

    return new_array;
}

void* _darray_push(void* array, const void* value_ptr)
{
    u64 length = darray_length(array);
    u64 stride = darray_stride(array);

    if(length >= darray_capacity(array))
    {
        array = _darray_resize(array);
    }

    u64 addr = (u64)array;
    addr += (length * stride);
    ncopy_memory((void*)addr, value_ptr, stride);
    darray_length_set(array, length + 1);

    return array;
}

void _darray_pop(void* array, void* dest)
{
    u64 length = darray_length(array);
    u64 stride = darray_stride(array);
    u64 addr = (u64)array;
    addr += ((length - 1) * stride);
    ncopy_memory(dest, (void*)addr, stride);
    darray_length_set(array, length - 1);
}

void* _darray_pop_at(void* array, u64 index, void* dest)
{
    u64 length = darray_length(array);
    u64 stride = darray_stride(array);
    if(index >=  length)
    {
        NERROR("Index out of bound! Length: %i, index: %d", length, index);
        return array;
    }

    u64 addr = (u64)array;
    ncopy_memory(dest, (void*)(addr + (index * stride)), stride);

    /* if not the last element, adjust the array length, copy it. */
    if(index != length-1)
    {
        ncopy_memory(
            (void*)(addr + (index * stride)),
            (void*)(addr + ((index + 1) * stride)),
            stride * (length - index)
        );
    }

    darray_length_set(array, length - 1);
    return array;
}


void* _darray_insert_at(void* array, u64 index, void* value_ptr)
{
    u64 length = darray_length(array);
    u64 stride = darray_stride(array);

    if(index >=  length)
    {
        NERROR("Index out of bound! Length: %i, index: %d", length, index);
        return array;
    }

    if(length >= darray_capacity(array))
    {
        array = _darray_resize(array);
    }

    u64 addr = (u64)array;

    /* If not the last element, copy the rest outward. */
    if(index != length - 1)
    {
        ncopy_memory(
            (void*)(addr + ((index + 1) * stride)),
            (void*)(addr + (index * stride)),
            stride * (length - index)
        );
    }

    /* set the value at the index. */
    ncopy_memory( 
        (void*)( addr + (index * stride)),
        value_ptr,
        stride
    );

    darray_length_set(array, length + 1);
    return array;
}
