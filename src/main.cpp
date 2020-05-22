#include <iostream>

#include "Menu.h"

int main() {
    DataReader dataReader;
    dataReader.readData("","4x4", onFoot);
    dataReader.displayGraph();
    dataReader.getGraph().dijkstraShortestPath(*dataReader.getGraph().findVertex(2), *dataReader.getGraph().findVertex(10));
    dataReader.getGraph().getPathTo(10);
    getchar();
    //dataReader.getGraph().dfsAllPathsVisit(0, 1);
    menu();

    return 0;
}

