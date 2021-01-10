from typing import List

from swt_python3 import swt

from skimage import draw
from skimage.io import imread, imshow, imsave


def rectangle_perimeter(r0, c0, width, height, shape=None, clip=False):
    rr, cc = [r0, r0 + width, r0 + width, r0], [c0, c0, c0 + height, c0 + height]

    return draw.polygon_perimeter(rr, cc, shape=shape, clip=clip)


if __name__ == "__main__":
    image_name = "input.jpg"
    buffer = open(image_name, "rb").read()
    import time

    start = time.time()
    swt_result: List[dict] = swt(buffer, len(buffer))
    end = time.time()
    image = imread(image_name)
    for item in swt_result:
        for i in range(0, 3):  # just to make lines thicker
            x, y, width, height = [item[key] for key in ("x", "y", "width", "height")]
            print(x, y, width, height)
            rr, cc = rectangle_perimeter(
                y + i, x + i, height, width, shape=image.shape, clip=True
            )
            image[rr, cc] = (255, 0, 0)

    imsave("result.jpg", image)
    # from matplotlib import pyplot as plt
    # imshow(image)
    # plt.show()
    print(f"SWT time: {end-start:0.4f}s")
