cmake_minimum_required(VERSION 3.21)
project(Task2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(build/conanbuildinfo.cmake)
conan_basic_setup()


add_executable(Task2 main.cpp)

include_directories(redBlackTree_lib)
add_subdirectory(redBlackTree_lib)

target_link_libraries(Task2 redBlackTree_lib)

add_subdirectory(testCatch2)