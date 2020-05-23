#include <iostream>

#include "Menu.h"

int main() {
    DataReader dataReader;
    dataReader.readData("","16x16", onFoot);
    //dataReader.displayGraph();
    //getchar();
    menu();
    dataReader.getGraph().dijkstraShortestPath(*dataReader.getGraph().findVertex(2), *dataReader.getGraph().findVertex(10));
    dataReader.getGraph().getPathTo(10);
    dataReader.displayGraph();
    vector<Path *>  A = dataReader.getGraph().YenKSP(0, 200, 100);

    for(auto path: A){
        for(int id: path->getPath())
            cout<<id<<" ";
        cout <<endl;
    }
    //dataReader.getGraph().dfsAllPathsVisit(0, 1);
   // menu();
    getchar();
    return 0;
}

