cmake_minimum_required(VERSION 3.16)
project(TP2)

add_executable(
    bataille
    Card.cpp
    Card.hpp
    Player.cpp
    Player.hpp
    main.cpp
)

target_compile_features(bataille PRIVATE cxx_std_17)

target_compile_options(bataille PRIVATE -Wall -Wextra -Werror)