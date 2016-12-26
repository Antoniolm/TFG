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

MainMenu::MainMenu()
{
    currentOption=0;
    activateMenu=false;
    MeshCollection * meshCollect =MeshCollection::getInstance();

    currentMaterial=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/mainMenuStart.png");
    Material * materialBack=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/menuBack.png");

    positionMenu=new Matrix4f();
    positionMenu->translation(0.0,3.25,8.0);
    Matrix4f * scaleMenu=new Matrix4f();
    scaleMenu->scale(0.4,1.3,0.4);
    Matrix4f * scaleMenuBack=new Matrix4f();
    scaleMenuBack->scale(4.0,4.0,4.0);

    Matrix4f * rotationMenu=new Matrix4f();
    rotationMenu->rotation(20,1.0,0.0,0.0);

    root=new NodeSceneGraph();
    root->add(positionMenu);
    root->add(rotationMenu);
    root->add(scaleMenu);
    root->add(currentMaterial);
    root->add(meshCollect->getMesh(TEXT));
    root->add(scaleMenuBack);
    root->add(materialBack);
    root->add(meshCollect->getMesh(TEXT));
    currentTime=SDL_GetTicks();
    menuDelay=currentTime;

    openSound=new Sound("sounds/openSound.wav",0,120,1,1);
    moveSound=new Sound("sounds/coin.wav",1,40,4,0);

    //Add the options
    Texture * option=new Texture("./textures/mainMenuStart.png");
    addOption(option);
    option=new Texture("./textures/mainMenuCont.png");
    addOption(option);
    option=new Texture("./textures/mainMenuControl.png");
    addOption(option);
    option=new Texture("./textures/mainMenuQuit.png");
    addOption(option);
}

//**********************************************************************//

MainMenu::~MainMenu()
{
    //dtor
}

//**********************************************************************//

void MainMenu::visualization(Context & cv){
    if(activateMenu)
        root->visualization(cv);
}

//**********************************************************************//

void MainMenu::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap){
    vec3f position;

    if(time-currentTime>200)
        currentTime=time-50;

    if(activateMenu){ //If the menu is activated
        if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)] && menuDelay<(time-300)){ //If the user push the action move on the menu
            currentOption-=1;
            if(currentOption==-1)
                currentOption=(options.size()-1);

            currentMaterial->setTexture(options[currentOption]);
            menuDelay=time;
            moveSound->stop();
            moveSound->play();
        }
        else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)] && menuDelay<(time-300)){ //If the user push the action move on the menu
            currentOption++;
            if(currentOption==options.size())
                currentOption=0;


            currentMaterial->setTexture(options[currentOption]);
            menuDelay=time;
            moveSound->stop();
            moveSound->play();
        }
        if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_p)] && menuDelay<(time-300)){ //If the user push the action intro
            switch(currentOption){
                case 0:
                    activateMenu=false;
                    openSound->play();
                break;
                case 1:
                    activateMenu=false;
                    openSound->play();
                break;
                case 2:
                    activateMenu=false;
                    openSound->play();
                break;
                case 3:
                    exit(0);
                break;

            }

            menuDelay=time;
        }
    }

    currentTime+=time-currentTime;
}

//**********************************************************************//

void MainMenu::activate(){
    activateMenu=true;
}


