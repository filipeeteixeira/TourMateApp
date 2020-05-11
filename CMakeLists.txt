cmake_minimum_required(VERSION 3.15)
project(TourMateApp)

set(CMAKE_CXX_STANDARD 14)

link_libraries(ws2_32 wsock32)

include_directories(lib)

add_executable(TourMateApp src/main.cpp
        lib/connection.cpp lib/graphviewer.cpp src/DataReader.cpp src/DataReader.h src/GraphBuilder/Graph.h
        src/GraphBuilder/Vertex.h src/GraphBuilder/Edge.h src/GraphBuilder/Vertex.cpp src/GraphBuilder/Edge.cpp
        src/GraphBuilder/MutablePriorityQueue.h src/GraphBuilder/Graph.cpp src/Menu.cpp src/Menu.h src/Utils.h)

