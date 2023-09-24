cmake_minimum_required(VERSION 3.0.0)
project(HWM VERSION 0.1.0 LANGUAGES C CXX)
set (CMAKE_CXX_STANDARD 17)



include(CTest)
enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)
include(GoogleTest)
add_executable(test_HWM test/test.cpp)
target_link_libraries(test_HWM GTest::gtest_main)
gtest_discover_tests(test_HWM)

add_executable(HWM ./src/main.cpp)

add_compile_options(
    -Werror
    -g
    -Wall
    -Wextra
    -Wpedantic
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -O0
)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
