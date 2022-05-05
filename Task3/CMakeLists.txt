cmake_minimum_required(VERSION 3.20)
project(Task3)


include(buildconan/conanbuildinfo.cmake)
conan_basic_setup()


add_executable(Task3 main.cpp)
add_subdirectory(Currency)
add_subdirectory(Server)


target_link_libraries(
        Task3 PRIVATE Currency
)



target_link_libraries(
        Task3 PRIVATE Server
)

set_target_properties(
        Task3 PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)
