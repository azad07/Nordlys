/**
 * @file renderer_forntend.c
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief
 * @version 1.0
 * @date 2023-08-09
 *
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 *
 */

#include "renderer_forntend.h"

#include "renderer_backend.h"
#include "core/logger.h"
#include "core/nmemory.h"
#include "vulkan/vulkan_backend.h"

/* backend renderer backend.
 * TODO: support for more than one backend.
 */
struct renderer_backend* backend = NULL;

b8 renderer_initialize(const char* application_name, struct platform_state* plat_state)
{
    backend = nallocate(sizeof(renderer_backend), MEMORY_TAG_RENDERER);

    /* TODO: make this configurable and support multiple backend. */
    renderer_backend_create(RENDERER_BACKEND_TYPE_VULKAN, plat_state, backend);
    backend->frame_number = 0;

    if (!backend->initialize(backend, application_name, plat_state))
    {
        NFATAL("Renderer backend failed to initialize, Shutting down.");
        return FALSE;
    }

    return TRUE;
}

void renderer_shutdown()
{
    backend->shutdown(backend);
    nfree(backend, sizeof(renderer_backend), MEMORY_TAG_RENDERER);
}

void renderer_on_resized(u16 width, u16 height)
{
    
}

b8 renderer_begin_frame(f32 delta_time)
{
    return backend->begin_frame(backend, delta_time);
}

b8 renderer_end_frame(f32 delta_time)
{
    b8 result = backend->end_frame(backend, delta_time);
    backend->frame_number++;
    return result;
}

b8 renderer_draw_frame(render_packet* packet)
{
    /* If the begin frame return successfully, mid-frame operation may continue. */
    if (renderer_begin_frame(packet->delta_time))
    {
        /* If end frame fails, it is likely un-recoverable, so, better boot out and shut down application. */
        b8 result = renderer_end_frame(packet->delta_time);

        if (!result)
        {
            NERROR("Renderer end frame failed, shutting down application....");
            return FALSE;
        }
    }

    return FALSE;
}
