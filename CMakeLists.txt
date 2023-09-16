cmake_minimum_required(VERSION 3.0.0)
project(HWM VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(HWM ./src/main.cpp)

add_compile_options(
    -Werror
    -g
    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
