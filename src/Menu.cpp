//
// Created by breno on 5/12/2020.
//

#include "Menu.h"
#include "GraphBuilder/Graph.h"
#include "GraphBuilder/Vertex.h"

DataReader dataReader;
User user;

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
    unsigned int option;

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
    cout << "   [2] Load User Info" << endl;
    cout << "   [0] BACK" << endl;
}

void showUserLoadOptions() {
    cout << "USER LOAD OPTIONS: " << endl;
    cout << "   [1] Change/Add User Name" << endl;
    cout << "   [2] Change/Add User Age" << endl;
    cout << "   [3] Add Preference" << endl;
    cout << "   [4] Insert Available time" << endl;
    cout << "   [0] BACK" << endl;
}

void showPreferenceSelection() {
    cout << "PREFERENCE SELECTION: " <<endl;
    cout << "   [1] Information" << endl;
    cout << "   [2] Hotel" << endl;
    cout << "   [3] Attraction" << endl;
    cout << "   [4] View Point" << endl;
    cout << "   [5] Guest House" << endl;
    cout << "   [6] Picnic Site" << endl;
    cout << "   [7] Artwork" << endl;
    cout << "   [8] Camp Site" << endl;
    cout << "   [9] Museum" << endl;
    cout << "   [10] *" << endl;
    cout << "   [0] BACK" << endl;
}
void choosePreferences() {
    unsigned int option;

    do{
        clear();
        showPreferenceSelection();
        readInt(option, "Option");
        switch(option){
            case 10:
                user.addPreference("*");
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 9:
                user.addPreference("Museum");
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 8:
                user.addPreference("Camp Site");
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 7:
                user.addPreference("Artwork");
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 6:
                user.addPreference("Picnic Site");
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 5:
                user.addPreference("Guest House");
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 4:
                user.addPreference("View Point");
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 3:
                user.addPreference("Attraction");
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 2:
                user.addPreference("Hotel");
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 1:
                user.addPreference("Information");
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 0:
                return;
            default:
                cout << "Invalid option..." << endl;
                cout << "Press any key to continue ...";
                getchar();
                break;
        }

    }while(true);
}

void showUserInfo() {
    cout << "USER INFO:" << endl;
    list <string> pref = user.getPreferences();
    cout << "   Name: " << user.getName() << endl;
    cout << "   Age: " << user.getAge() << endl;
    cout << "   Preferences:" <<endl;
    for(auto p: pref)
        cout << "   " << p << endl;
    cout << "   Available time:" <<endl;
}

void userLoadOptions(){
    unsigned int option;
    string aux;

    do{
        clear();
        showUserLoadOptions();
        readInt(option, "Option");
        switch(option){
            case 3:
                choosePreferences();
                break;
            case 2:
                clear();
                unsigned int age;
                readInt(age, "Age");
                user.setAge(age);
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 1:
                clear();
                cout << "Name ? ";
                getline(cin, aux);
                user.setName(aux);
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 4:
                clear();
                unsigned int time;
                cout << "Available time?";
                readInt(time,"Time");
                break;
            case 0:
                return;
            default:
                cout << "Invalid option..." << endl;
                cout << "Press any key to continue ...";
                getchar();
                break;
        }

    }while(true);
}

void userOptions(){
    unsigned int option;

    do{
        clear();
        showUserOptions();
        readInt(option, "Option");
        switch(option){
            case 2:
                userLoadOptions();
                break;
            case 1:
                showUserInfo();
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 0:
                return;
            default:
                cout << "Invalid option..." << endl;
                cout << "Press any key to continue ...";
                getchar();
                break;
        }

    }while(true);
}

void askForCity(string &city) {
    do{
        getline(cin, city);
        normalizeCity(city);
        if(city == "Aveiro" || city == "Braga" || city == "Coimbra" || city == "Ermesinde" || city == "Fafe" || city == "Gondomar" || city == "Lisboa" || city == "Maia" || city == "Porto"  || city == "Viseu")
            break;
        cout << "Invalid city name.";
    }while(true);
}

void showTourOptions(){
    cout << "TOUR OPTIONS: " << endl;
    cout << "   [1] New Tour" << endl;
    cout << "   [0] BACK" << endl;
}

void tourOptions(){
    unsigned int option;
    do{
        clear();
        showTourOptions();
        readInt(option, "Option");
        switch(option){
            case 1: {
                string city;
                dataReader.setRealMaps(true);
                cout << "Select the city to make a tour" << endl;
                askForCity(city);

                cout << "Loading city graph..." << endl;
                dataReader.readData(city, "");
                cout << "Graph loaded." << endl;
                //------90379617 122528348
                Graph g = dataReader.getGraph();
                Vertex *sv, *dv;
                do{
                    unsigned int src, dest;
                    readInt(src, "Select origin");
                    readInt(dest, "Select destination");

                    sv = dataReader.getGraph().findVertex(src);
                    dv = dataReader.getGraph().findVertex(dest);
                    if(dataReader.getGraph().findVertex(src)!=nullptr && dataReader.getGraph().findVertex(dest)!=nullptr)
                        break;
                    cout << "Invalid path." << endl;
                }while(true);

                dataReader.getGraph().dijkstraShortestPath(*sv, *dv);
                cout << "1";
                vector<int> path =  dataReader.getGraph().getPath(*sv, *dv);
                cout << "2";
                for(int i=0; i < path.size(); i++){
                    cout << g.findVertex(path.at(i))->getName() << "->";
                }
                cout << endl;

                //------
                cout << "Press any key to continue ...";
                getchar();
            }
            case 0:
                return;
            default:
                cout << "Invalid option..." << endl;
                cout << "Press any key to continue ...";
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
    unsigned int option;

    do{
        clear();
        showGraphOptions();
        readInt(option, "Option");

        switch(option){
            case 1:
                dataReader.displayGraph(750,750);
                break;
            case 2:
                chooseGraphOptions();
                break;
            case 0:
                return;
            default:
                cout << "Invalid option..." << endl;
                cout << "Press any key to continue ...";
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
    unsigned int option;

    do{
        clear();
        showGraphSelectionOptions();
        readInt(option, "Option");
        switch(option){
            case 1:
                dataReader.setRealMaps(false);
                dataReader.readData("","4x4");
                cout << "Graph Loaded..." << endl;
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 2:
                dataReader.setRealMaps(false);
                dataReader.readData("","8x8");
                cout << "Graph Loaded..." << endl;
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 3:
                dataReader.setRealMaps(false);
                dataReader.readData("","16x16");
                cout << "Graph Loaded..." << endl;
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 0:
                return;
            default:
                cout << "Invalid option..." << endl;
                cout << "Press any key to continue ...";
                getchar();
                break;
        }

    }while(true);
}

