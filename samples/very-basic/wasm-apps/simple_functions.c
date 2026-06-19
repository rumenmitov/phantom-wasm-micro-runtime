//
//
//

#include <stdint.h>

double
calculate_e(int N)
{
    double fac = 1.0;
    double e = 1.0;

    for (int n = 1; n <= N; n++) {
        fac *= n;
        e += 1.0 / fac;
    }

    return e;
}

#define declare_simple_sum(type)                   \
    type simple_sum_##type(type a, type b, type c) \
    {                                              \
        return a + b + c;                          \
    }

typedef long long int64;
declare_simple_sum(int) declare_simple_sum(int64) declare_simple_sum(float)
    declare_simple_sum(double)

        typedef int bool;
#define true 1
#define false 0

bool
is_prime(int num)
{
    if (num < 2)
        return false;

    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0)
            return false;
    }
    return true;
}

int
count_primes(int n)
{
    int primeCount = 0;

    for (int i = 0; i <= n; i++) {
        if (is_prime(i))
            primeCount++;
    }

    return primeCount;
}

void
void_return(int a, float b)
{
    double c = a + b;
}

#include <stdio.h>

void
hello_world()
{
    printf("Hello, world!\n");
}

void
print_prime_numbers(int limit, int interval, int offset)
{
    int counter = 0;

    for (int i = 0; i <= limit; i++) {
        if (is_prime(i)) {
            counter++;

            if ((counter + offset) % interval == 0) {
                printf("Prime number #%d: %d\n", counter, i);
            }
        }
    }
}

int
calculate_percentage(long long num, long long den)
{
    return (int)(100 * num / den);
}

int64_t
sum_perf_test(int64_t iter_count)
{
    int64_t sum = 0;

    for (int64_t i = 1; i <= iter_count; i++) {
        sum += i;
    }

    return sum;
}

#include <stdlib.h>

int64_t
memory_perf_test(int iter_count)
{
    int cell_count = 30000;

    int64_t *cells = calloc(sizeof(int64_t), cell_count);
    if (cells == 0) {
        printf("ERROR : MALLOC FAILURE\n");
        return -1;
    }

    for (int i = 1; i <= iter_count; i++) {
        for (int j = 0; j < cell_count; j++) {
            cells[j]++;
        }

        for (int j = 0; j < cell_count; j++) {
            if (cells[j] != i) {
                printf("Error : cell value invalid!\n");
                free(cells);
                return -1;
            }
        }
    }

    int64_t result = 0;

    for (int j = 0; j < cell_count; j++) {
        result += cells[j];
    }

    free(cells);

    return result;
}

void
perf_test()
{
    memory_perf_test(4000);
}

long long
long_sum_test(long long iter_count, int interval, long long start)
{
    long long sum = 0;
    long long step = start;

    printf("long_sum_test(): starting calculation...\n");

    int last_perc = 0;

    for (long long i = 0; i < iter_count; i++) {
        sum += step;
        step += interval;

        int new_perc = calculate_percentage(i + 1, iter_count);
        if (new_perc > last_perc) {
            last_perc = new_perc;
            printf("Calculating... %2d%%\n", new_perc);
        }
    }

    printf("long_sum_test() complete: %lld\n", sum);

    return sum;
}

#include "phantom_api.h"

void
phantom_hello_world()
{
    phantom_object_t tty = phantom_create_object(PHANTOM_TTY_CLASS);

    phantom_object_t message_string = phantom_new_string("Hello, world!");

    ph_syscall(tty, PHANTOM_IO_TTY_PUTWS, &message_string, 1);
    phantom_release_object(message_string);
}

#include "weather-images.h"

