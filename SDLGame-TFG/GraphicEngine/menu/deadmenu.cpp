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

#include "deadmenu.h"

DeadMenu::DeadMenu(vec3f initialPos,string fileName)
{
    currentOption=0;
    activateMenu=false;
    initialPosition=initialPos;
    MeshCollection * meshCollect =MeshCollection::getInstance();
    SoundCollection * soundCollect =SoundCollection::getInstance();

    currentMaterial=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"");
    Material * materialBack=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,fileName.c_str());

    positionMenu=new Matrix4f();
    positionMenu->identity();

    Matrix4f * betweenMenu=new Matrix4f();
    betweenMenu->translation(0.0,0.0,-0.1);

    Matrix4f * scaleMenu=new Matrix4f();
    scaleMenu->scale(0.4,1.5,0.4);
    Matrix4f * scaleMenuBack=new Matrix4f();
    scaleMenuBack->scale(4.0,4.0,4.0);

    Matrix4f * rotationMenu=new Matrix4f();
    rotationMenu->rotation(20,1.0,0.0,0.0);

    root=new NodeSceneGraph(false,true);
    root->add(positionMenu);
    root->add(rotationMenu);
    root->add(scaleMenu);
    root->add(currentMaterial);
    root->add(meshCollect->getMesh(TEXT));
    root->add(betweenMenu);
    root->add(scaleMenuBack);
    root->add(materialBack);
    root->add(meshCollect->getMesh(TEXT));
    currentTime=SDL_GetTicks();
    menuDelay=currentTime;

    openSound=soundCollect->getSound(sOpen);
}

//**********************************************************************//

DeadMenu::~DeadMenu()
{
    delete root;

    delete currentMaterial;
}

//**********************************************************************//

void DeadMenu::visualization(Context & cv){
    if(activateMenu){
        root->visualization(cv);
    }
}

//**********************************************************************//

void DeadMenu::updateState(GameState & gameState){
    vec3f position;
    float time=gameState.time;

    if(time-currentTime>200)
        currentTime=time-50;

    if(activateMenu){ //If the menu is activated
        position=gameState.rootMap->getHero()->getPosition();
        positionMenu->translation(position.x+initialPosition.x,position.y+initialPosition.y,position.z+initialPosition.z);

        if(gameState.controller->checkButton(cACTION) && menuDelay<(time-300)){ //If the user push the action intro
            menuDelay=time;
            (Profile::getInstance())->showResult();
            gameState.mainMenu->activate();
            activateMenu=false;
            gameState.controller->consumeButtons();
        }
    }

    currentTime+=time-currentTime;
}

//**********************************************************************//

void DeadMenu::activate(){
    activateMenu=true;
}

//**********************************************************************//

void DeadMenu::add(string fileName){
    currentMaterial->setTexture(fileName.c_str());
}
