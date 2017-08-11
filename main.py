from __future__ import print_function
import ccvwrapper
import numpy as np
from skimage import draw
from skimage.io import imread, imshow, imsave
from matplotlib import pyplot as plt


def rectangle_perimeter(r0, c0, width, height, shape=None, clip=False):
    rr, cc = [r0, r0 + width, r0 + width, r0], [c0, c0, c0 + height, c0 + height]

    return draw.polygon_perimeter(rr, cc, shape=shape, clip=clip)


if __name__ == "__main__":
    image_name = "test_input.jpg"
    bytes = open(image_name, "rb").read()
    swt_result_raw = ccvwrapper.swt(bytes, len(bytes), 1024, 1360)
    swt_result = np.reshape(swt_result_raw, (len(swt_result_raw) / 4, 4))

    image = imread(image_name, as_grey=False)
    for x, y, width, height in swt_result:
        for i in xrange(0, 3): # just to make lines thicker
            rr, cc = rectangle_perimeter(y + i, x + i, height, width, shape=image.shape, clip=True)
            image[rr, cc] = (255, 0, 0)

    imshow(image)
    imsave("result.jpg", image)
    plt.show()
