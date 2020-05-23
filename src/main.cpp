#include <iostream>

#include "Menu.h"

int main() {
    DataReader dataReader;
    dataReader.readData("","4x4", onFoot);
    dataReader.displayGraph();
    dataReader.getGraph().dijkstraShortestPath(*dataReader.getGraph().findVertex(2), *dataReader.getGraph().findVertex(10));
    dataReader.getGraph().getPathTo(10);
    vector<vector<int>>  A = dataReader.getGraph().YenKSP(2, 10, 10);

    for(auto path: A){
        for(int id: path)
            cout<<id<<" ";
        cout <<endl;
    }
    //dataReader.getGraph().dfsAllPathsVisit(0, 1);
   // menu();
    getchar();
    return 0;
}

