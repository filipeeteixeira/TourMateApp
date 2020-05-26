#include <iostream>
#include <chrono>
#include "Menu.h"

#include <fstream>
#include <sstream>
#include <random>
#include <time.h>
#include <chrono>

void geneateRandomGridGraph(int n, Graph & g) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, n);

    string idx;
    for (int i = 10; i < n + 10; i++)
        for (int j = 10; j < n + 10; j++) {
            idx = to_string(i) + to_string(j);
            g.addVertex(stoi(idx), i, j);
            //cout << stoi(idx) << endl;
        }
    //cout <<"===============================" << endl;
    for (int i = 10; i < n + 10; i++)
        for (int j = 10; j < n + 10; j++)
            for (int di = -1; di <= 1; di++)
                for (int dj = -1; dj <= 1; dj++)
                    if ((di != 0) != (dj != 0) && i+di >= 10 && i+di < n + 10 && j+dj >= 10 && j+dj < n + 10){

                        g.addEdge(stoi(to_string(i) + to_string(j)), stoi(to_string(i+di) + to_string(j+dj)), dis(gen));

                        //cout << stoi(to_string(i) + to_string(j)) << " -> " << stoi(to_string(i+di) + to_string(j+dj))<< endl;
                    }
}
int main() {

    ofstream(csv_file);
    csv_file.open("dfs_performance.csv ");
    csv_file <<  "dfs processing grid, average time (micro-seconds)" << endl;

    for (int n = 10; n <= 170; n += 10) {
        Graph g;
        cout << "dfs generating grid " << n << " x " << n << " ..." << endl;
        geneateRandomGridGraph(n, g);
        cout << "dfs processing grid " << n << " x " << n << " ..." << endl;
        auto start = std::chrono::high_resolution_clock::now();
        g.dfs();
        //g.YenKSP(1010, stoi(to_string(10+n-1) + to_string(10+n-1)), 10000000, onFoot);
        auto finish = std::chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::microseconds>(finish - start).count();
        cout << "dfs processing grid " << n << " x " << n << " average time (micro-seconds)=" << elapsed << endl;
        csv_file << n << "," << (elapsed / (n*n))  << endl;
    }
    csv_file.close();

    //menu();
    return 0;
}
