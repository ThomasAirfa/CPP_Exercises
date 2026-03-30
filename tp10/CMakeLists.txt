cmake_minimum_required(VERSION 3.16)
project(TP10)

add_executable(grayscale
    src/grayscale.cpp
    lib/image_lib.cpp
)

add_executable(mandelbrot
    src/mandelbrot.cpp
    lib/image_lib.cpp
)
add_executable(gray
    src/gray.cpp
    lib/image_lib.cpp
)

target_compile_features(grayscale PRIVATE cxx_std_17)
target_compile_options(grayscale PRIVATE "-Wfatal-errors")

target_compile_features(mandelbrot PRIVATE cxx_std_17)
target_compile_options(mandelbrot PRIVATE "-Wfatal-errors")

target_compile_features(gray PRIVATE cxx_std_17)
target_compile_options(gray PRIVATE "-Wfatal-errors")

if(WIN32)
    target_compile_definitions(grayscale PRIVATE "WINDOWS")
endif()