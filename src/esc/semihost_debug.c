#include <esc/semihost_debug.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

#define SWD_CONNECTED (*((uint32_t*)0xE000EDF0) & 1)

extern void initialise_monitor_handles(void);
static bool initialized = false;

void semihost_debug_printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    if (SWD_CONNECTED) {
        if (!initialized) {
            initialise_monitor_handles();
            initialized = true;
        }
        printf(fmt, args);
    }
    va_end(args);
}
