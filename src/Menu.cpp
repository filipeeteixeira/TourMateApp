
//
// Created by breno on 5/12/2020.
//

#include <algorithm>
#include <chrono>
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
                user.addPreference("museum");
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 8:
                user.addPreference("camp_site");
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 7:
                user.addPreference("artwork");
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 6:
                user.addPreference("picnic_site");
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 5:
                user.addPreference("guest_house");
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 4:
                user.addPreference("viewpoint");
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 3:
                user.addPreference("attraction");
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 2:
                user.addPreference("hotel");
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 1:
                user.addPreference("information");
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

void showTagsOptions(){
    cout << "TAG OPTIONS: " << endl;
    cout << "   [1] Generic" << endl;
    cout << "   [2] Museum" << endl;
    cout << "   [3] Camp site" << endl;
    cout << "   [4] Artwork" << endl;
    cout << "   [5] Picnic Site" << endl;
    cout << "   [6] Guest House" << endl;
    cout << "   [7] ViewPoint" << endl;
    cout << "   [8] Attraction" << endl;
    cout << "   [9] Information" << endl;
    cout << "   [10] Hotel" << endl;
}

string chooseTag(string msg) {
    unsigned int option;

    do{
        clear();
        showTagsOptions();
        readInt(option, msg);
        switch(option){
            case 1:
                return "*";
            case 2:
                return "museum";
            case 3:
                return "camp_site";
            case 4:
                return "artwork";
            case 5:
                return "picnic_site";
            case 6:
                return "guest_house";
            case 7:
                return "viewpoint";
            case 8:
                return "attraction";
            case 9:
                return "information";
            case 10:
                return "hotel";
            default:
                cout << "Invalid option..." << endl;
                cout << "Press any key to continue ...";
                getchar();
                break;
        }

    }while(true);
}

/*
 * ================================================================================================
 * USER PREFERENCES
 * ================================================================================================
 */

//return number of preferences in path
int checkIfPathHasUserPreferences(Path*  path){
    int total = 0;
    for(auto i: path->getPath()){
        for(const auto& preference: user.getPreferences())
            if(dataReader.getGraph().findVertex(i)->getTag() == preference) total++;
    }
    return total;
}

bool comparePaths(Path* path1, Path* path2){
    return path1->preferences > path2->preferences;
}

void sortByUserPreferences(vector<Path*> & paths){
    sort(paths.begin(), paths.end(), comparePaths);
}

/*
 * ================================================================================================
 *
 * ================================================================================================
 */

