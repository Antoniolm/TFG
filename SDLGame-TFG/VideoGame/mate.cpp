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

#include "mate.h"

Mate::Mate(vec3f aPosition)
{
    position=vec4f(aPosition.x,aPosition.y,aPosition.z,1.0);

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    moveAvatar=new Matrix4f();
    moveAvatar->translation(position.x,position.y+0.8,position.z-4.0);

    root=new NodeSceneGraph();
    root->add(moveAvatar);
    root->add(materialCollect->getMaterial(mMATE));
    root->add(meshCollect->getMesh(MATEHEAD));
    currentTime=SDL_GetTicks();

}

//**********************************************************************//

Mate::~Mate()
{
    delete root;
    delete moveAvatar;
}

//**********************************************************************//

void Mate::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void Mate::updateState(float time,ControllerManager * controller,RootMap * rootMap ){
    Hero * hero=rootMap->getHero();
    vec3f posHero=hero->getPosition();

    currentMove=nextPosition(posHero);
    moveMate(time,currentMove.second,currentMove.first);
    position=moveAvatar->product(vec4f());
    currentTime+=time-currentTime;
}

//**********************************************************************//

void Mate::moveMate(float time,vec3f aMove,avatarDirection aDir){
    if(direction!=aDir){
        position=moveAvatar->product(vec4f());
        Matrix4f transHero;
        transHero.translation(position.x,position.y,position.z);
        LinearMovement lineMove(aMove);
        transHero.product(lineMove.updateState(time-currentTime).getMatrix());

        moveAvatar->rotation(45*aDir,0.0f,1.0f,0.0f);
        moveAvatar->product(transHero.getMatrix());

        direction=aDir;
    }
    else{
        LinearMovement lineMove(aMove);
        moveAvatar->product(lineMove.updateState(time-currentTime).getMatrix());
    }
}

//**********************************************************************//

pair<avatarDirection,vec3f> Mate::nextPosition(vec3f posHero){

    vec3f newMovement;
    float distance,minDistance;
    pair<avatarDirection,vec3f> result;

    if(sqrt(pow(position.x-posHero.x,2.0)+pow(position.z-posHero.z,2.0))<0.8){
        result.first=currentMove.first;
        result.second=vec3f(0.0f,0.0f,0.0f);
        return result;
    }

    //Case -> Default
    newMovement.x=position.x;newMovement.y=position.y;newMovement.z=position.z;
    result.first=FORWARD;
    result.second=vec3f(0.0f,0.0f,0.0f);
    minDistance=1000.0;

    //Case -> Leftward
    newMovement.x=position.x-2.0;newMovement.y=position.y;newMovement.z=position.z;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance ){ //If Rightward will be our move -> The distance is smallest between them
        result.first=LEFTWARD;
        result.second=vec3f(-2.0f,0.0f,0.0f);
        minDistance=distance;
    }


    //Case -> Rightward
    newMovement.x=position.x+2.0;newMovement.z=position.z;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance){ //If Rightward will be our move -> The distance is smallest between them
        result.first=RIGHTWARD;
        result.second=vec3f(2.0f,0.0f,0.0f);
        minDistance=distance;
    }

    //Case -> Backward
    newMovement.x=position.x;newMovement.z=position.z-2.0;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance){ //If Backward will be our move -> The distance is smallest between them
        result.first=BACKWARD;
        result.second=vec3f(0.0f,0.0f,-2.0f);
        minDistance=distance;
    }

    //Case -> Forward
    newMovement.x=position.x;newMovement.z=position.z+2.0;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance){ //If Forward will be our move -> The distance is smallest between them
        result.first=FORWARD;
        result.second=vec3f(0.0f,0.0f,2.0f);
        minDistance=distance;
    }

    //Case -> Left-forward
    newMovement.x=position.x-1.0;newMovement.z=position.z+1.0;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance){ //If Left-forward will be our move -> The distance is smallest between them
        result.first=FOR_LEFTWARD;
        result.second=vec3f(-1.0f,0.0f,1.0f);
        minDistance=distance;
    }

    //Case -> Right-forward
    newMovement.x=position.x+1.0;newMovement.z=position.z+1.0;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance){ //If Right-forward will be our move -> The distance is smallest between them
        result.first=FOR_RIGHTWARD;
        result.second=vec3f(+1.0f,0.0f,+1.0f);
        minDistance=distance;
    }

    //Case -> Left-backward
    newMovement.x=position.x-1.0;newMovement.z=position.z-1.0;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance){ //If Left-backward will be our move -> The distance is smallest between them
        result.first=BACK_LEFTWARD;
        result.second=vec3f(-1.0f,0.0f,-1.0f);
        minDistance=distance;
    }

    //Case -> Right-backward
    newMovement.x=position.x+1.0;newMovement.z=position.z-1.0;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance){ //If Right-backward will be our move -> The distance is smallest between them
        result.first=BACK_RIGHTWARD;
        result.second=vec3f(1.0f,0.0f,-1.0f);
        minDistance=distance;
    }

    return result;
}


