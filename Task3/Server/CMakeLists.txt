cmake_minimum_required(VERSION 3.23)
project(Server)

set(HEADERS Server.h)
set(SOURCES Server.cpp)

add_library(Server STATIC ${HEADERS} ${SOURCES})


set_target_properties(
        Server PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)