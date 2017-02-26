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

Door::Door()
{
    //ctor
}

//**********************************************************************//

Door::~Door()
{
    //dtor
}

//**********************************************************************//

void Door::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void Door::updateState(GameState & gameState ){
    float time=gameState.time;
    Hero * hero=gameState.rootMap->getHero();
    Soul * soul=hero->getSoul();

    if(time-currentTime>200) currentTime=time-50;

    vec3f posHero=hero->getPosition();
    float distance=sqrt(pow(position.x-posHero.x,2.0)+pow(position.z-posHero.z,2.0));

    //if hero is near of a soulCarrier and he push E -> SoulCarrier catch the soul in his arms
    if(soul!=0 && !activated && gameState.controller->checkButton(cACTION) && distance<=1.5 && (position.y>posHero.y-1 && position.y<posHero.y+1)){
        activated=true;
        soul->setPosition(vec3f(position.x,position.y+1.0,position.z));
        soul->setInCarrier(true);
        hero->setSoul(0);
        //gameState.controller->consumeButtons();
    }

    if(activated){ //if hero caught a soul in his arms

    }

    currentTime+=time-currentTime;
}