int temp_data[] = {
    12, 12, 13, 14, 14, 13, 12, 13, 14, 14, 15, 14, 13, 14, 14, 14, 15, 14, 14,
    14, 14, 14, 15, 16, 16, 15, 15, 14, 13, 12, 12, 12, 11, 11, 11, 11, 10, 11,
    10, 9,  10, 11, 12, 13, 13, 12, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 15,
    16, 14, 15, 15, 16, 15, 16, 16, 17, 16, 15, 15, 15, 16, 15, 15, 15, 15, 14,
    14, 14, 14, 14, 13, 11, 11, 10, 10, 12, 12, 13, 13, 13, 13, 12, 12, 12, 13,
    13, 13, 12, 12, 12, 13, 13, 12, 11, 11, 10, 10, 10, 10, 10, 10, 11, 9,  9,
    9,  9,  10, 11, 10, 10, 10, 10, 11, 10, 9,  9,  10, 11, 11, 11, 11, 11, 11,
    12, 12, 12, 13, 12, 12, 12, 13, 13, 14, 13, 13, 12, 12, 12, 13, 13, 14, 14,
    15, 16, 16, 16, 17, 17, 16, 16, 16, 16, 15, 15, 16, 17, 17, 16, 16, 15, 15,
    16, 15, 13, 14, 14, 15, 16, 16, 17, 17, 17, 17, 16, 15, 16, 15, 15, 15, 15,
    15, 15, 15, 14, 15, 18, 19, 19, 20, 18, 18, 19, 19, 19, 20, 20, 19, 19, 20,
    19, 18, 18, 20, 21, 21, 20, 21, 22, 21, 21, 20, 21, 21, 21, 22, 22, 21, 20,
    20, 20, 20, 20, 20, 20, 19, 18, 19, 19, 19, 19, 19, 18, 17, 17, 17, 16, 16,
    18, 17, 17, 18, 18, 17, 18, 18, 18, 16, 16, 16, 17, 17, 16, 17, 18, 18, 18,
    17, 19, 19, 19, 18, 18, 17, 17, 16, 15, 16, 15, 14, 14, 14, 15, 15, 16, 15,
    15, 15, 16, 16, 16, 15, 16, 15, 16, 16, 16, 15, 16, 17, 16, 15, 15, 14, 13,
    14, 15, 15, 15, 16, 17, 16, 17, 17, 16, 17, 17, 16, 17, 17, 16, 18, 17, 17,
    17, 18, 19, 19, 20, 19, 19, 19, 20, 21, 20, 20, 21, 22, 21, 21, 22, 22, 22,
    20, 19, 19, 20, 21, 20, 19, 20, 20, 20, 20, 20, 20, 19, 19, 18, 18, 19, 19,
    20, 19, 19, 19, 17, 17, 17, 16, 16, 16, 16, 16, 17, 18, 17, 17, 17, 16, 15,
    14, 13, 12, 12, 12, 12, 12, 11, 11, 11, 11, 12, 11, 11, 12, 12, 11, 11, 11,
    10, 11, 12, 12, 11, 12, 11, 10, 10, 10, 11, 11, 12, 11, 10, 9,  8,  8,  8,
    9,  10, 11, 11, 11, 12, 12, 13, 14, 13, 12, 12, 11, 11, 12, 13, 14, 14, 14,
    14, 13, 14, 15, 16, 15, 14, 14, 14, 14, 13, 14, 14, 13, 12, 12, 13, 13, 12,
    12, 13, 13, 13, 14, 13, 13, 12, 12, 13, 12, 12, 11, 11, 10, 10, 10, 9,  7,
    6,  7,  8,  8,  7,  7,  8,  8,  8,  7,  7,  7,  8,  7,  7,  8,  8,  8,  9,
    9,  10, 10, 11, 12, 12
};
int temp_data_size = sizeof(temp_data) / sizeof(int);

