include(FetchContent)

#FetchContent_Declare(
#        pybind11
#        URL   "https://github.com/pybind/pybind11/archive/v2.4.2.tar.gz"
#        URL_HASH SHA512=05a49f99c1dff8077b05536044244301fd1baff13faaa72c400eafe67d9cb2e4320c77ad02d1b389092df703cc585d17da0d1e936b06112e2c199f6c1a6eb3fc
#)

FetchContent_Declare(
        pybind11
        URL   "https://github.com/pybind/pybind11/archive/v2.6.1.tar.gz"
)

FetchContent_MakeAvailable(pybind11)
