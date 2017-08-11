#!/bin/bash
swig -python ccvwrapper.i
gcc -fpic -c ccvwrapper.c ccvwrapper_wrap.c ccv_algebra.c ccv_basic.c ccv_cache.c ccv_classic.c ccv_io.c ccv_memory.c ccv_output.c ccv_resample.c ccv_sift.c ccv_swt.c ccv_transform.c ccv_util.c ./3rdparty/sha1/sha1.c -I/usr/include/python2.7
ld -shared ccvwrapper.o ccvwrapper_wrap.o ccv_algebra.o ccv_basic.o ccv_cache.o ccv_classic.o ccv_io.o ccv_memory.o ccv_output.o ccv_resample.o ccv_sift.o ccv_swt.o ccv_transform.o ccv_util.o sha1.o -ljpeg -o _ccvwrapper.so
