#ifndef GENODE_PRINT_ADAPTER_H
#define GENODE_PRINT_ADAPTER_H

#include <ph_io.h>

#define snprintf(s, n, fmt, ...) ph_snprintf(s, n, fmt, __VA_ARGS__)
static inline int
vsnprintf(char *s, size_t n, const char *format, va_list arg)
{
    return ph_vsnprintf(s, n, format, arg);
}

#define os_printf(...) ph_printf(__VA_ARGS__)
static inline int
os_vprintf(const char *format, va_list ap)
{
    return ph_vprintf(format, ap);
}

#endif // GENODE_PRINT_ADAPTER_H