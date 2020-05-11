#include <iostream>

#include "DataReader.h"
#include "GraphBuilder/Vertex.h"
#include "GraphBuilder/Edge.h"

int main() {
    DataReader dataReader("../res/GridGraphs/4x4/nodes.txt", "../res/GridGraphs/4x4/edges.txt");
    dataReader.readData();
    dataReader.viewGraph();

    std::cout << "Press any key to continue ...";
    getchar();

    return 0;
}