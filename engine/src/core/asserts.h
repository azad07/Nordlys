/**
 * @file asserts.h
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief
 * @version 1.0
 * @date 2023-04-17
 *
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 *
 */

#pragma once

#include "defines.h"

/**
 * @brief Disable assertions by commenting out the below declarations.
 *
 */
#define NASSERTIONS_ENABLED

#ifdef NASSERTIONS_ENABLED

#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif

NAPI void report_assertion_failure(const char *expression, const char *message, const char *file, i32 line);

#define NASSERT(expr)                                                \
    {                                                                \
        if (expr)                                                    \
        {                                                            \
        }                                                            \
        else                                                         \
        {                                                            \
            report_assertion_failure(#expr, "", __FILE__, __LINE__); \
            debugBreak();                                            \
        }                                                            \
    }

#define NASSERT_MSG(expr, message)                                        \
    {                                                                     \
        if (expr)                                                         \
        {                                                                 \
        }                                                                 \
        else                                                              \
        {                                                                 \
            report_assertion_failure(#expr, message, __FILE__, __LINE__); \
            debugBreak();                                                 \
        }                                                                 \
    }

#ifdef _DEBUG
#define NASSERT_DEBUG(expr)                                          \
    {                                                                \
        if (expr)                                                    \
        {                                                            \
        }                                                            \
        else                                                         \
        {                                                            \
            report_assertion_failure(#expr, "", __FILE__, __LINE__); \
            debugBreak();                                            \
        }                                                            \
    }
#else
#define NASSERT_DEBUG(expr) // Does nothing at all
#endif

#else
#define NASSERT(expr)              // Does nothing at all
#define NASSERT_MSG(expr, message) // Does nothing at all
#define NASSERT_DEBUG(expr)        // Does nothing at all
#endif