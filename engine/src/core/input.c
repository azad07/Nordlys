/**
 * @file input.c
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief
 * @version 1.0
 * @date 2023-07-22
 *
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 *
 */

#include "core/input.h"
#include "core/event.h"
#include "core/nmemory.h"
#include "core/logger.h"
#include "nmemory.h"

typedef struct keyboard_state {
    b8 keys[256];
}keyboard_state;

typedef struct mouse_state {
    i16 x;
    i16 y;
    u8 buttons[BUTTON_MAX_BUTTONS];
}mouse_state;

typedef struct input_state {
    keyboard_state keyboard_current;
    keyboard_state keyboard_previous;

    mouse_state mouse_current;
    mouse_state mouse_previous;
}input_state;

/* Internal Input state */
static b8 is_initialized = FALSE;
static input_state state = {};

b8 input_initialize()
{
    nzero_memory(&state, sizeof(input_state));
    is_initialized = TRUE;
    NINFO("Input subsystem Initialized. ");

    /* TODO: handle cases, when input system can fail. */
    return TRUE;
}

void input_shutdown()
{
    /* TODO: Add shutdown routines when needed in future. */
    is_initialized = FALSE;
}

void input_update(f64 delta_time)
{
    if(!is_initialized)
    {
        /* boot out and print dbg msg. */
        NDEBUG(" Input subsystem not initialized. ");
        return ;
    }

    /* Copy current state to previous state. */
    ncopy_memory(&state.keyboard_previous, &state.keyboard_current, sizeof(keyboard_state));
    ncopy_memory(&state.mouse_previous, &state.mouse_current, sizeof(mouse_state));
}

void input_process_keyboard_key(keys key, b8 pressed)
{
    /* only handled if the state is actually changed. */
    if(state.keyboard_current.keys[key] != pressed)
    {
        /* update internal state. */
        state.keyboard_current.keys[key] = pressed;

        /* Fire off an event for immediate processing. */
        event_context context;
        context.data.u16[0] = key;
        event_fire(pressed ? EVENT_CODE_KEY_PRESSED : EVENT_CODE_KEY_RELEASED, 0 /* no sender trackder needed*/, context );        
    }
}

void input_process_mouse_button(buttons button, b8 pressed)
{
    /* If the state changed, fire an event. */
    if(state.mouse_current.buttons[button] != pressed)
    {
        state.mouse_current.buttons[button] = pressed;

        /* Fire mouse event. */
        event_context context;
        context.data.u16[0] = button;
        event_fire(pressed ? EVENT_CODE_BUTTON_PRESSED : EVENT_CODE_BUTTON_RELEASED, 0, context);
    }
}

void input_process_mouse_move(i32 x, i32 y) {
    /* only process when there is change in mouse coordinates. */
    if (state.mouse_current.x != x ||
        state.mouse_current.y != y) 
    {
        /* NOTE: enable this for mouse debugging. */
        //KDEBUG("Mouse pos: %i, %i!", x, y);
        
        /* update internal state. */
        state.mouse_current.x = x;
        state.mouse_current.y = y;

        /* Fire mouse event for x, y coordinate update. */
        event_context context;
        context.data.u16[0] = x;
        context.data.u16[1] = y;
        event_fire(EVENT_CODE_MOUSE_MOVED, 0, context);
    }
}
void input_process_mouse_wheel(i8 z_delta)
{
    /* NOTE: no internal event to update. */

    /* Fire the event. */
    event_context context;
    context.data.i8[0] = z_delta;
    event_fire(EVENT_CODE_MOUSE_WHEEL, 0, context);
}

b8 input_is_key_down(keys key)
{
    if(!is_initialized)
    {
        return FALSE;
    }
    return state.keyboard_current.keys[key] == TRUE;
}

b8 input_is_key_up(keys key)
{
    if(!is_initialized)
    {
        return FALSE;
    }
    return state.keyboard_current.keys[key] == FALSE;
}

b8 input_was_key_down(keys key)
{
    if(!is_initialized)
    {
        return FALSE;
    }
    return state.keyboard_previous.keys[key] == TRUE;
}

b8 input_was_key_up(keys key)
{
    if(!is_initialized)
    {
        return FALSE;
    }
    return state.keyboard_previous.keys[key] == FALSE;
}

b8 input_is_button_down(buttons button)
{
    if(!is_initialized)
    {
        return FALSE;
    }
    return state.mouse_current.buttons[button] == TRUE;
}

b8 input_is_button_up(buttons button)
{
    if(!is_initialized)
    {
        return FALSE;
    }
    return state.mouse_current.buttons[button] == FALSE;
}

b8 input_was_button_down(buttons button)
{
    if(!is_initialized)
    {
        return FALSE;
    }
    return state.mouse_previous.buttons[button] == TRUE;
}

b8 input_was_button_up(buttons button)
{
    if(!is_initialized)
    {
        return FALSE;
    }
    return state.mouse_previous.buttons[button] == FALSE;
}

void input_get_mouse_position(i32* x, i32* y)
{
    if(!is_initialized)
    {
        *x = 0;
        *y = 0;
        return ;
    }
    *x = state.mouse_current.x;
    *y = state.mouse_current.y;
}

void input_get_previous_mouse_position(i32* x, i32 *y)
{
    if(!is_initialized)
    {
        *x = 0;
        *y = 0;
        return ;
    }
    *x = state.mouse_previous.x;
    *y = state.mouse_previous.y;
}
