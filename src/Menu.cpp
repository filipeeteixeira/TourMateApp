//
// Created by breno on 5/12/2020.
//

#include <string>
#include <iostream>
#include "Menu.h"
#include "Utils.h"
#include "DataReader.h"
#include "GraphBuilder/Vertex.h"
#include "GraphBuilder/Edge.h"

string nodesFilename = "../res/GridGraphs/4x4/nodes.txt";
string edgesFilename = "../res/GridGraphs/4x4/edges.txt";

using namespace std;

void showMainMenu(){
    cout << "......................." << endl;
    cout << "=====TOUR MATE APP=====" << endl;
    cout << "......................." << endl << endl;
    cout << "MAIN MENU: " << endl;
    cout << "   [1] User Settings" << endl;
    cout << "   [2] Tour" << endl;
    cout << "   [3] Graph Settings" << endl;
    cout << "   [0] Exit" << endl;
}

void menu(){
    int option;

    do{
        clear();
        showMainMenu();
        readInt(option, "Option");
        switch(option){
            case 1:
                userOptions();
                break;
            case 2:
                tourOptions();
                break;
            case 3:
                graphOptions();
                break;
            case 0:
                return;
            default:
                cout << "Invalid option..." << endl;
                break;
        }
    }while(true);
}

void showUserOptions(){
    cout << "USER OPTIONS: " << endl;
    cout << "   [1] Show User Info" << endl;
    cout << "   [0] BACK" << endl;
}

void userOptions(){
    int option;

    do{
        clear();
        showUserOptions();
        readInt(option, "Option");
        switch(option){
            case 1:
                cout << "To be done..." << endl;
                std::cout << "Press any key to continue ...";
                getchar();
                break;
            case 0:
                return;
            default:
                cout << "Invalid option..." << endl;
                std::cout << "Press any key to continue ...";
                getchar();
                break;
        }

    }while(true);
}

void showTourOptions(){
    cout << "TOUR OPTIONS: " << endl;
    cout << "   [1] New Tour" << endl;
    cout << "   [0] BACK" << endl;
}

void tourOptions(){
    int option;
    do{
        clear();
        showTourOptions();
        readInt(option, "Option");
        switch(option){
            case 1:
                cout << "To be done..." << endl;
                std::cout << "Press any key to continue ...";
                getchar();
            case 0:
                return;
            default:
                cout << "Invalid option..." << endl;
                std::cout << "Press any key to continue ...";
                getchar();
                break;
        }

    }while(true);
}

void showGraphOptions(){
    cout << "GRAPH OPTIONS: " << endl;
    cout << "   [1] Show Graph" << endl;
    cout << "   [2] Load Graph" << endl;
    cout << "   [0] BACK" << endl;
}

void graphOptions(){
    int option;

    do{
        clear();
        showGraphOptions();
        DataReader dataReader(nodesFilename, edgesFilename);
        readInt(option, "Option");

        switch(option){
            case 1:

                dataReader.readData();
                dataReader.viewGraph();
                break;
            case 2:
                chooseGraphOptions();
                break;
            case 0:
                return;
            default:
                cout << "Invalid option..." << endl;
                std::cout << "Press any key to continue ...";
                getchar();
                break;
        }

    }while(true);
}

void showGraphSelectionOptions(){
    cout << "GRAPH SELECTION: " << endl;
    cout << "   [1] 4x4" << endl;
    cout << "   [2] 8x8" << endl;
    cout << "   [3] 16x16" << endl;
    cout << "   [0] BACK" << endl;
}


void chooseGraphOptions() {
    int option;

    do{
        clear();
        showGraphSelectionOptions();
        readInt(option, "Option");
        switch(option){
            case 1:
                nodesFilename = "../res/GridGraphs/4x4/nodes.txt";
                edgesFilename = "../res/GridGraphs/4x4/edges.txt";
                cout << "Graph Loaded..." << endl;
                std::cout << "Press any key to continue ...";
                getchar();
                break;
            case 2:
                nodesFilename = "../res/GridGraphs/8x8/nodes.txt";
                edgesFilename = "../res/GridGraphs/8x8/edges.txt";
                cout << "Graph Loaded..." << endl;
                std::cout << "Press any key to continue ...";
                getchar();
                break;
            case 3:
                nodesFilename = "../res/GridGraphs/16x16/nodes.txt";
                edgesFilename = "../res/GridGraphs/16x16/edges.txt";
                cout << "Graph Loaded..." << endl;
                std::cout << "Press any key to continue ...";
                getchar();
                break;
            case 0:
                return;
            default:
                cout << "Invalid option..." << endl;
                std::cout << "Press any key to continue ...";
                getchar();
                break;
        }

    }while(true);
}

