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
#include "vulkan_platform.h"

#include "core/logger.h"
#include "core/nstring.h"

#include "container/darray.h"

#include "platform/platform.h"

/* static vulkan context. */
static vulkan_context context;

VKAPI_ATTR VkBool32 VKAPI_CALL _debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_types,
    const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
    void* user_data);

b8 vulkan_renderer_backend_initialize(renderer_backend* backend, const char* application_name, struct platform_state* plat_state)
{
    // TODO: Implement and use custom allocation, something like VMA (Vulkan memeory allocator from AMD.)
    context.allocator = NULL;

    /* Setup vulkan instance. */
    VkApplicationInfo app_info = { VK_STRUCTURE_TYPE_APPLICATION_INFO };
    app_info.apiVersion = VK_API_VERSION_1_3;
    app_info.pApplicationName = application_name;
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "Nordlys Game Engine";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);

    /* Obtain a list of required extensions. */
    const char** required_extension = darray_create(const char*);
    darray_push(required_extension, &VK_KHR_SURFACE_EXTENSION_NAME);        // Generic surface extension.
    platform_get_required_extension_names(&required_extension);             // Platform specific extension(s);

#if defined (_DEBUG)
    darray_push(required_extension, &VK_EXT_DEBUG_UTILS_EXTENSION_NAME);    // debug utilities.

    NDEBUG("Required Extensions...");
    u32 length = darray_length(required_extension);
    for (u32 i = 0; i < length; ++i)
    {
        NDEBUG(required_extension[i]);
    }
#endif

    /* Validation layers. */
    const char** required_validation_layer_names = NULL;
    u32 required_validation_layer_count = 0;

    /* If validation needed, get a list of required validation layer names and make
     * sure all the layeres exist on the platform. Validation should be performed on
     * non-release build only.
     */
#if defined (_DEBUG)
    NINFO("Validation layer enabled. Enumerating...");

    /* List of validation layer requred. */
    required_validation_layer_names = darray_create(const char*);
    darray_push(required_validation_layer_names, &"VK_LAYER_KHRONOS_validation");
    required_validation_layer_count = darray_length(required_validation_layer_names);

    /* Obtain a list of available validation layer.*/
    u32 available_validation_layer_count = 0;
    VK_CHECK(vkEnumerateInstanceLayerProperties(&available_validation_layer_count, 0));
    VkLayerProperties* available_layers = darray_reserve(VkLayerProperties, available_validation_layer_count);
    VK_CHECK(vkEnumerateInstanceLayerProperties(&available_validation_layer_count, available_layers));

    /* Verify all the required layers are available.*/
    for (u32 i = 0; i < required_validation_layer_count; ++i)
    {
        NINFO("Searching for layer: %s...", required_validation_layer_names[i]);
        b8 found = FALSE;
        for (u32 j = 0; j < available_validation_layer_count; ++j)
        {
            if (strings_equal(required_validation_layer_names[i], available_layers[j].layerName))
            {
                found = TRUE;
                NINFO("Found.");
                break;
            }
        }
        if (!found)
        {
            NFATAL("Required validation layer is missing: %s", required_validation_layer_names[i]);
            return FALSE;
        }
    }
    NINFO("All requred validation layers are present.");
#endif

    VkInstanceCreateInfo create_info = { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
    create_info.pNext = NULL;
    //FIXME:  flag should be from platfrom specific ...?
    create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    create_info.pApplicationInfo = &app_info;
    create_info.enabledExtensionCount = darray_length(required_extension);
    create_info.ppEnabledExtensionNames = required_extension;
    create_info.enabledLayerCount = required_validation_layer_count;
    create_info.ppEnabledLayerNames = required_validation_layer_names;

    VK_CHECK(vkCreateInstance(&create_info, context.allocator, &context.instance));
    NINFO("Vulkan Instance created.");

    /* Vulkan debugger. */
#if defined (_DEBUG)
    NDEBUG("Creating Vulkan debugger...");
    u32 log_severity =  VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT   |
                        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                        VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT    |
                        VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;

    VkDebugUtilsMessengerCreateInfoEXT debug_create_info = { VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT };
    debug_create_info.messageSeverity = log_severity;
    debug_create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                    VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT |
                                    VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                    VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT;
    debug_create_info.flags = 0;
    debug_create_info.pUserData = 0;
    debug_create_info.pfnUserCallback = _debug_callback;
    PFN_vkCreateDebugUtilsMessengerEXT func =
        (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(context.instance, "vkCreateDebugUtilsMessengerEXT");
    NASSERT_MSG(func, "Failed to create debug messenger!");
    VK_CHECK(func(context.instance, &debug_create_info, context.allocator, &context.debug_messenger));
    NDEBUG("Vulkan debugger created.");
#endif

    NINFO("Vulkan renderer initialized successfully. ");
    return TRUE;
}

void vulkan_renderer_backend_shutdown(renderer_backend* backend)
{
    NDEBUG("Destroying Vulkan debugger...");
    if (context.debug_messenger) {
        PFN_vkDestroyDebugUtilsMessengerEXT func =
            (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(context.instance, "vkDestroyDebugUtilsMessengerEXT");
        func(context.instance, context.debug_messenger, context.allocator);
    }

    NDEBUG("Destroying Vulkan instance...");
    vkDestroyInstance(context.instance, context.allocator);
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

VKAPI_ATTR VkBool32 VKAPI_CALL _debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_types,
    const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
    void* user_data)
{
    switch (message_severity)
    {
    default:
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
    NERROR(callback_data->pMessage);
    break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
    NWARN(callback_data->pMessage);
    break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
    NINFO(callback_data->pMessage);
    break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
    NTRACE(callback_data->pMessage);
    break;
    }
    return VK_FALSE;
}