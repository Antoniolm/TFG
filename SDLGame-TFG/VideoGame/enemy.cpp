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

#include "enemy.h"

Enemy::Enemy(vec3f aPosition,vec3f aRadioActivity)
{
    position=vec4f(aPosition.x,aPosition.y,aPosition.z,1.0);
    radioActivity=aRadioActivity;

    acceleratedMove=new AcceleratedMovement();
    acceleratedMove->resetState();
    direction=FORWARD;
    isMoving=false;
    isFalling=false;
    isJumping=false;
    enemyActivate=false;

    Mesh * cubeObject=new Mesh("geometries/cube.obj");
    cubeObject->init();

    moveAvatar=new Matrix4f();
    moveAvatar->translation(position.x,position.y,position.z);

    Matrix4f * scaleCube=new Matrix4f();
    scaleCube->scale(0.5,1,0.5);

    Material * material=new Material(vec3f(1.0f, 0.2f, 0.2f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/wood.png");

    NodeSceneGraph * cubeNode=new NodeSceneGraph();
    cubeNode->add(moveAvatar);
    cubeNode->add(scaleCube);
    cubeNode->add(material);
    cubeNode->add(cubeObject);
    root->add(cubeNode);

    currentTime=SDL_GetTicks();
    jumpDelay=currentTime;
}

//**********************************************************************//

Enemy::~Enemy()
{
    //dtor
}

//**********************************************************************//

void Enemy::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void Enemy::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap){
    bool hasMove=true;
    avatarDirection heroDir;
    pair<avatarDirection,vec3f> moveHero;
    currentMap=rootMap;

    if(time-currentTime>200)
        currentTime=time-50;

    if(enemyActivate){ //If enemy is activated
        moveHero=IA.nextPosition(vec3f(position.x,position.y,position.z),rootMap->getHero()->getPosition());
        if(!moveBody(moveHero.second,moveHero.first)){
            activeJump(vec3f(0.0,15.0,0.0),vec3f(0.0,5.0,0.0));
        }
        if(isJumping){
            jump(time);
        }
        else
            gravity(time);
    }

    //Update our vec4f position
    position=moveAvatar->product(vec4f());
    currentTime+=(time-currentTime);
}

//**********************************************************************//

void Enemy::activatedEnemy(bool value){
    enemyActivate=value;
}

//**********************************************************************//

bool Enemy::isActivate(){
    return enemyActivate;
}

//**********************************************************************//

vec3f Enemy::getRadioActivity(){
    return radioActivity;
}
