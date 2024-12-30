cmake_minimum_required(VERSION 3.22.1)
project(diff)
file(GLOB SOURCES
    inc/*.h
    src/*.cpp
)
add_executable(diff main.cpp ${SOURCES}) 
target_include_directories(diff PRIVATE inc /)
target_compile_options(diff PRIVATE -march=native)
target_compile_options(diff PRIVATE -fconcepts)
#target_compile_options(rrtStarBaby PRIVATE - g)
