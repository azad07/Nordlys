/**
 * @file game.c
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief
 * @version 1.0
 * @date 2023-04-18
 *
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 *
 */

#include "game.h"

#include <core/logger.h>

b8 game_initialize(game *game_instance)
{
    NDEBUG("game_initialize() called.");
    return TRUE;
}

b8 game_update(game *game_instance, f32 delta_time)
{
    // NDEBUG("game_update() called.");
    return TRUE;
}

b8 game_render(game *game_instance, f32 delta_time)
{
    // NDEBUG("game_render() called.");
    return TRUE;
}

void game_on_resize(game *game_instance, u32 width, u32 height)
{
    NDEBUG("game_on_resize() called.");
}