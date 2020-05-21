#include <iostream>

#include "Menu.h"

int main() {
    DataReader dataReader;
    dataReader.readData("","4x4", onFoot);
    dataReader.getGraph().dfsAllPathsVisit(0, 1);
    //menu();

    return 0;
}