void showRecommendedPaths(vector<Path*> paths){
    cout << "Loading recommendations..." << endl;
    if(paths.empty()){
        cout << "No recommendations found..." << endl;
        return;
    }
    sortByUserPreferences(paths);
    dataReader.showPath(paths[0], user);
    cout << endl  << "Expected Time: " ;
    outputHoursAndMinutes(paths[0]->getWeight());
    cout << endl;
    cout << "User preferences in path: " << paths[0]->preferences << endl;
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
                double time;
                dataReader.setRealMaps(true);
                readDouble(time, "Available time (in hours)");
                user.setAvailableTime(time);
                chooseTransport();
                clear();
                //cout << "Select the city to make a tour" << endl;
                //askForCity(city);

                cout << "Loading city graph..." << endl;
                dataReader.readData(city, "",user.transport);
                cout << "Graph loaded." << endl;

                Graph g = dataReader.getGraph();
                if(g.stronglyConnected())
                    cout << "Graph Strongly Connected: " << "Yes" << endl;
                else
                    cout << "Graph Strongly Connected: " << "No" << endl;
                sleep(2);

                getStartPoint(user, dataReader,chooseTag("Where are you"));
                getEndPoint(user, dataReader,chooseTag("Where do you want to end the tour"));

                cout << "Finding the best path for you..." << endl;

                if(user.transport == metro){
                    Path* sourceToTransport;
                    Path* transportToDest;
                    int transportSP = dataReader.getGraph().dijkstraShortestPathToTransport(*user.getUserSP());
                    sourceToTransport =  dataReader.getGraph().getPathTo(transportSP, user);
                    int transportEP = dataReader.getGraph().dijkstraShortestPathToTransport(*user.getUserEP());
                    transportToDest =  dataReader.getGraph().getPathTo(transportEP, user);

                    showRecommendedPaths(dataReader.getGraph().YenKSP(user.getUserSP()->getId(), transportSP, (user.getAvailableTime()-sourceToTransport->getWeight())/2.0, user, 15));
                    cout << "->>>>>Go to " << dataReader.getGraph().findVertex(transportSP)->getTag() << " station<<<<<-" << endl;

                    showRecommendedPaths(dataReader.getGraph().YenKSP(transportEP, user.getUserEP()->getId(), (user.getAvailableTime()-transportToDest->getWeight())/2.0, user, 15));
                    cout << "->>>>>Leave on " << dataReader.getGraph().findVertex(transportEP)->getTag() << " station<<<<<-" << endl;
                }
                else
                    showRecommendedPaths(dataReader.getGraph().YenKSP(user.getUserSP()->getId(), user.getUserEP()->getId(), user.getAvailableTime(), user, 15));

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

void showTransportOption(){
    cout << "HOW DO YOU WANT TO GO TO YOUR DESTINATION: " << endl;
    cout << "   [1] On foot" << endl;
    cout << "   [2] Car" << endl;
    cout << "   [3] Metro" << endl;
}

void chooseTransport(){
    unsigned int option;
    do{
        clear();
        showTransportOption();
        readInt(option, "Option");

        switch(option){
            case 1:
                user.transport = onFoot;
                return;
            case 2:
                user.transport = car;
                return;
            case 3:
                user.transport = metro;
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
    cout << "   [3] Test Yen's Algorithm" << endl;
    cout << "   [0] BACK" << endl;
}

void graphOptions(){
    unsigned int option;

    do{
        clear();
        showGraphOptions();
        readInt(option, "Option");

        switch(option){
            default:
                cout << "Invalid option..." << endl;
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 0:
                return;
            case 1:
                dataReader.displayGraph();
                break;
            case 2:
                chooseGraphOptions();
                break;
            case 3:
                if(dataReader.getFileNameXY() == ""){
                    clear();
                    cout << "There is no grid graph loaded! Load one in Load Graph menu." << endl;
                    cout << "Press any key to continue ...";
                    getchar();
                    break;
                }
                chooseYenOptions();
                auto g = dataReader.getGraph();
                User user;/*
                for (int k = 10; k <= 100; k += 10) {
                    Graph g;
                    cout << "Generating "<< k << " paths." << endl;
                    cout << "Generating "<< k << " paths." << endl;
                    auto start = std::chrono::high_resolution_clock::now();
                    g.YenKSP(1010, stoi(to_string(10+n-1) + to_string(10+n-1)), 10000000, user);
                    auto finish = std::chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(finish - start).count();
                    cout << "dfs processing grid " << n << " x " << n << " average time (micro-seconds)=" << elapsed << endl;
                    csv_file << n << "," << (elapsed / (n*n))  << endl;
                }*/
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
                dataReader.readData("","4x4",user.transport);
                cout << "Graph Loaded..." << endl;
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 2:
                dataReader.setRealMaps(false);
                dataReader.readData("","8x8",user.transport);
                cout << "Graph Loaded..." << endl;
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 3:
                dataReader.setRealMaps(false);
                dataReader.readData("","16x16",user.transport);
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

void showYenOptions() {
    cout << "Yen Test Options: " << endl;
    cout << "   [1] Test Yen Time" << endl;
    cout << "   [2] Show Resulting Paths" << endl;
    cout << "   [0] BACK" << endl;
}

void chooseYenOptions() {
    unsigned int option;

    do{
        clear();
        showYenOptions();
        readInt(option, "Option");
        switch(option){
            case 0:
                return;
            default:
                cout << "Invalid option..." << endl;
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 1:
                int dest_;
                for(int k = 10; k<=100; k+=10) {
                    cout << "Generating "<< k << " paths." << endl;
                    auto start = std::chrono::high_resolution_clock::now();
                    if(dataReader.getFileNameXY() == "../res/GridGraphs/4x4/nodes.txt")
                        dest_ = 15;
                    else if(dataReader.getFileNameXY() == "../res/GridGraphs/8x8/nodes.txt")
                        dest_ = 55;
                    else
                        dest_ = 255;
                    dataReader.getGraph().YenKSP(0, dest_, INF, user, k);

                    auto finish = std::chrono::high_resolution_clock::now();
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(finish - start).count();
                    cout << k << " paths generation average time (micro-seconds)=" << elapsed << endl;
                }
                cout << "Press any key to continue ...";
                getchar();
                break;
            case 2:
                int dest;
                unsigned int k;
                vector <Path *> paths;
                readInt(k,"How many paths do you wish to see");
                Graph g;
                g = dataReader.getGraph();
                if(dataReader.getFileNameXY() == "../res/GridGraphs/4x4/nodes.txt")
                    dest = 15;
                else if(dataReader.getFileNameXY() == "../res/GridGraphs/8x8/nodes.txt")
                    dest = 55;
                else
                    dest = 255;

                paths = g.YenKSP(0, dest, INF, user, k);
                clear();
                cout << "Paths between the nodes 0 and "<< dest << ":" << endl;
                for(auto path : paths){
                    for(auto p : path->getPath())
                        cout<<p<<" ";
                    cout<<endl;
                }
                cout << "Press any key to continue ...";
                getchar();
                break;

        }

    }while(true);
}