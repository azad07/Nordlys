/**
 * @file vulkan_backend.c
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-08-09
 * 
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 * 
 */

#include "vulkan_backend.h"
#include "vulkan_type.inl"

#include "core/logger.h"

/* static vulkan context. */
static vulkan_context context;

b8 vulkan_renderer_backend_initialize(renderer_backend* backend, const char* application_name, struct platform_state* plat_state)
{
    context.allocator = NULL;
    
    /* Setup vulkan instance. */
    VkApplicationInfo app_info = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
    app_info.apiVersion = VK_API_VERSION_1_3;
    app_info.pApplicationName = application_name;
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "Nordlys Game Engine";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);

    /* VK_KHR_PORTABILITY_ENUMERATION extension is needed for MacOS, MoltenVK,
     * as its not fully compatible.
     * FIXME: make it configurable for MAC
     */
    const char* requiredExtension[] = {VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME};

    VkInstanceCreateInfo create_info = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
    create_info.pNext = NULL;
    create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    create_info.pApplicationInfo = &app_info;
    create_info.enabledExtensionCount = 1;
    create_info.ppEnabledExtensionNames = requiredExtension;
    create_info.enabledLayerCount = 0;
    create_info.ppEnabledLayerNames = NULL;

    VkResult result = vkCreateInstance(&create_info, context.allocator, &context.instance);
    if (result != VK_SUCCESS)
    {      
        NERROR("vkCreateInstance failed with result: %u", result);
        return FALSE;
    }

    NINFO("Vulkan renderer initialized successfully. ");
    return TRUE;
}

void vulkan_renderer_backend_shutdown(renderer_backend* backend)
{
    
}

void vulkan_renderer_backend_on_resized(renderer_backend* backend, u16 width, u16 height)
{
    
}

b8 vulkan_renderer_backend_begin_frame(renderer_backend* backend, f32 delta_time)
{
    return TRUE;
}

b8 vulkan_renderer_backend_end_frame(renderer_backend* backend, f32 delta_time)
{
    return TRUE;
}