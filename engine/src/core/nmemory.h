/**
 * @file nmemory.h
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief
 * @version 1.0
 * @date 2023-04-18
 *
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 *
 */

#pragma once

#include "defines.h"

/**
 * @brief Tag for allocated memory types.
 *
 */
typedef enum memory_tag
{
    /* For temporary use. Should be assigned one of the them or get new created.
     */
    MEMORY_TAG_UNKNOWN,
    MEMORY_TAG_ARRAY,
    MEMORY_TAG_DARRAY,
    MEMORY_TAG_DICT,
    MEMORY_TAG_RING_QUEUE,
    MEMORY_TAG_BST,
    MEMORY_TAG_STRING,
    MEMORY_TAG_APPLICATION,
    MEMORY_TAG_JOB,
    MEMORY_TAG_TEXTURE,
    MEMORY_TAG_MATERIAL_INSTANCE,
    MEMORY_TAG_RENDERER,
    MEMORY_TAG_GAME,
    MEMORY_TAG_TRANSFORM,
    MEMORY_TAG_ENTITY,
    MEMORY_TAG_ENTITY_NODE,
    MEMORY_TAG_SCENEN,

    MEMORY_TAG_MAX_TAGS
} memory_tag;

/**
 * @brief Initializes the memory subsystem.
 *
 * @return void
 */
NAPI void initialize_memory();

/**
 * @brief clean up and shutdown the memory subsystem.
 *
 * @return void
 */
NAPI void shutdown_memory();

/**
 * @brief allocates a new memory from the memory subsystem.
 *
 * @param size size in bytes for the new memory chunk.
 * @param m_tag memory tag.
 * @return pointer to the new memory chunk.
 */
NAPI void *nallocate(u64 size, memory_tag m_tag);

/**
 * @brief frees a memory chunk from the memory subsystem.
 *
 * @param block pointer to the memory chunk to free.
 * @param size size in bytes for the memory chunk.
 * @param m_tag memory tag.
 * @return void
 */
NAPI void nfree(void *block, u64 size, memory_tag m_tag);

/**
 * @brief
 *
 * @param block
 * @param size
 * @return NAPI*
 */
NAPI void *nzero_memory(void *block, u64 size);

/**
 * @brief copies memory from source to destination of specified size.
 *
 * @param dest pointer to destination.
 * @param src pointer to source.
 * @param size size in bytes for copying.
 * @return pointer to the copied memory.
 */
NAPI void *ncopy_memory(void *dest, const void *src, u64 size);

/**
 * @brief set the memory value to the specified value.
 *
 * @param dest pointer to destination.
 * @param value value to set.
 * @param size size in bytes.
 * @return pointer to the new memory value.
 */
NAPI void *nset_memory(void *dest, i32 value, u64 size);

/**
 * @brief Get the memory usage str.
 *
 * @return void
 */
NAPI char *get_memory_usage_str();
