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

#include "door.h"

Door::Door(const Value & doorFeatures,const vector<SoulCarrier*> & soulCarriers)
{
    position=vec4f(doorFeatures["position"][0].GetFloat(),doorFeatures["position"][1].GetFloat(),doorFeatures["position"][2].GetFloat(),1.0);
    sCarrier=soulCarriers[doorFeatures["soulCarrier"].GetFloat()];
    activated=false;

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    transMatrix=new Matrix4f();
    transMatrix->translation(position.x,position.y,position.z);

    root=new NodeSceneGraph();
    root->add(transMatrix);
    root->add(materialCollect->getMaterial(mDOOR));
    root->add(meshCollect->getMesh(DOOR));
    currentTime=SDL_GetTicks();
}

//**********************************************************************//

Door::~Door()
{
    delete root;
}

//**********************************************************************//

void Door::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void Door::updateState(GameState & gameState ){
    float time=gameState.time;

    if(time-currentTime>200) currentTime=time-50;

    //if hero is near of a soulCarrier and he push E -> SoulCarrier catch the soul in his arms
    if(sCarrier.){
        activated=true;
    }

    currentTime+=time-currentTime;
}

