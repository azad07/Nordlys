/**
 * @file nstring.c
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief
 * @version 1.0
 * @date 2023-08-30
 *
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 *
 */

#include "core/nstring.h"

#include "core/nmemory.h"
#include "core/asserts.h"

/* TODO: use system stings for now, will implement it later. */
#include <string.h>

u64 string_length(const char* str)
{
    return strlen(str);
}

char* string_duplicate(const char* str)
{
    NASSERT(str != NULL);
    
    u64 length = string_length(str);
    char* str_dup = (char*)nallocate(length + 1, MEMORY_TAG_STRING);
    ncopy_memory(str_dup, str, length + 1);
    return str_dup;
}

b8 strings_equal(const char* str1, const char* str2)
{
    return (strcmp(str1, str2) == 0);
}