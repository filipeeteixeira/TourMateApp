//
// Created by filip on 20/05/2020.
//

#include <algorithm>
#include "UserUtils.h"

void showTags(GraphViewer* gv, const vector<Vertex*>& vertexes) {
    for(int i = 0; i < vertexes.size(); i++) {
        gv->setVertexColor(vertexes.at(i)->getId(), "yellow");
        gv->setVertexLabel(vertexes.at(i)->getId(), to_string(i));
        gv->setVertexSize(vertexes.at(i)->getId(), 20);
    }

    gv->rearrange();
}

void getStartPoint(User &user, DataReader &dataReader, string startTag) {
    cout << "Loading..." <<endl;

    //dataReader.displayGraph();

    vector<Vertex*> tags;
    for(Vertex* vertex: dataReader.getGraph()->getVertexSet()) {
        //dataReader.getGraphViewer()->setVertexSize(vertex->getId(), 0);
        if(vertex->getTag() == startTag)
            tags.push_back(vertex);
    }
    //showTags(dataReader.getGraphViewer(), tags);

    unsigned int startPoint;
    do{
        readInt(startPoint,"What is your location id");

        if(startPoint<=tags.size() && startPoint>=1)
            break;
        cout << "Invalid point." << endl;
    }while(true);

    user.setUserSP(tags.at(startPoint));
}

void getEndPoint(User &user, DataReader &dataReader, string endTag) {
    cout << "Loading..." << endl;

    vector<Vertex*> tags;
    for(Vertex* vertex: dataReader.getGraph()->getVertexSet()) {
        //dataReader.getGraphViewer()->setVertexSize(vertex->getId(), 0);
        //dataReader.getGraphViewer()->clearVertexLabel(vertex->getId());
        if(vertex->getTag() == endTag)
            tags.push_back(vertex);
    }

    //showTags(dataReader.getGraphViewer(), tags);

    //dataReader.getGraphViewer()->setVertexColor(user.getUserSP()->getId(),"green");
    //dataReader.getGraphViewer()->setVertexSize(user.getUserSP()->getId(),20);
    //dataReader.getGraphViewer()->setVertexLabel(user.getUserSP()->getId(),"START");

    //dataReader.getGraphViewer()->rearrange();

    unsigned int endPoint;
    do{
        readInt(endPoint,"What is your end point id");

        if(endPoint<=tags.size() && endPoint>=1)
            break;
        cout << "Invalid point." << endl;
    }while(true);

    user.setUserEP(tags.at(endPoint));

    //for(Vertex* vertex: dataReader.getGraph()->getVertexSet()) {
    //    dataReader.getGraphViewer()->setVertexSize(vertex->getId(), 1);
    //    dataReader.getGraphViewer()->clearVertexLabel(vertex->getId());
    //}
}

/*
//return number of preferences in path
int checkIfPathHasUserPreferences(User &user, DataReader &dataReader, Path*  path){
    int total = 0;
    for(auto i: path->getPath()){
        for(const auto& preference: user.getPreferences())
            if(dataReader.getGraph().findVertex(i)->getTag() == preference) total++;
    }
    return total;
}

bool comparePaths(Path* path1, Path* path2){
    return checkIfPathHasUserPreferences(path1) > checkIfPathHasUserPreferences(path2);
}

void sortByUserPreferences(vector<Path*> & paths){
    sort(paths.begin(), paths.end(), comparePaths);
}*/