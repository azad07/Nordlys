/**
 * @file renderer_backend.c
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief
 * @version 1.0
 * @date 2023-08-13
 *
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 *
 */

#include "renderer_backend.h"

#include "vulkan/vulkan_backend.h"

b8 renderer_backend_create(renderer_backend_type type, struct platform_state* plat_state, renderer_backend* out_renderer_backend)
{
    out_renderer_backend->plat_state = plat_state;

    if (type == RENDERER_BACKEND_TYPE_VULKAN)
    {
        out_renderer_backend->initialize = vulkan_renderer_backend_initialize;
        out_renderer_backend->shutdown = vulkan_renderer_backend_shutdown;
        out_renderer_backend->begin_frame = vulkan_renderer_backend_begin_frame;
        out_renderer_backend->end_frame = vulkan_renderer_backend_end_frame;
        out_renderer_backend->resized = vulkan_renderer_backend_on_resized;
        
        return TRUE;
    }

    return FALSE;
}

void renderer_backend_destroy(renderer_backend* renderer_backend)
{
    if (renderer_backend != NULL)
    {
        renderer_backend->initialize = NULL;
        renderer_backend->shutdown = NULL;
        renderer_backend->resized = NULL;
        renderer_backend->begin_frame = NULL;
        renderer_backend->end_frame = NULL;
        
        renderer_backend->plat_state = NULL;
    }
}