/**
 * @file game.h
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief
 * @version 1.0
 * @date 2023-04-18
 *
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 *
 */

#pragma once

#include <defines.h>
#include <game_types.h>

typedef struct game_state
{
    f32 delta_time;
} game_state;

b8 game_initialize(game *game_instance);

b8 game_update(game *game_instance, f32 delta_time);

b8 game_render(game *game_instance, f32 delta_time);

void game_on_resize(game *game_instance, u32 width, u32 height);