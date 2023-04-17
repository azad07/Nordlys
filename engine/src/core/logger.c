/**
 * @file logger.c
 * @author Ashish Azad (ashish.azad07@gmail.com)
 * @brief
 * @version 1.0
 * @date 2023-04-17
 *
 * @copyright Nordlys Game Engine is Copyright (c) Ashish Azad 2023.
 *
 */

#include "logger.h"
#include "asserts.h"

// TODO: temporary.
#include <errno.h>
#include <execinfo.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

b8 logging_initialize()
{
    // TODO: create log file/s.
    return TRUE;
}

void logging_shutdown()
{
    // TODO: cleanup logging/write queued entries.
}

void log_output(log_level level, const char *message, ...)
{
    const char *level_strings[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]:  ",
                                    "[INFO]:  ", "[DEBUG]: ", "[TRACE]: "};
    // b8 is_error = level < 2;

    // Technically imposes a 32k character limit on a single log entry, but...
    // DON'T DO THAT!
    char out_message[32000];
    memset(out_message, 0, sizeof(out_message));

    // Format original message.
    // NOTE: Oddly enough, MS's headers override the GCC/Clang va_list type with a
    // "typedef char* va_list" in some cases, and as a result throws a strange
    // error here. The workaround for now is to just use __builtin_va_list, which
    // is the type GCC/Clang's va_start expects.
    __builtin_va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(out_message, 32000, message, arg_ptr);
    va_end(arg_ptr);

    char out_message2[32000];
    sprintf(out_message2, "%s%s\n", level_strings[level], out_message);

    // TODO: platform-specific output.
    printf("%s", out_message2);
}

void full_write(int fd, const char *buf, size_t len)
{
    while (len > 0)
    {
        ssize_t ret = write(fd, buf, len);

        if ((ret == -1) && (errno != EINTR))
            break;

        buf += (size_t)ret;
        len -= (size_t)ret;
    }
}

void print_backtrace(void)
{
    static const char start[] = "BACKTRACE ------------\n";
    static const char end[] = "----------------------\n";

    void *bt[1024];
    int bt_size;
    char **bt_syms;
    int i;

    bt_size = backtrace(bt, 1024);
    bt_syms = backtrace_symbols(bt, bt_size);
    full_write(STDERR_FILENO, start, strlen(start));
    for (i = 1; i < bt_size; i++)
    {
        size_t len = strlen(bt_syms[i]);
        full_write(STDERR_FILENO, bt_syms[i], len);
        full_write(STDERR_FILENO, "\n", 1);
    }
    full_write(STDERR_FILENO, end, strlen(end));
    free(bt_syms);
}

void report_assertion_failure(const char *expression, const char *message,
                              const char *file, i32 line)
{
    log_output(LOG_LEVEL_FATAL,
               "Assertion Failure: %s, message: '%s', in file: %s, line: %d\n",
               expression, message, file, line);
}
