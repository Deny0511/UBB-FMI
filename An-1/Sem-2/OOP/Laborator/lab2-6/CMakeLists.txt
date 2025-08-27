cmake_minimum_required(VERSION 3.10)
project(lab2_6 C)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

add_executable(lab2_6
        main.c
        validator.c
        Cheltuieli.c
        teste.c
        repo.c
        service.c
        ui.c
)
