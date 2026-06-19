#ifndef GENODE_STRING_ADAPTER_H
#define GENODE_STRING_ADAPTER_H

#include <ph_string.h>

// Probably crucial for WAMR
static inline size_t
strlen(const char *string)
{
    return ph_strlen(string);
}
static inline int
strcmp(const char *s1, const char *s2)
{
    return ph_strcmp(s1, s2);
}
static inline int
memcmp(const void *s1v, const void *s2v, size_t size)
{
    return ph_memcmp(s1v, s2v, size);
}
static inline void *
memmove(void *dst0, const void *src0, size_t length)
{
    return ph_memmove(dst0, src0, length);
}
static inline void *
memcpy(void *dst0, const void *src0, size_t length)
{
    return ph_memcpy(dst0, src0, length);
}
static inline void *
memset(void *dst0, int c0, size_t length)
{
    return ph_memset(dst0, c0, length);
}

// Additional ones for built-in libc functions
static inline char *
strchr(const char *p, int ch)
{
    return ph_strchr(p, ch);
}
static inline int
strncmp(const char *s1, const char *s2, size_t n)
{
    return ph_strncmp(s1, s2, n);
}
static inline char *
strncpy(char *to, const char *from, ssize_t count)
{
    return ph_strncpy(to, from, count);
}
static inline long
strtol(const char *nptr, char **endptr, int base)
{
    return ph_strtol(nptr, endptr, base);
}
static inline char *
strstr(const char *s1, const char *s2)
{
    return ph_strstr(s1, s2);
}
static inline int
atoi(const char *str)
{
    return ph_atoi(str);
}
static inline void *
memchr(const void *ptr, int ch, size_t count)
{
    return ph_memchr(ptr, ch, count);
}

// Additional just for WASI
static inline size_t
strnlen(const char *s, size_t count)
{
    return ph_strnlen(s, count);
}

#endif // GENODE_STRING_ADAPTER_H