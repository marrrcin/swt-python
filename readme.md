# Fast Stroke Width Transform for Python
This repo contains wrapper for libccv's SWT algorithm for use in Python 3.
It's compatible with Linux, macOS and Docker.

For more information, see my blog post: http://zablo.net/blog/post/stroke-width-transform-swt-python-3.9

## Usage

```python
from swt_python3 import swt

buffer = open("input.jpg", "rb").read()
swt_result: List[dict] = swt(buffer, len(buffer))
for item in swt_result:
    x, y, width, height = [item[key] for key in ("x", "y", "width", "height")]
    print(x, y, width, height)
```

See `example.py` for details.

## Docker image
```bash
docker pull marrrcin/swt-python3-ccv:20210111
docker run --rm -it --entrypoint bash marrrcin/swt-python3-ccv:20210111
```