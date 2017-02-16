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

#include "spiketrap.h"

SpikeTrap::SpikeTrap(const Value & spikeFeatures)
{
    position=vec4f(spikeFeatures["position"][0].GetFloat(),spikeFeatures["position"][1].GetFloat(),spikeFeatures["position"][2].GetFloat(),1.0);

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    Matrix4f * transObject=new Matrix4f();
    transObject->translation(position.x,position.y,position.z);

    transActivate=new Matrix4f();
    transActivate->identity();

    root=new NodeSceneGraph();
    root->add(transObject);
    root->add(transActivate);
    root->add(materialCollect->getMaterial(mSPIKE));
    root->add(meshCollect->getMesh(SPIKE));

    currentTime=SDL_GetTicks();
    hitDelay=currentTime;
    activated=false;
}

//**********************************************************************//

SpikeTrap::~SpikeTrap()
{
    delete root;
}


//**********************************************************************//

void SpikeTrap::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void SpikeTrap::updateState(GameState & gameState ){
    float time=gameState.time;
    RootMap * rootMap=gameState.rootMap;
    Hero * hero=rootMap->getHero();

    if(time-currentTime>200) currentTime=time-50;

    vec3f posHero=hero->getPosition();
    float distance=sqrt(pow(position.x-posHero.x,2.0)+pow(position.z-posHero.z,2.0));

    if(distance<=0.75 && (position.y>posHero.y-1 && position.y<posHero.y)){ //if hero is near of a disactivated trap
        activated=true;
    }

    if(distance>0.75){ //if hero is far of an activated trap
        activated=false;
    }

    if(activated){
        transActivate->translation(0.0,1.0,0.0);
        if(distance<=0.75 && (position.y>posHero.y-1 && position.y<posHero.y) && hitDelay<(time-200)){
            hero->takeDamage(-1);
            hitDelay=time;
        }
    }
    else transActivate->identity();

    currentTime+=time-currentTime;
}
