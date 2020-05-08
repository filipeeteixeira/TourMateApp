cmake_minimum_required(VERSION 3.15)
project(TourMateApp)

set(CMAKE_CXX_STANDARD 14)

link_libraries(ws2_32 wsock32)

include_directories(lib)
add_executable(TourMateApp src/main.cpp)