/**
 * @file renderer_backend.h
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-08-09
 * 
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 * 
 */

#pragma once

#include "renderer_type.inl"

struct platform_state;

b8 renderer_backend_create(renderer_backend_type type, struct platform_state* plat_state, renderer_backend* out_renderer_backend);

void renderer_backend_destroy(renderer_backend* renderer_backend);