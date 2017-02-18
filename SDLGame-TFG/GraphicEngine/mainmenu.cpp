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

#include "mainmenu.h"

MainMenu* MainMenu::instance = NULL;

MainMenu::MainMenu()
{
    currentOption=0;
    activateMenu=true;
    MeshCollection * meshCollect =MeshCollection::getInstance();

    currentMaterial=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/mainMenuStart.png");
    Material * materialBack=new Material(vec3f(0.2f, 0.2f, 0.2f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/menuBack.png");

    positionMenu=new Matrix4f();
    positionMenu->translation(0.0,6.75,11.0);

    Matrix4f * betweenMenu=new Matrix4f();
    betweenMenu->translation(0.0,0.0,-0.1);

    Matrix4f * scaleMenu=new Matrix4f();
    scaleMenu->scale(0.4,1.8,0.5);
    Matrix4f * scaleMenuBack=new Matrix4f();
    scaleMenuBack->scale(2.5,2.5,2.5);

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

    openSound=new Sound("sounds/openSound.wav",0,120,1,1);
    moveSound=new Sound("sounds/coin.wav",1,40,4,0);

    //Add the options
    addOption(new Texture("./textures/mainMenuStart.png"));
    addOption(new Texture("./textures/mainMenuCont.png"));
    addOption(new Texture("./textures/mainMenuControl.png"));
    addOption(new Texture("./textures/mainMenuQuit.png"));
}

//**********************************************************************//

MainMenu::~MainMenu()
{
    delete openSound;
    delete moveSound;
    delete root;

    for(unsigned i=0;i<options.size();i++)
        delete options[i];

    delete currentMaterial;


}

//**********************************************************************//

void MainMenu::visualization(Context & cv){
    if(activateMenu)
        root->visualization(cv);
}

//**********************************************************************//

void MainMenu::updateState(GameState & gameState){
    vec3f position;

    float time=gameState.time;
    ControllerManager * controller=gameState.controller;

    if(time-currentTime>200)
        currentTime=time-50;

    if(activateMenu){ //If the menu is activated
        if(controller->checkButton(cUP) && menuDelay<(time-300)){ //If the user push the action move on the menu
            currentOption-=1;
            if(currentOption==-1)
                currentOption=(options.size()-1);

            currentMaterial->setTexture(options[currentOption]);
            menuDelay=time;
            moveSound->stop();
            moveSound->play();
        }
        else if(controller->checkButton(cDOWN) && menuDelay<(time-300)){ //If the user push the action move on the menu
            currentOption++;
            if((unsigned)currentOption==options.size())
                currentOption=0;

            currentMaterial->setTexture(options[currentOption]);
            menuDelay=time;
            moveSound->stop();
            moveSound->play();
        }
        if(controller->checkButton(cACTION) && menuDelay<(time-300)){ //If the user push the action intro
            switch(currentOption){
                case 0:
                    activateMenu=false;
                    openSound->play();
                    RootMap::loading=true;
                    //delete gameState.rootMap;
                    gameState.rootMap=new RootMap("./maps/map.json",true);
                break;
                case 1:
                    //activateMenu=false;
                    openSound->play();
                break;
                case 2:
                    //activateMenu=false;
                    openSound->play();
                break;
                case 3:
                    (Profile::getInstance())->showResult();
                    exit(0);
                break;

            }

            menuDelay=time;
            controller->setState(false,cACTION);
        }
    }

    currentTime+=time-currentTime;
}

//**********************************************************************//

void MainMenu::setPosition(vec3f aPosition){
    positionMenu->translation(aPosition.x,aPosition.y+6.75,aPosition.z+11.0);
}


//**********************************************************************//

void MainMenu::activate(){
    activateMenu=true;
}


