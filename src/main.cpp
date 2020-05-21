#include <iostream>

#include "Menu.h"

int main() {
    DataReader dataReader;
    dataReader.readData("","16x16", onFoot);
    dataReader.displayGraph();
    dataReader.getGraph().BFS_Paths(5, 34, 10);
    getchar();
    //dataReader.getGraph().dfsAllPathsVisit(0, 1);
    //menu();

    return 0;
}

