cmake_minimum_required(VERSION 3.23)
project(Server)

set(HEADERS Server.h)
set(SOURCES Server.cpp main.cpp)

include(../buildconan/conanbuildinfo.cmake)
conan_basic_setup()


add_executable(Server  ${HEADERS} ${SOURCES})

include_directories(../Currency)
target_link_libraries(Server  ../Currency)

target_link_libraries(Server ${CONAN_LIBS})

if(MINGW)
    target_link_libraries(Server ws2_32)
endif()

set_target_properties(
        Server PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)