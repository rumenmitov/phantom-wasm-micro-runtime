#ifndef PHANTOM_WASM_API_H
#define PHANTOM_WASM_API_H

/* Bare API calls */

typedef unsigned long long phantom_object_t;

phantom_object_t
phantom_create_string(const char *data, unsigned int len);

#define DECLARE_NUMERIC_CALLS(ph_type, c_type)                           \
    phantom_object_t phantom_##ph_type(c_type value);                    \
    int phantom_set_##ph_type(phantom_object_t object_id, c_type value); \
    int phantom_get_##ph_type(phantom_object_t object_id, c_type *out);

DECLARE_NUMERIC_CALLS(int, int)
DECLARE_NUMERIC_CALLS(long, long long)
DECLARE_NUMERIC_CALLS(float, float)
DECLARE_NUMERIC_CALLS(double, double)

phantom_object_t
phantom_create_object(phantom_object_t class_id);

int
phantom_syscall(phantom_object_t me_id, phantom_object_t *ret_id,
                phantom_object_t thread_id, int syscall_index,
                phantom_object_t *arg_ids, unsigned int args_size);

void
phantom_release_object(phantom_object_t object_id);

int
phantom_throw(phantom_object_t object);

unsigned int
phantom_create(const char *path);

unsigned int
phantom_mkdir(const char *path);

unsigned int
phantom_fwrite(const char *path, void *buf, unsigned int bufsize);

unsigned int
phantom_fread(const char *path, void *buf, unsigned int bufsize);

unsigned int
phantom_file_size(const char *path);

unsigned int
phantom_rename(const char *oldpath, const char *newpath);

void
phantom_unlink(const char *path);

unsigned char *
phantom_get_string_contents(phantom_object_t object_id);

/* Additional wrappers */

#include <string.h>

// class ids
#define PHANTOM_NULL_CLASS 1
#define PHANTOM_CLASS_CLASS 2
#define PHANTOM_INTERFACE_CLASS 3
#define PHANTOM_CODE_CLASS 4
#define PHANTOM_INT_CLASS 5
#define PHANTOM_STRING_CLASS 6
#define PHANTOM_ARRAY_CLASS 7
#define PHANTOM_PAGE_CLASS 8
#define PHANTOM_THREAD_CLASS 9
#define PHANTOM_CALL_FRAME_CLASS 10
#define PHANTOM_ISTACK_CLASS 11
#define PHANTOM_OSTACK_CLASS 12
#define PHANTOM_ESTACK_CLASS 13
#define PHANTOM_LONG_CLASS 14
#define PHANTOM_FLOAT_CLASS 15
#define PHANTOM_DOUBLE_CLASS 16
#define PHANTOM_BOOT_CLASS 17
#define PHANTOM_TTY_CLASS 18
#define PHANTOM_MUTEX_CLASS 21
#define PHANTOM_COND_CLASS 22
#define PHANTOM_BINARY_CLASS 23
#define PHANTOM_BITMAP_CLASS 24
#define PHANTOM_WORLD_CLASS 25
#define PHANTOM_CLOSURE_CLASS 26
#define PHANTOM_UDP_CLASS 27
#define PHANTOM_TCP_CLASS 28
#define PHANTOM_WEAKREF_CLASS 29
#define PHANTOM_WINDOW_CLASS 30
#define PHANTOM_DIRECTORY_CLASS 31
#define PHANTOM_CONNECTION_CLASS 32
#define PHANTOM_SEMA_CLASS 33
#define PHANTOM_NET_CLASS 34
#define PHANTOM_HTTP_CLASS 35
#define PHANTOM_TIME_CLASS 36
#define PHANTOM_STAT_CLASS 37
#define PHANTOM_IO_CLASS 38
#define PHANTOM_PORT_CLASS 39
#define PHANTOM_UI_CONTROL_CLASS 40
#define PHANTOM_UI_FONT_CLASS 41
#define PHANTOM_WASM_CLASS 42

#define PHANTOM_NULL_OBJECT 999
#define PHANTOM_CURRENT_THREAD 998
#define CT PHANTOM_CURRENT_THREAD

// method indices
#define PHANTOM_STRING_LENGTH (11)

#define PHANTOM_DIRECTORY_PUT (8)

#define PHANTOM_CONNECTION_CONNECT (8)
#define PHANTOM_CONNECTION_BLOCK (13)

#define PHANTOM_IO_TTY_PUTWS (17)

#define PHANTOM_BITMAP_LOAD_FROM_STRING (8)

