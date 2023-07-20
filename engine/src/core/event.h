/**
 * @file event.h
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-07-18
 * 
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 * 
 */

 #pragma once

 #include "defines.h"

 typedef struct event_context {
    // 128 bytes event.
    union
    {
        /* data */
        i64 i64[2];
        u64 u64[2];
        f64 f64[2];

        i32 i32[4];
        u32 u32[4];
        f32 f32[4];

        i16 i16[8];
        u16 u16[8];

        i8 i8[16];
        u8 u8[16];

        char c[16];
    } data;
 } event_context;

/**
 * @brief function pointer for on_event.
 * 
 * @param code The event code to listen for.
 * @param sender A pointer to the sender.
 * @param listener_instance A pointer to the listener instance.
 * @param data The event data.
 * @returns should return true if handled.
 */
typedef b8 (*PFN_on_event)(u16 code, void* sender, void* listener_instance, event_context data);

/**
 * @brief Initialize the event subsystem.
 * 
 * @return b8 true on success, false on error.
 */
b8 event_initialize();

/**
 * @brief Clean  up and shutdown event subsystem.
 * 
 */
void event_shutdown();

/**
 * @brief Register to listen, when event are sent with the provided code. Events with duplicate listener/callback
 * will not be registered again and will cause this to return FALSE.
 * 
 * @param code The event code to listen for.
 * @param listener_instance A pointer to the listener instance. can be 0/NULL.
 * @param on_event The callback function pointer to be call invoked when the event code is fired.
 * @return TRUE if event is successfully registered; otherwise FALSE.
 */
NAPI b8 event_register(u16 code, void* listener_instance, PFN_on_event on_event);

/**
 * @brief Unregister from listening when events are send with the provided code.
 * If no matching registration is found, this function returns FALSE.
 * 
 * @param code The event code to stop listening for.
 * @param listener_instance Pointer to the listener instance.
 * @param on_evnet callback function pointer to be un-register.
 * @return TRUE if the event code is successfully un-register, otherwise FALSE.
 */
NAPI b8 event_unregister(u16 code, void* listener_instance, PFN_on_event on_evnet);

/**
 * @brief Fires an event to listeners of the given event code. If an event handlers
 * returns TRUE, the evnet is considered to be handled and will not propagate to any more listeners.
 * 
 * @param code event code to fire. 
 * @param sender Pointer to the sender. Can be 0/NULL.
 * @param eContext event data.
 * @return TRUE if handled, otherwise FALSE.
 */
NAPI b8 event_fire(u16 code, void* sender, event_context eContext);

/**
 * @brief 
 * 
 */
typedef enum system_event_code {
    /**
     * @brief 
     * 
     */
    EVENT_CODE_APPLICATION_SHUTDOWN =   0x01,
    EVENT_CODE_KEY_PRESSED =            0x02,
    EVENT_CODE_KEY_RELEASED =           0x03,
    EVENT_CODE_BUTTON_PRESSED =         0x04,
    EVENT_CODE_BUTTON_RELEASED =        0x05,
    EVENT_CODE_MOUSE_MOVED =            0x06,
    EVENT_CODE_MOUSE_WHEEL =            0x07,
    EVENT_CODE_RESIZED =                0x08,

    MAX_EVENT_CODE =                    0xFF
} system_event_code;