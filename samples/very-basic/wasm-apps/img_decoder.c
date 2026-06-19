/*
 * This is a demo of WAMR-Phantom integration showcasing the possibility
 * of porting existing C code to Phantom (stb_image.h is an image decoding
 * mini-library). This code compiles to Wasm and is able to provide image
 * decoding functionality to Phantom programs
 */

#define STB_IMAGE_IMPLEMENTATION

// no file io
#define STBI_NO_STDIO

// these rely on math.h, we don't have it
#define STBI_NO_LINEAR
#define STBI_NO_HDR

// we don't have proper assert.h, redefine our own assert
#include <stdio.h> // for printf (to remove)
#define STBI_ASSERT(x)                    \
    do {                                  \
        if (!(x))                         \
            printf("Assertion failed\n"); \
    } while (0)

#include <stdlib.h>
#include <string.h>
void *
my_realloc(void *ptr, size_t old_size, size_t new_size)
{
    if (new_size == 0) {
        free(ptr);
        return NULL;
    }

    void *new_ptr = malloc(new_size);
    if (!new_ptr) {
        return NULL; // out of memory
    }

    size_t copy_size = (new_size < old_size) ? new_size : old_size;

    memcpy(new_ptr, ptr, copy_size);

    free(ptr);

    return new_ptr;
}
#define STBI_MALLOC(sz) malloc(sz)
#define STBI_FREE(p) free(p)
#define STBI_REALLOC_SIZED(p, oldsz, newsz) my_realloc(p, oldsz, newsz)

// our stdlib does not provide this
int
abs(int x)
{
    if (x < 0) {
        return -x;
    }
    else {
        return x;
    }
}

#include "stb_image.h"
#include "phantom_api.h"

// `image_contents` - phantom string
// returns phantom bitmap
phantom_object_t
decode_image(phantom_object_t image_contents)
{
    int buffer_size;
    unsigned char *buffer = ph_unpack_string(image_contents, &buffer_size);

    // Load bitmaps
    int x, y, ch_cnt;
    unsigned char *image =
        stbi_load_from_memory(buffer, buffer_size, &x, &y, &ch_cnt, 3);
    free(buffer);
    int img_length = x * y * ch_cnt;
    int ppm_length =
        img_length + 64; // 64 extra should be enough for any header
    char *ppm = malloc(ppm_length);

    // write the header
    int offset = snprintf(ppm, ppm_length, "P6\n%d %d\n%d\n", x, y, 255);
    memcpy(ppm + offset, image, img_length);
    free(image);

    // create bitmap object
    phantom_object_t bmp = ph_load_bitmap(ppm, img_length);
    free(ppm);

    return bmp;
}

// `image_contents` - phantom string
// creates a phantom window and draws the given image there
void
decode_show_image(phantom_object_t jpeg_contents)
{
    phantom_object_t zero_int = phantom_int(0);

    phantom_object_t win = ph_new_window("Jpeg", 250, 250, -1, -1, 0xFFCCCCb4);
    phantom_object_t bmp = decode_image(jpeg_contents);

    // draw background image
    phantom_object_t draw_image_params[] = { zero_int, zero_int, bmp };
    ph_syscall(win, PHANTOM_WINDOW_DRAW_IMAGE, draw_image_params, 3);

    ph_syscall0(win, PHANTOM_WINDOW_UPDATE);
}
