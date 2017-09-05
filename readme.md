# Fast Stroke Width Transform for Python
This repo contains wrapper for libccv's SWT algorithm for use in Python.

For more information, see my blog post: http://zablo.net/blog/post/stroke-width-transform-swt-python

## How to:

1. Checkout libccv (I've forked it at the time when I built this wrapper):
    ```
    git clone https://github.com/marrrcin/ccv.git
    ```
1. Put ```ccvwrapper.*``` files from this repo into ```/lib``` folder of ccv
1. Use the following script to build the wrapper:
    ```
    #!/bin/bash
    swig -python ccvwrapper.i

    gcc -fpic -c ccvwrapper.c ccvwrapper_wrap.c ccv_algebra.c ccv_basic.c ccv_cache.c ccv_classic.c ccv_io.c ccv_memory.c ccv_output.c ccv_resample.c ccv_sift.c ccv_swt.c ccv_transform.c ccv_util.c ./3rdparty/sha1/sha1.c -I/usr/include/python2.7

    ld -shared ccvwrapper.o ccvwrapper_wrap.o ccv_algebra.o ccv_basic.o ccv_cache.o ccv_classic.o ccv_io.o ccv_memory.o ccv_output.o ccv_resample.o ccv_sift.o ccv_swt.o ccv_transform.o ccv_util.o sha1.o -ljpeg -o _ccvwrapper.so

    ```
1. Copy outputs of the build into your project
    ```
    cp ccvwrapper* ~/PycharmProjects/path_to_your_project
    cp _ccvwrapper* ~/PycharmProjects/path_to_your_project
    ```

1. In Python just use:
    ```
    import ccvwrapper
    import numpy as np
    swt_result_raw = ccvwrapper.swt(open("test_input.jpg", "rb").read(), len(bytes), 1024, 1360)
    swt_result = np.reshape(swt_result_raw, (len(swt_result_raw) / 4, 4))
    ```
1. Done!
