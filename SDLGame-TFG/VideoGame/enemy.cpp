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

Enemy::Enemy(vec3f aPosition)
{
    position=vec4f(aPosition.x,aPosition.y,aPosition.z,1.0);
    acceleratedMove=new AcceleratedMovement();
    acceleratedMove->resetState();
    direction=FORWARD;
    isMoving=false;
    isFalling=false;
    isJumping=false;

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
    vec3f moveHero;
    currentMap=rootMap;

    if(time-currentTime>200)
        currentTime=time-50;

    //Case-> Push Left bottom
    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)] && !currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)] &&
    !currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)]){
        moveHero.x=-3.0;moveHero.z=0.0;
        heroDir=LEFTWARD;
    }
    //Case-> Push Right bottom
    else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)]&& !currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)] &&
    !currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)]){
        moveHero.x=3.0;moveHero.z=0.0;
        heroDir=RIGHTWARD;
    }
    //Case-> Push Up bottom
    else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)]&& !currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)] &&
    !currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)]){
        moveHero.x=0.0;moveHero.z=-3.0;
        heroDir=BACKWARD;
    }
    //Case-> Push Down bottom
    else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)]&& !currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)] &&
    !currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)]){
        moveHero.x=0.0;moveHero.z=3.0;
        heroDir=FORWARD;
    }
    //Case-> Push Dowm-Left bottoms
    else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)] && currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)] ){
        moveHero.x=-2.0;moveHero.z=2.0;
        heroDir=FOR_LEFTWARD;
    }
    //Case-> Push Dowm-Right bottoms
    else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)] && currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)] ){
        moveHero.x=2.0;moveHero.z=2.0;
        heroDir=FOR_RIGHTWARD;
    }
    //Case-> Push Up-Left bottoms
    else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)] && currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)]){
        moveHero.x=-2.0;moveHero.z=-2.0;
        heroDir=BACK_LEFTWARD;
    }
    //Case-> Push Up-Right bottoms
    else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)] && currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)] ){
        moveHero.x=2.0;moveHero.z=-2.0;
        heroDir=BACK_RIGHTWARD;
    }
    else{ //Case-> If not move
        hasMove=false;
    }

    //Case-> Push Scape bottom to jump
    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_s)] && !isJumping && !isFalling && jumpDelay<(time-600)){
        activeJump(15.0,5.0);
        jumpDelay=time;
    }
    //Move the body
    if(hasMove){
        moveBody(moveHero,heroDir);
    }
    //If the jump is activate
    if(isJumping){
        jump(time);
    }

    //If the jump is not activate
    else gravity(time);

    //Update our vec4f position
    position=moveAvatar->product(vec4f());

    currentTime+=(time-currentTime);
}