#define PHANTOM_WINDOW_CLEAR (20)
#define PHANTOM_WINDOW_SET_FOREGROUND (22)
#define PHANTOM_WINDOW_SET_BACKGROUND (23)
#define PHANTOM_WINDOW_DRAW_STRING (24)
#define PHANTOM_WINDOW_DRAW_IMAGE (25)
#define PHANTOM_WINDOW_SET_SIZE (26)
#define PHANTOM_WINDOW_SET_POSITION (27)
#define PHANTOM_WINDOW_FILL_BOX (30)
#define PHANTOM_WINDOW_SET_TITLE (33)
#define PHANTOM_WINDOW_UPDATE (34)
#define PHANTOM_WINDOW_DRAW_IMAGE_PART (36)

static inline phantom_object_t
phantom_new_string(const char *str)
{
    return phantom_create_string(str, strlen(str));
}

static inline phantom_object_t
phantom_to_string(phantom_object_t me_id, phantom_object_t thread_id)
{
    phantom_object_t ret;
    phantom_syscall(me_id, &ret, thread_id, 5, NULL, 0);
    return ret;
}

// exceptions?
static inline int
ph_syscall(phantom_object_t me_id, int syscall_index, phantom_object_t *arg_ids,
           unsigned int arg_count)
{
    phantom_object_t ret;
    int retval =
        phantom_syscall(me_id, &ret, CT, syscall_index, arg_ids, arg_count * 2);
    phantom_release_object(ret);

    return retval;
}

static inline int
ph_syscall0(phantom_object_t me_id, int syscall_index)
{
    phantom_object_t ret;
    int retval = phantom_syscall(me_id, &ret, CT, syscall_index, NULL, 0);
    phantom_release_object(ret);

    return retval;
}

static inline phantom_object_t
ph_new_window(const char *title, int xpos, int ypos, int width, int height,
              int bg_color)
{
    phantom_object_t params[] = { phantom_int(xpos), phantom_int(ypos) };
    phantom_object_t win_title = phantom_new_string(title);

    phantom_object_t win = phantom_create_object(PHANTOM_WINDOW_CLASS);
    ph_syscall(win, PHANTOM_WINDOW_SET_POSITION, params, 2);
    ph_syscall(win, PHANTOM_WINDOW_SET_TITLE, &win_title, 1);

    if (width >= 0 && height >= 0) {
        phantom_set_int(params[0], width);
        phantom_set_int(params[1], height);
        ph_syscall(win, PHANTOM_WINDOW_SET_SIZE, params, 2);
    }

    phantom_set_int(params[0], bg_color);
    ph_syscall(win, PHANTOM_WINDOW_SET_BACKGROUND, params, 1);
    ph_syscall0(win, PHANTOM_WINDOW_CLEAR);
    ph_syscall0(win, PHANTOM_WINDOW_UPDATE);

    phantom_release_object(win_title);
    phantom_release_object(params[0]);
    phantom_release_object(params[1]);

    return win;
}

static inline phantom_object_t
ph_new_timer()
{
    phantom_object_t timer = phantom_create_object(PHANTOM_CONNECTION_CLASS);
    phantom_object_t timer_name = phantom_new_string("tmr:");
    int ret = ph_syscall(timer, PHANTOM_CONNECTION_CONNECT, &timer_name, 1);
    phantom_release_object(timer_name);

    if (ret) {
        phantom_release_object(timer);
        return 0;
    }

    return timer;
}

static inline phantom_object_t
ph_load_bitmap(const char *bitmap_data, unsigned int length)
{
    phantom_object_t bmp = phantom_create_object(PHANTOM_BITMAP_CLASS);
    phantom_object_t bmp_data = phantom_create_string(bitmap_data, length);
    int ret = ph_syscall(bmp, PHANTOM_BITMAP_LOAD_FROM_STRING, &bmp_data, 1);
    phantom_release_object(bmp_data);

    if (ret) {
        phantom_release_object(bmp);
        return 0;
    }

    return bmp;
}

static inline void
ph_print(phantom_object_t tty, phantom_object_t message, int release_message)
{
    ph_syscall(tty, PHANTOM_IO_TTY_PUTWS, &message, 1);
    if (release_message)
        phantom_release_object(message);
}

static inline unsigned char *
ph_unpack_string(phantom_object_t string, int *string_length)
{
    unsigned char *buffer = phantom_get_string_contents(string);
    phantom_object_t ret;
    int retval =
        phantom_syscall(string, &ret, CT, PHANTOM_STRING_LENGTH, NULL, 0);
    phantom_get_int(ret, string_length);

    return buffer;
}

#endif // PHANTOM_WASM_API_H
