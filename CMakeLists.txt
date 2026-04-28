cmake_minimum_required(VERSION 3.25)
project(example C)

file(GLOB SOURCES 
    src/*.c
)

add_executable(main ${SOURCES})

target_include_directories(main PRIVATE src)
