// *********************************************************************
// **
// ** Copyright (C) 2016-2017 Antonio David L�pez Machado
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************


#include "nodescenegraph.h"

NodeSceneGraph::NodeSceneGraph()
{
    currentTime=SDL_GetTicks();
}

//**********************************************************************//

NodeSceneGraph::NodeSceneGraph(const NodeSceneGraph & aNode){
    entrance=aNode.entrance;
}

//**********************************************************************//

NodeSceneGraph::~NodeSceneGraph()
{

}

//**********************************************************************//

void NodeSceneGraph::visualization(Context & cv){
    float time=SDL_GetTicks();

    int contMatrix=1;
    int contMaterial=0;
    cv.matrixStack.push();
    vector<EntryNGE>::iterator it;
    for(it=entrance.begin();it!=entrance.end();it++){
            switch((*it).type){
            case 0: //Object3d
                (*it).obj->visualization(cv);
                break;
            case 1: //Matrix4f
                cv.matrixStack.cMatrix((*(*it).matrix));
                contMatrix++;
                break;
            case 2: //Material
                cv.materialStack.push((*(*it).material));
                (*it).material->activate(&cv.currentShader);
                contMaterial++;
                break;
            }

    }
    cv.materialStack.pop(contMaterial);
    cv.materialStack.getMaterial().activate(&cv.currentShader);

    cv.matrixStack.pop(contMatrix);

    currentTime=time;
}

//**********************************************************************//

void NodeSceneGraph::updateState(float time){

}

//**********************************************************************//
void NodeSceneGraph::add(EntryNGE * anEntry){
    entrance.push_back(*anEntry);
}

//**********************************************************************//

void NodeSceneGraph::add(Object3D * anObject){
    EntryNGE newEntrance(anObject);
    entrance.push_back(newEntrance);
}

//**********************************************************************//
void NodeSceneGraph::add(Matrix4f * aMatrix){
    EntryNGE newEntrance(aMatrix);
    entrance.push_back(newEntrance);

}

//**********************************************************************//

void NodeSceneGraph::add(Material * aMaterial){
    EntryNGE newEntrance(aMaterial);
    entrance.push_back(newEntrance);

}

