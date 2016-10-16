////////////////////////////////////////
//  Author: Antonio David López Machado
////////////////////////////////////////


#include "nodescenegraph.h"

NodeSceneGraph::NodeSceneGraph()
{

}

//**********************************************************************//

NodeSceneGraph::~NodeSceneGraph()
{

}

//**********************************************************************//

void NodeSceneGraph::visualization(Context & cv){
    vector<EntranceNGE>::iterator it;
    for(it=entrance.begin();it!=entrance.end();it++){
            switch((*it).type){
            case 0:
                (*it).obj->visualization(cv);
                break;
            case 1:
                glMultMatrixd((*it).matrix->getMatrix());
            }
    }
}

//**********************************************************************//

void NodeSceneGraph::updateState(float time){

}

//**********************************************************************//
void NodeSceneGraph::add(EntranceNGE * anEntrance){
    entrance.push_back(*anEntrance);
}

//**********************************************************************//

void NodeSceneGraph::add(Object3D * anObject){
    EntranceNGE newEntrance(anObject);
    entrance.push_back(newEntrance);
}

//**********************************************************************//
void NodeSceneGraph::add(Matrix4f * aMatrix){
    EntranceNGE newEntrance(aMatrix);
    entrance.push_back(newEntrance);

}
