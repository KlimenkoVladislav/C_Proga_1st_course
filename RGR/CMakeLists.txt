cmake_minimum_required(VERSION 3.10)
project(RGR)

set(CMAKE_CXX_STANDARD 11)
add_executable(rgr 
        main.cpp
        algorithms.cpp
        math.cpp
        messages.cpp
)

target_link_libraries(rgr m)