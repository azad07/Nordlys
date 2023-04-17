/**
 * @file defines.h
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief defines datatype and set-up platform related stuffs.
 * @version 1.0
 * @date 2023-02-22
 *
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2022-2023
 *
 */
#pragma once

// Unsigned int types.
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

// Singed int types.
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

// Floating point types.
typedef float f32;
typedef double f64;

// Boolean type.
typedef char b8;
typedef int b32;

#define TURE 1
#define FALSE 0

// Properly define static assertions.
#if defined(__clang__) || defined(__gcc__)
#define STATIC_ASSERT _Static_assert
#else
#define STATIC_ASSERT static_assert
#endif

// check all types are of the correct size at compile time for the platform.
STATIC_ASSERT(sizeof(u8) == 1, "Expected u8 to be of 1 byte.");
STATIC_ASSERT(sizeof(u16) == 2, "Expected u16 to be of 2 byte.");
STATIC_ASSERT(sizeof(u32) == 4, "Expected u32 to be of 4 byte.");
STATIC_ASSERT(sizeof(u64) == 8, "Expected u64 to be of 8 byte.");

STATIC_ASSERT(sizeof(i8) == 1, "Expected i8 to be of 1 byte.");
STATIC_ASSERT(sizeof(i16) == 2, "Expected i16 to be of 2 byte.");
STATIC_ASSERT(sizeof(i32) == 4, "Expected i32 to be of 4 byte.");
STATIC_ASSERT(sizeof(i64) == 8, "Expected i64 to be of 8 byte.");

STATIC_ASSERT(sizeof(f32) == 4, "Expected f32 to be of 4 bytes.");
STATIC_ASSERT(sizeof(f64) == 8, "Expected f64 to be of 8 bytes.");

#define TRUE 1
#define FALSE 0

// Platform detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define NPLATFORM_WINDOWS 1
#ifndef _WIN64
#error "64-bit is required on windows!"
#endif
#elif defined(__linux__) || defined(__gnu_linux__)
// Linux OS
#define NPLATFORM_LINUX 1
#if defined(__ANDROID__)
#define NPLATFORM_ANDROID
#endif
#elif defined(__unix__)
// catch anything not caught by above.
#define NPLATFORM_UNIX 1
#elif defined(_POSIX_VERSION)
// Posix
#define KPLATFORM_POSIX 1
#elif __APPLE__
// Apple platform
#define NPLATFORM_APPLE 1
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
// ios simulator.
#define NPLATFORM_IOS 1
#define NPLATFORM_IOS_SIMULATOR 1
#elif TARGET_OS_IPHONE
#define NPLATFORM_ISO 1
// ios device.
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#else
#error "Unknown Apple platform!"
#endif
#else
#error "Unknown platform!"
#endif

#ifdef NEXPORT
// Exports
#ifdef _MSC_VER
#define NAPI __declspec(dllexport)
#else
#define NAPI __attribute__((visibility("default")))
#endif
#else
// Imports
#ifdef _MSC_VER
#define NAPI __declspec(dllimport)
#else
#define NAPI
#endif
#endif