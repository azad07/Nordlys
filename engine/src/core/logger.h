/**
 * @file logger.h
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
 * @brief Indicates whether warnings level logging is enabled.
 *
 */
#define LOG_WARN_ENABLED 1

/**
 * @brief Indicates whether info level logging is enabled.
 *
 */
#define LOG_INFO_ENABLED 1

/**
 * @brief Indicates whether debug level logging is enabled.
 *
 */
#define LOG_DEBUG_ENABLED 1

/**
 * @brief Indicates whether error level logging is enabled.
 *
 */
#define LOG_TRACE_ENABLED 1

/* Disable debug and trace level logging for release builds. */
#if NRELEASE == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

/**
 * @brief Represent the levels of logging.
 *
 */
typedef enum log_level
{
    /**
     * @brief Fatal log level, should be used to stop the application when hit.
     *
     */
    LOG_LEVEL_FATAL = 0,

    /**
     * @brief Error log level, should be used to indicate critical runtime
     * problems with the application to run improperly or not at all.
     */
    LOG_LEVEL_ERROR = 1,

    /**
     * @brief Warning log level, should be used to indicat non-critical runtime
     * problems with the application that cause it to run suboptimally.
     */
    LOG_LEVEL_WARN = 2,

    /**
     * @brief Info log level, should be used for non-erronous informational
     * purposes.
     *
     */
    LOG_LEVEL_INFO = 3,

    /**
     * @brief Debug log level, should be used for debugging purposes.
     *
     */
    LOG_LEVEL_DEBUG = 4,

    /**
     * @brief Trace log level, should be used for verbose debugging purposes.
     *
     */
    LOG_LEVEL_TRACE = 5
} log_level;

b8 logging_initialize();

void logging_shutdown();

/**
 * @brief function for logging.
 *
 * @param level
 * @param message
 * @param ...
 * @return void
 */
NAPI void log_output(log_level level, const char *message, ...);

/**
 * @brief Logs a fatal-level error message.
 *
 */
#define NFATAL(message, ...) \
    log_output(LOG_LEVEL_FATAL, message, ##__VA_ARGS__);

#ifndef NERROR
/**
 * @brief Logs an error-level message.
 *
 */
#define NERROR(message, ...) \
    log_output(LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
#endif

#if LOG_WARN_ENABLED == 1
/**
 * @brief Logs a warning-level message.
 *
 */
#define NWARN(message, ...) \
    log_output(LOG_LEVEL_WARN, message, ##__VA_ARGS__);
#else
#define NWARN(message, ...) /* Does nothing. */
#endif

#if LOG_INFO_ENABLED == 1
/**
 * @brief Logs a info-level message.
 *
 */
#define NINFO(message, ...) \
    log_output(LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#else
#define KINFO(message, ...) /* Does nothing. */
#endif

#if LOG_DEBUG_ENABLED == 1
/**
 * @brief Logs a debug-level message.
 *
 */
#define NDEBUG(message, ...) \
    log_output(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#else
#define KDEBUG(message, ...) /* Does nothing. */
#endif

#if LOG_TRACE_ENABLED == 1
/**
 * @brief Logs a trace-level message.
 *
 */
#define NTRACE(message, ...) \
    log_output(LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
#else
#define KTRACE(message, ...) /* Does nothing. */
#endif