void
weather_demo(int sleep_msec)
{
    phantom_object_t zero_int = phantom_int(0);

    phantom_object_t win =
        ph_new_window("Weather", 100, 100, -1, -1, 0xFFCCCCb4);
    phantom_object_t sleep = ph_new_timer();

    // Load bitmaps
    phantom_object_t bmp = ph_load_bitmap((const char *)weather_window_bmp_data,
                                          sizeof(weather_window_bmp_data));
    phantom_object_t bmpw = ph_load_bitmap((const char *)weather_sun_sm_data,
                                           sizeof(weather_sun_sm_data));

    // set fg window color
    phantom_object_t color = phantom_int(0xFF93CDB4);
    ph_syscall(win, PHANTOM_WINDOW_SET_FOREGROUND, &color, 1);
    phantom_release_object(color);

    // draw background image
    phantom_object_t draw_image_params[] = { zero_int, zero_int, bmp };
    ph_syscall(win, PHANTOM_WINDOW_DRAW_IMAGE, draw_image_params, 3);

    // Draw icon and update window
    phantom_object_t draw_icon_params[] = { phantom_int(17), phantom_int(102),
                                            bmpw };
    ph_syscall(win, PHANTOM_WINDOW_DRAW_IMAGE, draw_icon_params, 3);
    phantom_release_object(draw_icon_params[0]);
    phantom_release_object(draw_icon_params[1]);
    ph_syscall0(win, PHANTOM_WINDOW_UPDATE);

    phantom_object_t draw_params[] = {
        zero_int,         zero_int,         bmp,
        phantom_int(250), phantom_int(240), phantom_int(120),
        phantom_int(22)
    };

    phantom_object_t first_str_draw[] = { phantom_int(280), phantom_int(235),
                                          0 };
    phantom_object_t second_str_draw[] = { phantom_int(250), phantom_int(235),
                                           phantom_new_string("T =") };
    phantom_object_t plot_params[] = { phantom_int(0), phantom_int(0),
                                       phantom_int(2), phantom_int(2) };
    phantom_object_t sleep_params[] = { PHANTOM_NULL_OBJECT,
                                        phantom_int(sleep_msec /* ms */) };

    int xpos = 17;
    int temp_data_index = 0;

    phantom_object_t black_color = phantom_int(0xFF000000);
    ph_syscall(win, PHANTOM_WINDOW_SET_FOREGROUND, &black_color, 1);
    phantom_release_object(black_color);

    phantom_object_t temp_obj = phantom_int(0);
    // phantom_object_t id_obj = phantom_int(0);

    // phantom_object_t tty = phantom_create_object(PHANTOM_TTY_CLASS);
    // phantom_object_t message_string1 = phantom_new_string("TTY heartbeat: ");
    // phantom_object_t message_string2 = phantom_new_string("...\n");

    // Plotting loop
    while (1) {
        int itemp = temp_data[(temp_data_index++) % temp_data_size];

        ph_syscall(win, PHANTOM_WINDOW_DRAW_IMAGE_PART, draw_params, 7);

        // heartbeat
        // phantom_set_int(id_obj, temp_data_index);
        // ph_print(tty, message_string1, /* release_message = */ 0);
        // ph_print(tty, phantom_to_string(id_obj, CT), /* release_message = */
        // 1); ph_print(tty, message_string2, /* release_message = */ 0);

        phantom_set_int(temp_obj, itemp);
        first_str_draw[2] = phantom_to_string(temp_obj, CT);
        ph_syscall(win, PHANTOM_WINDOW_DRAW_STRING, first_str_draw, 3);
        ph_syscall(win, PHANTOM_WINDOW_DRAW_STRING, second_str_draw, 3);
        phantom_release_object(first_str_draw[2]);

        int ypos = 15 + (itemp * 2);

        if (ypos < 70) {
            phantom_set_int(plot_params[0], xpos);
            phantom_set_int(plot_params[1], ypos);
            ph_syscall(win, PHANTOM_WINDOW_FILL_BOX, plot_params, 4);
        }

        ph_syscall(sleep, PHANTOM_CONNECTION_BLOCK, sleep_params, 2);

        xpos++;
        if (xpos > 358) {
            xpos = 17;
        }
    }
}
