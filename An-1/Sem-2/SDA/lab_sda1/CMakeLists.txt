cmake_minimum_required(VERSION 3.30)
project(lab_sda1)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(lab_sda1 main.cpp
               Colectie.cpp
               IteratorColectie.cpp
               TestExtins.cpp
               TestScurt.cpp
               Colectie.h
               IteratorColectie.h
               TestExtins.h
               TestScurt.h

 )
