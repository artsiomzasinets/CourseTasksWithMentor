cmake_minimum_required(VERSION 3.23)
project(Currency)


set(HEADERS Currency.h)
set(SOURCES Currency.cpp)

add_library(Currency STATIC ${HEADERS} ${SOURCES})


set_target_properties(
        Currency PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

