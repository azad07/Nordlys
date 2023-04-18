/**
 * @file application.c
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief
 * @version 1.0
 * @date 2023-04-18
 *
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 *
 */

#include "application.h"
#include "game_types.h"

#include "logger.h"

#include "platform/platform.h"
#include "core/nmemory.h"

typedef struct application_state
{
    game *game_instance;
    b8 is_running;
    b8 is_suspended;
    platform_state platform;
    i16 width;
    i16 height;
    f64 last_time;
} application_state;

static b8 initialized = FALSE;
static application_state app_state;

b8 application_create(struct game *game_instance)
{
    if (initialized == TRUE)
    {
        NERROR("application_create called more than once.");
        return FALSE;
    }

    app_state.game_instance = game_instance;

    /* Initialize subsystems. */
    logging_initialize();

    // TODO: remove this.
    NFATAL("A test message: %f", 3.14f);
    NERROR("A test message: %f", 3.14f);
    NWARN("A test message: %f", 3.14f);
    NINFO("A test message: %f", 3.14f);
    NDEBUG("A test message: %f", 3.14f);
    NTRACE("A test message: %f", 3.14f);

    app_state.is_running = TRUE;
    app_state.is_suspended = FALSE;

    if (!platform_initialize(&app_state.platform,
                             game_instance->app_config.name,
                             game_instance->app_config.start_pos_x,
                             game_instance->app_config.start_pos_y,
                             game_instance->app_config.start_width,
                             game_instance->app_config.start_height))
    {
        return FALSE;
    }

    /* Initialize the game. */
    if (!app_state.game_instance->initialize(app_state.game_instance))
    {
        NFATAL("Game failed to initialize.");
        return FALSE;
    }

    app_state.game_instance->on_resize(app_state.game_instance, app_state.width, app_state.height);

    initialized = TRUE;
    return TRUE;
}

b8 application_run()
{
    NINFO(get_memory_usage_str());

    while (app_state.is_running)
    {
        if (!platform_pump_messages(&app_state.platform))
        {
            app_state.is_running = FALSE;
        }

        if (!app_state.is_suspended)
        {
            if (!app_state.game_instance->update(app_state.game_instance,
                                                 (f32)0))
            {
                NFATAL("Game update failed, Shutting down...");
                app_state.is_running = FALSE;
                break;
            }
        }

        /* Call the game's render routine. */
        if (!app_state.game_instance->render(app_state.game_instance, (f32)0))
        {
            NFATAL("Game render failed, Shutting down...");
            app_state.is_running = FALSE;
            break;
        }
    }

    app_state.is_running = FALSE;

    platform_shutdown(&app_state.platform);
    return TRUE;
}