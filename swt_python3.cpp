extern "C" {
    #include "lib/ccv.h"
}

#include <pybind11/pybind11.h>

namespace py = pybind11;


py::list swt(char *bytes, int array_length){
    py::list result;
    ccv_enable_default_cache();
    ccv_dense_matrix_t* image = 0;
    ccv_enable_default_cache();
    ccv_read((void*)bytes, &image, CCV_IO_GRAY | CCV_IO_ANY_STREAM, array_length);
    if(image != 0) {
        ccv_array_t *words = ccv_swt_detect_words(image, ccv_swt_default_params);
        if (words) {
            int i;
            for (i = 0; i < words->rnum; i++) {
                ccv_rect_t *rect = (ccv_rect_t *) ccv_array_get(words, i);
                py::dict item;
                item["x"] = rect->x;
                item["y"] = rect->y;
                item["width"] = rect->width;
                item["height"] = rect->height;
                result.append(item);
            }
            ccv_array_free(words);
        }
        ccv_matrix_free(image);
    }

    return result;
}


PYBIND11_MODULE(swt_python3, m) {
    m.doc() = "Python 3 compatible SWT (Stroke-Width-Transform) binding to libccv by Marcin Zabłocki";
    m.def("swt", &swt, "Apply Stroke-Width-Transform on input byte stream");
}