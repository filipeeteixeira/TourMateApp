//
// Created by filip on 20/05/2020.
//

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

    dataReader.displayGraph();

    vector<Vertex*> tags;
    for(Vertex* vertex: dataReader.getGraph().getVertexSet()) {
        dataReader.getGraphViewer()->setVertexSize(vertex->getId(), 0);
        if(vertex->getTag() == startTag)
            tags.push_back(vertex);
    }
    showTags(dataReader.getGraphViewer(), tags);

    unsigned int startPoint;
    do{
        readInt(startPoint,"What is your location id");

        if(startPoint<=tags.size() && startPoint>=1)
            break;
        cout << "Invalid point." << endl;
    }while(true);

    //dataReader.getGraphViewer()->closeWindow();
    user.setUserSP(tags.at(startPoint));
    cout << user.getUserSP()->getId()<< endl;
    //delete dataReader.getGraphViewer();
}

void getEndPoint(User &user, DataReader &dataReader, string endTag) {
    cout << "Loading..." << endl;
    //dataReader.displayGraph();
    cout << user.getUserSP()->getId()<< endl;

    vector<Vertex*> tags;
    for(Vertex* vertex: dataReader.getGraph().getVertexSet()) {
        dataReader.getGraphViewer()->setVertexSize(vertex->getId(), 0);
        if(vertex->getTag() == endTag)
            tags.push_back(vertex);
    }

    dataReader.getGraphViewer()->setVertexColor(user.getUserSP()->getId(),"green");
    dataReader.getGraphViewer()->setVertexSize(user.getUserSP()->getId(),20);
    dataReader.getGraphViewer()->setVertexLabel(user.getUserSP()->getId(),"START");

    showTags(dataReader.getGraphViewer(), tags);

    dataReader.getGraphViewer()->rearrange();

    unsigned int endPoint;
    do{
        readInt(endPoint,"What is your end point id");

        if(endPoint<=tags.size() && endPoint>=1)
            break;
        cout << "Invalid point." << endl;
    }while(true);

    dataReader.getGraphViewer()->closeWindow();
    user.setUserEP(tags.at(endPoint));
}