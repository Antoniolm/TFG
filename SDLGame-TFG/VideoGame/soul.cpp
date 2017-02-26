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

#include "soul.h"

Soul::Soul(const Value & soulFeatures)
{
    position=vec4f(soulFeatures["position"][0].GetFloat(),soulFeatures["position"][1].GetFloat(),soulFeatures["position"][2].GetFloat(),1.0);
    activated=false;

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    transMatrix=new Matrix4f();
    transMatrix->translation(position.x,position.y,position.z);

    root=new NodeSceneGraph();
    root->add(transMatrix);
    root->add(materialCollect->getMaterial(mCRYSTAL));
    root->add(meshCollect->getMesh(COIN));
    currentTime=SDL_GetTicks();

}

//**********************************************************************//

Soul::~Soul()
{
    delete root;
}

//**********************************************************************//

void Soul::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void Soul::updateState(GameState & gameState ){
    float time=gameState.time;
    Hero * hero=gameState.rootMap->getHero();

    if(time-currentTime>200) currentTime=time-50;

    vec3f posHero=hero->getPosition();
    float distance=sqrt(pow(position.x-posHero.x,2.0)+pow(position.z-posHero.z,2.0));

    if(activated && gameState.controller->checkButton(cACTION)){ //If is activated and hero push E -> Drop the soul in the scene.
        activated=false;
        hero->setSoul(0);

        transMatrix->translation(posHero.x,posHero.y,posHero.z);
        gameState.controller->consumeButtons();
    }

    //if hero is near of a soul and he push E -> Hero catch the soul in his arms
    if(!activated && hero->getSoul()==0 && gameState.controller->checkButton(cACTION) && distance<=0.75 &&
       (position.y>posHero.y-1 && position.y<posHero.y+1)){
        activated=true;
        gameState.controller->consumeButtons();
        hero->setSoul(this);
    }

    if(activated){ //if hero caught a soul in his arms
        calculatePosition(posHero,hero->getDirection());
    }

    position=transMatrix->product(vec4f());
    currentTime+=time-currentTime;
}

//**********************************************************************//
//                              PRIVATE                                 //
//**********************************************************************//

void Soul::calculatePosition(vec3f posHero,avatarDirection direction){
    switch(direction){
            case FORWARD:
                transMatrix->translation(posHero.x,posHero.y,posHero.z+0.5);
            break;
            case BACKWARD:
                transMatrix->translation(posHero.x,posHero.y,posHero.z-0.5);
            break;
            case LEFTWARD:
                transMatrix->translation(posHero.x-0.5,posHero.y,posHero.z);
            break;
            case RIGHTWARD:
                transMatrix->translation(posHero.x+0.5,posHero.y,posHero.z);
            break;
            case FOR_LEFTWARD:
                transMatrix->translation(posHero.x-0.4,posHero.y,posHero.z+0.4);
            break;
            case FOR_RIGHTWARD:
                transMatrix->translation(posHero.x+0.4,posHero.y,posHero.z+0.4);
            break;
            case BACK_LEFTWARD:
                transMatrix->translation(posHero.x-0.4,posHero.y,posHero.z-0.4);
            break;
            case BACK_RIGHTWARD:
                transMatrix->translation(posHero.x+0.4,posHero.y,posHero.z-0.4);
            break;
    }
}