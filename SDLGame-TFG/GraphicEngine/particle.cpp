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

#include "particle.h"

Particle::Particle()
{
    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    transMatrix=new Matrix4f();
    transMatrix->identity();

    Matrix4f * scaleCube=new Matrix4f();
    scaleCube->scale(0.3,1,1.0);

    root=new NodeSceneGraph();
    NodeSceneGraph * cubeNode=new NodeSceneGraph();
    cubeNode->add(transMatrix);
    cubeNode->add(scaleCube);
    cubeNode->add(materialCollect->getMaterial(mWOOD));
    cubeNode->add(meshCollect->getMesh(TEXT));
    root->add(cubeNode);
    currentTime=SDL_GetTicks();
}

//**********************************************************************//

Particle::Particle(vec3f minPos,vec3f maxPos,vec3f aVelocity,float minTime,float maxTime){
    position.x=minPos.x + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxPos.x-minPos.x)));
    position.y=minPos.y + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxPos.y-minPos.y)));
    position.z=minPos.z + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxPos.z-minPos.z)));
    velocity=aVelocity;
    remainingTime= minTime + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxTime-minTime)));

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    transMatrix=new Matrix4f();
    transMatrix->translation(position.x,position.y,position.z);

    Matrix4f * scaleCube=new Matrix4f();
    scaleCube->scale(0.1,0.3,1.0);

    root=new NodeSceneGraph();
    NodeSceneGraph * cubeNode=new NodeSceneGraph();
    cubeNode->add(transMatrix);
    cubeNode->add(scaleCube);
    cubeNode->add(materialCollect->getMaterial(mWOOD));
    cubeNode->add(meshCollect->getMesh(TEXT));
    root->add(cubeNode);
    currentTime=SDL_GetTicks();
}

//**********************************************************************//

Particle::~Particle()
{
    //dtor
}

//**********************************************************************//

void Particle::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void Particle::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap){
    //update the position
    LinearMovement lineMove(velocity);
    transMatrix->product(lineMove.updateState(time-currentTime).getMatrix());

    remainingTime-=(time-currentTime);
    currentTime+=(time-currentTime);
}

//**********************************************************************//

float Particle::getRemainingTime(){
    return remainingTime;
}

