cmake_minimum_required(VERSION 3.16)
project(TP11)

add_executable(factory
    src/factory.cpp
)

target_compile_features(factory PRIVATE cxx_std_17)
target_compile_options(factory PRIVATE "-Wfatal-errors")

add_executable(string
    src/tostring.cpp
)

target_compile_features(string PRIVATE cxx_std_17)
target_compile_options(string PRIVATE "-Wfatal-errors")

if(WIN32)
    target_compile_definitions(grayscale PRIVATE "WINDOWS")
endif()