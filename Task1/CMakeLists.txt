cmake_minimum_required(VERSION 3.21)
project(Task1)


add_executable(Task1 main.cpp)

set_target_properties(
        Task1 PROPERTIES
        CXX_STANDARD 20 #требуемый стандарт
        CXX_STANDARD_REQUIRED ON # если нет компилятора 20 выводиться ошибка
)
