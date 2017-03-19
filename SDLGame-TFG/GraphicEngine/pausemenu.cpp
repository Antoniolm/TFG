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

#include "pausemenu.h"

PauseMenu::PauseMenu()
{
    currentOption=0;
    activateMenu=false;
    MeshCollection * meshCollect =MeshCollection::getInstance();
    SoundCollection * soundCollect =SoundCollection::getInstance();

    currentMaterial=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/menuPauseResume.png");
    Material * materialBack=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/menuBack.png");

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
    moveSound=soundCollect->getSound(sCoin);

    //Add the options
    addOption(new Texture("./textures/menuPauseResume.png"));
    addOption(new Texture("./textures/menuPauseQuit.png"));
}

//**********************************************************************//

PauseMenu::~PauseMenu()
{
    delete root;

     for(vector<Texture *>::iterator it = options.begin() ; it != options.end(); ++it){
        delete (*it);
    }

    delete currentMaterial;
}

//**********************************************************************//

void PauseMenu::visualization(Context & cv){
    if(activateMenu)
        root->visualization(cv);
}

//**********************************************************************//

void PauseMenu::updateState(GameState & gameState){
    vec3f position;

    if(!gameState.movie->isActivated() && !gameState.deadMenu->isActivate() && !gameState.camera->isViewMode()){
        float time=gameState.time;
        ControllerManager * controller=gameState.controller;

        if(time-currentTime>200)
            currentTime=time-50;

        if(controller->checkButton(cPAUSE) && menuDelay<(time-600)){
            activateMenu=!activateMenu;
            menuDelay=time;
            if(activateMenu){
                (Profile::getInstance())->showResult();
                position=gameState.rootMap->getHero()->getPosition();
                positionMenu->translation(position.x,position.y+6.75,position.z+11.0);

                //Consume the current events -> User has to push again the buttons
                controller->setState(false,cUP);
                controller->setState(false,cDOWN);
                controller->setState(false,cACTION);
            }
            else {
                currentOption=0;
                currentMaterial->setTexture(options[currentOption]);
            }
            openSound->play();
        }


        if(activateMenu){ //If the menu is activated
            if(controller->checkButton(cUP) && menuDelay<(time-300)){ //If the user push the action move on the menu
                currentOption-=1;
                if(currentOption==-1)
                    currentOption=(options.size()-1);

                currentMaterial->setTexture(options[currentOption]);
                menuDelay=time;
                moveSound->play();
            }
            else if(controller->checkButton(cDOWN) && menuDelay<(time-300)){ //If the user push the action move on the menu
                currentOption++;
                if((unsigned)currentOption==options.size())
                    currentOption=0;

                currentMaterial->setTexture(options[currentOption]);
                menuDelay=time;
                moveSound->play();
            }
            if(controller->checkButton(cACTION) && menuDelay<(time-300)){ //If the user push the action intro
                switch(currentOption){
                    case 0: //Resume
                        currentOption=0;
                         currentMaterial->setTexture(options[currentOption]);
                        activateMenu=false;
                        openSound->play();
                    break;
                    case 1: //Exit
                        currentOption=0;
                        currentMaterial->setTexture(options[currentOption]);
                        (Profile::getInstance())->showResult();
                        MainMenu::getInstance()->activate();
                        activateMenu=false;
                    break;

                }

                menuDelay=time;
                controller->setState(false,cACTION);
            }
        }

        currentTime+=time-currentTime;
    }
}
