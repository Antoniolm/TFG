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

    transObject=new Matrix4f();
    transObject->translation(position.x,position.y,position.z);

    root=new NodeSceneGraph();
    root->add(transObject);
    root->add(materialCollect->getMaterial(mSPIKE));
    root->add(meshCollect->getMesh(SPIKE));

    currentTime=SDL_GetTicks();
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

    if(time-currentTime>200)
        currentTime=time-50;

    currentTime+=time-currentTime;
}
