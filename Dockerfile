FROM python:3.9.1-buster as base
RUN apt-get update && apt-get install -y libjpeg-dev libpng-dev libatlas-base-dev libblas-dev && \
    rm -rf /var/lib/apt/lists/*

FROM base AS build
# INSTALL CMAKE
WORKDIR /cmake
RUN wget https://github.com/Kitware/CMake/releases/download/v3.19.2/cmake-3.19.2-Linux-x86_64.sh && \
    mkdir -p /opt/cmake && \
    bash cmake-3.19.2-Linux-x86_64.sh --prefix=/opt/cmake --skip-license && \
    ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake

# BUILD CCV library
RUN mkdir /ccv && \
    git clone --single-branch --branch stable --depth 1 https://github.com/marrrcin/ccv.git /ccv && \
    cd /ccv/lib && ./configure && \
#    sed -i 's/O3/O0/g' makefile && \ # UNCOMENT THIS FOR FASTER DEBUG-PURPOSE BUILDS
    make libccv.a

# BUILD WRAPPER
RUN mkdir -p /swt-python/lib
COPY . /swt-python
RUN cp /ccv/lib/ccv.h /swt-python/lib/ccv.h && cp /ccv/lib/libccv.a /swt-python/lib/libccv.a
WORKDIR /swt-python
RUN cmake -DCMAKE_BUILD_TYPE=Release -DPYTHON_INCLUDE_DIRS=/usr/local/include/python3.9 . && make

FROM base as runtime
RUN mkdir /swt-python
WORKDIR /swt-python
COPY --from=build /swt-python/*.so /swt-python
COPY test.py /swt-python
COPY requirements.txt /swt-python
RUN pip install --no-cache-dir -r requirements.txt
COPY input.jpg /swt-python
ENTRYPOINT ["python", "test.py"]
