#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
test_argv_main(int argc, char **argv)
{
    if (argc < 1)
        return -1;
    if (argc == 1)
        return 0;

    int sum = 0;
    for (int i = 1; i < argc; i++) {
        int arg_sum = 0;

        for (char *ptr = argv[i]; *ptr != '\0'; ptr++)
            arg_sum += *ptr;

        sum += i * arg_sum;
    }

    return sum;
}

int
test_env_main()
{
    int sum = 0;
    char *display = getenv("DISPLAY");

    if (display) {
        for (char *ptr = display; *ptr != '\0'; ptr++)
            sum += *ptr;
    }

    char *path = getenv("PATH");

    if (path) {
        for (char *ptr = path; *ptr != '\0'; ptr++)
            sum -= *ptr;
    }

    return sum;
}

int
main(int argc, char **argv)
{
    if (argc <= 0)
        return -1;
    const char *program_name = argv[0];
    int retval = 0;

    if (strcmp(program_name, "argv_test") == 0) {
        retval = test_argv_main(argc, argv);
    }
    else if (strcmp(program_name, "env_test") == 0) {
        retval = test_env_main();
    }
    else
        return -1;

    // printf("Result: %d\n", retval);
    return retval;
}
