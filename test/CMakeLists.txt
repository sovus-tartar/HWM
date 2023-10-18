add_executable(test_HWM test.cpp)
target_include_directories(test_HWM PUBLIC ../include)
target_link_libraries(test_HWM GTest::gtest_main)
gtest_discover_tests(test_HWM)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_executable(release_test_HWM release_test.cpp)
    target_include_directories(release_test_HWM PUBLIC ../include)
    target_link_libraries(release_test_HWM GTest::gtest_main)
    gtest_discover_tests(release_test_HWM)
endif()

