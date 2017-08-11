#include "ccv.h"
#include <jpeglib.h>
#include "io/_ccv_io_libjpeg.c"
#include <sys/time.h>
#include <ctype.h>
#define SUCCESS 1
#define FAILURE 0

int* swt(char *bytes, int array_length, int width, int height){
    int *result_array;
    int status = FAILURE;
    ccv_enable_default_cache();
	ccv_dense_matrix_t* image = 0;

	FILE *stream;
	stream = fmemopen(bytes, array_length, "r");
	if(stream != NULL){
        int type = CCV_IO_JPEG_FILE | CCV_IO_GRAY;
        int ctype = (type & 0xF00) ? CCV_8U | ((type & 0xF00) >> 8) : 0;
        _ccv_read_jpeg_fd(stream, &image, ctype);

        if (image != 0)
        {
            ccv_array_t* words = ccv_swt_detect_words(image, ccv_swt_default_params);
            if (words)
            {
                int i;
                int result_idx = 1;
                result_array = (int*)malloc((4 * words->rnum + 1) * sizeof(int));
                result_array[0] = 4 * words->rnum;
                for (i = 0; i < words->rnum; i++)
                {
                    ccv_rect_t* rect = (ccv_rect_t*)ccv_array_get(words, i);
                    result_array[result_idx++] = rect->x;
                    result_array[result_idx++] = rect->y;
                    result_array[result_idx++] = rect->width;
                    result_array[result_idx++] = rect->height;
                }
                ccv_array_free(words);
                status = SUCCESS;
            }
            ccv_matrix_free(image);
        }
        ccv_drain_cache();
	}


    if(status != SUCCESS){
        result_array = (int*)malloc(1 * sizeof(int));
        result_array[0] = 0;
    }
    return result_array;
}


int main(){
    return 0;
}




