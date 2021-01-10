cmake_minimum_required(VERSION 3.17)
project(swt_python3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O3")

find_library(CCV ccv lib)
find_package(JPEG REQUIRED)
find_package(PNG REQUIRED)
#find_package(PythonLibs)
include_directories(${PYTHON_INCLUDE_DIRS})

add_subdirectory(pybind11)
pybind11_add_module(swt_python3)
target_sources(swt_python3 PRIVATE swt_python3.cpp)
target_link_libraries(swt_python3 PRIVATE ${CCV} ${JPEG_LIBRARIES} ${PNG_LIBRARIES})
