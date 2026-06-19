/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#ifndef _PLATFORM_INTERNAL_H
#define _PLATFORM_INTERNAL_H

#include <kernel/config.h>
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <ctype.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <ph_time.h>
#include <ph_setjmp.h>
#include <kernel/mutex.h>
#include <kernel/cond.h>
#include <threads.h>

#include "string_adapter.h"
#include "print_adapter.h"
#include "stubs.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Stack size of applet threads's native part.  */
#define BH_APPLET_PRESERVED_STACK_SIZE (32 * 1024)

/* Default thread priority */
#define BH_THREAD_DEFAULT_PRIORITY 0

typedef hal_mutex_t pthread_mutex_t;
typedef hal_cond_t pthread_cond_t;

// typedef pthread_t korp_tid;
typedef pthread_mutex_t korp_mutex;
typedef pthread_cond_t korp_cond;
// typedef pthread_t korp_thread;

typedef int phantom_thread;
typedef phantom_thread korp_thread;

typedef tid_t korp_tid;

#if WASM_DISABLE_HW_BOUND_CHECK == 0
#if defined(BUILD_TARGET_X86_64) || defined(BUILD_TARGET_AMD_64) \
    || defined(BUILD_TARGET_AARCH64)

typedef jmp_buf korp_jmpbuf;

#define OS_ENABLE_HW_BOUND_CHECK

#define os_thread_local_attribute __thread

#define os_setjmp ph_setjmp
#define os_longjmp ph_longjmp

#define os_getpagesize getpagesize

typedef void (*os_signal_handler)(void *sig_addr);

/*
    NB: These methods below are here because some of the types they need
   (korp_tid, uint64, etc.) are definced / declared / included here.
*/

// (used for logging)
static inline korp_tid
os_self_thread(void)
{
    return get_current_tid();
}

// Needed for logging and performance tracking. Can be implmeneted later
static inline uint64
os_time_get_boot_microsecond(void)
{
    return 0;
}

// Can return NULL for now, but WAMR recommends implementing it if possible
static inline uint8 *
os_thread_get_stack_boundary(void)
{
    return NULL;
}

// phantom callbacks
extern int
wamr_phantom_create_mutex(hal_mutex_t *mutex, const char *name);
extern int
wamr_phantom_destroy_mutex(hal_mutex_t *mutex);
extern int
wamr_phantom_create_cond(hal_cond_t *mutex, const char *name);
extern int
wamr_phantom_destroy_cond(hal_cond_t *mutex);

// mutexes
static inline errno_t
pthread_mutex_init(pthread_mutex_t *m, const char *name)
{
    return wamr_phantom_create_mutex(m, name);
}
static inline int
os_mutex_init(korp_mutex *m)
{
    return wamr_phantom_create_mutex(m, NULL);
}

static inline errno_t
pthread_mutex_lock(pthread_mutex_t *m)
{
    return hal_mutex_lock(m);
}
static inline int
os_mutex_lock(korp_mutex *m)
{
    return hal_mutex_lock(m);
}

static inline errno_t
pthread_mutex_unlock(pthread_mutex_t *m)
{
    return hal_mutex_unlock(m);
}
static inline int
os_mutex_unlock(korp_mutex *m)
{
    return hal_mutex_unlock(m);
}

static inline errno_t
pthread_mutex_destroy(hal_mutex_t *m)
{
    return wamr_phantom_destroy_mutex(m);
}
static inline int
os_mutex_destroy(korp_mutex *m)
{
    return wamr_phantom_destroy_mutex(m);
}

// conds
static inline errno_t
pthread_cond_init(pthread_cond_t *c, const char *name)
{
    return wamr_phantom_create_cond(c, name);
}
static inline int
os_cond_init(korp_cond *c)
{
    return wamr_phantom_create_cond(c, NULL);
}

static inline errno_t
pthread_cond_wait(pthread_cond_t *c, pthread_mutex_t *m)
{
    return hal_cond_wait(c, m);
}
static inline int
os_cond_wait(korp_cond *c, korp_mutex *m)
{
    return hal_cond_wait(c, m);
}

static inline errno_t
pthread_cond_timedwait(pthread_cond_t *c, pthread_mutex_t *m,
                       struct timespec *timeout)
{
    return hal_cond_timedwait(
        c, m, timeout->tv_sec * 1000 + timeout->tv_nsec / 1000000);
}
static inline int
os_cond_timedwait(korp_cond *c, korp_mutex *m, uint64 msecTimeout)
{
    return hal_cond_timedwait(c, m, msecTimeout);
}

static inline errno_t
pthread_cond_signal(pthread_cond_t *c)
{
    return hal_cond_signal(c);
}
static inline int
os_cond_signal(korp_cond *c)
{
    return hal_cond_signal(c);
}

static inline errno_t
pthread_cond_destroy(pthread_cond_t *c)
{
    return wamr_phantom_destroy_cond(c);
}
static inline int
os_cond_destroy(korp_cond *c)
{
    return wamr_phantom_destroy_cond(c);
}

#endif /* end of BUILD_TARGET_X86_64/AMD_64/AARCH64 */
#endif /* end of WASM_DISABLE_HW_BOUND_CHECK */

#ifdef __cplusplus
}
#endif

#endif /* end of _PLATFORM_INTERNAL_H */
