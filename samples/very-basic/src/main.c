#include <unistd.h>
#include "wasm_export.h"
#include "bh_read_file.h"
#include "bh_getopt.h"

void
print_usage(void)
{
    fprintf(stdout, "Usage:\r\n");
    fprintf(stdout, "  <path of wasm file> [input for wasm function]\n");
}

int
run_wasm(const char *filename, const char *funcname, int input)
{
    char *buffer, error_buf[128];

    wasm_module_t module = NULL;
    wasm_module_inst_t module_inst = NULL;
    wasm_exec_env_t exec_env = NULL;
    uint32 buf_size, stack_size = 8092, heap_size = 8092;
    wasm_function_inst_t func = NULL;

    // 01. Initialize wasm runtime
    if (!wasm_runtime_init()) {
        printf("Init runtime environment failed.\n");
        return -1;
    }

    // 02. Read WASM file into memory buffer
    buffer = bh_read_file_to_buffer(filename, &buf_size);

    if (!buffer) {
        printf("Open wasm app file [%s] failed.\n", filename);
        goto fail;
    }

    // 03. Parse WASM file from buffer and create a WASM module
    module = wasm_runtime_load(buffer, buf_size, error_buf, sizeof(error_buf));
    if (!module) {
        printf("Load wasm module failed. error: %s\n", error_buf);
        goto fail;
    }

    // 04. Create an instance of WASM module (WASM linear memory is ready)
    module_inst = wasm_runtime_instantiate(module, stack_size, heap_size,
                                           error_buf, sizeof(error_buf));

    if (!module_inst) {
        printf("Instantiate wasm module failed. error: %s\n", error_buf);
        goto fail;
    }

    // 05. Create executation environment to execute WASM function
    exec_env = wasm_runtime_create_exec_env(module_inst, stack_size);
    if (!exec_env) {
        printf("Create wasm execution environment failed.\n");
        goto fail;
    }

    // 06. Lookup WASM function by name
    if (!(func = wasm_runtime_lookup_function(module_inst, funcname, NULL))) {
        printf("The main wasm function is not found.\n");
        goto fail;
    }

    // 07. Function call with parameters in an array of 32 bits elements and
    // size
    uint32 argv[2];
    // pass 2 elements for function arguments
    argv[0] = input;
    if (!wasm_runtime_call_wasm(exec_env, func, 1, argv)) {
        printf("call wasm function main failed. %s\n",
               wasm_runtime_get_exception(module_inst));
        goto fail;
    }

    double e = *((double *)argv);

    printf("Executed successfully. Result: e = %f\n", e);

fail:
    if (exec_env)
        wasm_runtime_destroy_exec_env(exec_env);
    if (module_inst) {
        wasm_runtime_deinstantiate(module_inst);
    }
    if (module)
        wasm_runtime_unload(module);
    if (buffer)
        BH_FREE(buffer);
    wasm_runtime_destroy();
    return 0;
}

#include <stdlib.h>

int
main(int argc, char *argv_main[])
{
    if (argc == 1) {
        print_usage();
        return 0;
    }
    const char *wasm_path = argv_main[1];

    printf("WASM path: %s\n", wasm_path);

    const char *func_name = "calculate_e";
    int N = 100000;
    if (argc > 2) {
        N = atoi(argv_main[2]);
    }
    printf("Numerical argument: %d\n", N);

    run_wasm(wasm_path, func_name, N);

    return 0;
}
