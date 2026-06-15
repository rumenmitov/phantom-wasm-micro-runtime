#
# Copyright (C) 2019 Intel Corporation.  All rights reserved.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#

#!/bin/bash

CURR_DIR=$PWD
WAMR_DIR=${PWD}/../..
OUT_DIR=${PWD}/out
WASI_TARGETS=("wasi_functions.c")

WASM_APPS=${PWD}/wasm-apps


rm -rf ${OUT_DIR}
mkdir ${OUT_DIR}
mkdir ${OUT_DIR}/wasm-apps


echo "#####################build basic project"
cd ${CURR_DIR}
mkdir -p cmake_build
cd cmake_build
cmake ..
make
if [ $? != 0 ];then
    echo "BUILD_FAIL basic exit as $?\n"
    exit 2
fi

cp -a basic ${OUT_DIR}

echo -e "\n"

echo "#####################build wasm apps"

cd ${WASM_APPS}

for i in `ls *.c`
do
APP_SRC="$i"
OUT_FILE=${i%.*}.wasm
SKIP_FILE=0

for filename in ${WASI_TARGETS[@]}; do
        if [ "$APP_SRC" = "$filename" ]; then
                SKIP_FILE=1
                break
        fi
done

if [ $SKIP_FILE = 1 ]; then
        continue
fi

# use WAMR SDK to build out the .wasm binary
$WASI_SDK/bin/clang     \
        --target=wasm32 -O0 -z stack-size=16192 \
        --sysroot=${WAMR_DIR}/wamr-sdk/app/libc-builtin-sysroot  \
        -Wl,--allow-undefined-file=${WAMR_DIR}/wamr-sdk/app/libc-builtin-sysroot/share/defined-symbols.txt \
        -Wl,--strip-all,--no-entry -nostdlib \
        -Wl,--export-all \
        -Wl,--allow-undefined \
        -o ${OUT_DIR}/wasm-apps/${OUT_FILE} ${APP_SRC}


if [ -f ${OUT_DIR}/wasm-apps/${OUT_FILE} ]; then
        echo "build ${OUT_FILE} success"
else
        echo "build ${OUT_FILE} fail"
fi
done

# workaround to compile as wasi target
$WASI_SDK/bin/clang -O0        \
        -o ${OUT_DIR}/wasm-apps/wasi_functions.wasm wasi_functions.c

echo "####################build wasm apps done"
