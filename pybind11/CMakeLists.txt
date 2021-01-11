include(FetchContent)

FetchContent_Declare(
        pybind11
        URL   "https://github.com/pybind/pybind11/archive/v2.6.1.tar.gz"
)

FetchContent_MakeAvailable(pybind11)
