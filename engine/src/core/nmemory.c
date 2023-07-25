/**
 * @file nmemory.c
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief
 * @version 1.0
 * @date 2023-04-18
 *
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 *
 */

#include "nmemory.h"

#include "core/logger.h"
#include "core/asserts.h"
#include "platform/platform.h"

// TODO: custom string lib.
#include <string.h>
#include <stdio.h>

typedef struct memory_stats
{
    u64 total_allocated;
    u64 tagged_allocations[MEMORY_TAG_MAX_TAGS];
} memory_stats;

static const char* memory_tag_strings[MEMORY_TAG_MAX_TAGS] = {
    "UNKNOWN    ",
    "ARRAY      ",
    "DARRAY     ",
    "DICT       ",
    "RING_QUEUE ",
    "BST        ",
    "STRING     ",
    "APPLICATION",
    "JOB        ",
    "TEXTURE    ",
    "MAT_INST   ",
    "RENDERER   ",
    "GAME       ",
    "TRANSFORM  ",
    "ENTITY     ",
    "ENTITY_NODE",
    "SCENE      " };

static memory_stats stats;

void initialize_memory()
{
    platform_zero_memory(&stats, sizeof(stats));
}

void shutdown_memory()
{
}

void* nallocate(u64 size, memory_tag m_tag)
{
    if (m_tag == MEMORY_TAG_UNKNOWN)
    {
        NWARN("nallocatte called using MEMORY_TAG_UNKNOWN. re-class this allocation.");
    }

    stats.total_allocated += size;
    stats.tagged_allocations[m_tag] += size;

    // TODO: memory allignment.
    void* memory_block = platform_allocate(size, FALSE);
    NASSERT(memory_block);
    platform_zero_memory(memory_block, size);
    return memory_block;
}

void nfree(void* block, u64 size, memory_tag m_tag)
{
    if (m_tag == MEMORY_TAG_UNKNOWN)
    {
        NWARN("nfree called using MEMORY_TAG_UNKNOWN. re-class this allocation.");
    }

    stats.total_allocated -= size;
    stats.tagged_allocations[m_tag] -= size;

    // TODO: memory allignment.
    platform_free(block, FALSE);
}

void* nzero_memory(void* block, u64 size)
{
    return platform_zero_memory(block, size);
}

void* ncopy_memory(void* dest, const void* src, u64 size)
{
    return platform_copy_memory(dest, src, size);
}

void* nset_memory(void* dest, i32 value, u64 size)
{
    return platform_set_memory(dest, value, size);
}

char* get_memory_usage_str()
{
    const u64 gib = 1024 * 1024 * 1024;
    const u64 mib = 1024 * 1024;
    const u64 kib = 1024;

    /* 8 kb buffer size should be enough for printing all the memory statistics. */
    const u32 buffer_size = 8192;
    char buffer[buffer_size] = "System Memory Usage(tagged):\n";
    u64 offset = strlen(buffer);
    for (u32 i = 0; i < MEMORY_TAG_MAX_TAGS; ++i)
    {
        char unit[4] = "Xib";
        f32 amount = 1.0f; // FIXME: why...?
        if (stats.tagged_allocations[i] >= gib)
        {
            unit[0] = 'G';
            amount = (f32)stats.tagged_allocations[i] / (f32)gib;
        }
        else if (stats.tagged_allocations[i] >= mib)
        {
            unit[0] = 'M';
            amount = (f32)stats.tagged_allocations[i] / (f32)mib;
        }
        else if (stats.tagged_allocations[i] >= kib)
        {
            unit[0] = 'K';
            amount = (f32)stats.tagged_allocations[i] / (f32)kib;
        }
        else
        {
            unit[0] = 'B';
            unit[1] = 0;
            amount = (f32)stats.tagged_allocations[i];
        }

        i32 length = snprintf(buffer + offset, buffer_size, "  %s: %.2f %s\n", memory_tag_strings[i], amount, unit);
        offset += length;
    }

    char* out_string = strdup(buffer);
    return out_string;
}
