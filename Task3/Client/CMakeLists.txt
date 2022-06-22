cmake_minimum_required(VERSION 3.20)
project(client)


include(../buildconan/conanbuildinfo.cmake) # add this before executable files!!!
conan_basic_setup()

add_executable(client main.cpp client.cpp client.h)


target_link_libraries(client ${CONAN_LIBS})

if(MINGW)
    target_link_libraries(client ws2_32)
endif()


set_target_properties(
        client PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)
