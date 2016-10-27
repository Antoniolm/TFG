// *********************************************************************
// **
// ** Copyright (C) 2016-2017 Antonio David López Machado
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

NodeSceneGraph::~NodeSceneGraph()
{

}

//**********************************************************************//

void NodeSceneGraph::visualization(Context & cv){
    float time=SDL_GetTicks();

    cv.matrixStack.push();
    vector<EntranceNGE>::iterator it;
    for(it=entrance.begin();it!=entrance.end();it++){
            switch((*it).type){
            case 0:
                (*it).obj->visualization(cv);
                break;
            case 1:
                if(!cv.visualization_static)
                    cv.matrixStack.cMatrix((*(*it).matrix).updateState(time));
                break;
            }
    }
    cv.matrixStack.pop();
    currentTime=time;
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
void NodeSceneGraph::add(Matrix4fDinamic * aMatrix){
    EntranceNGE newEntrance(aMatrix);
    entrance.push_back(newEntrance);

}
