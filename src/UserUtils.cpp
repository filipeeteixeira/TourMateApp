//
// Created by filip on 20/05/2020.
//

#include "UserUtils.h"

void showTags(GraphViewer* gv, const vector<Vertex*>& vertexes) {
    for(int i = 0; i < vertexes.size(); i++) {
        gv->setVertexColor(vertexes.at(i)->getId(), "yellow");
        gv->setVertexLabel(vertexes.at(i)->getId(), to_string(i+1));
        gv->setVertexSize(vertexes.at(i)->getId(), 40);
    }

    gv->rearrange();
}

void getStartPoint(User user, DataReader dataReader, string startTag) {
    dataReader.displayGraph(1900,1000);

    vector<Vertex*> tags;
    for(Vertex* vertex: dataReader.getGraph().getVertexSet()) {
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

    dataReader.getGraphViewer()->closeWindow();
    user.setUserSP(dataReader.getGraph().findVertex(startPoint));
}

