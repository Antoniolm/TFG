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

#include "menu.h"

Menu::Menu()
{
    currentOption=0;
    activateMenu=false;
    Mesh * textObject=new Mesh(string("geometries/text.obj"));
    textObject->init();

    currentMaterial=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/menuPauseResume.png");
    Material * materialBack=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/menuBack.png");

    positionMenu=new Matrix4f();
    positionMenu->identity();
    Matrix4f * scaleMenu=new Matrix4f();
    scaleMenu->scale(0.4,1.0,0.4);
    Matrix4f * scaleMenuBack=new Matrix4f();
    scaleMenuBack->scale(4.0,4.0,4.0);

    Matrix4f * rotationMenu=new Matrix4f();
    rotationMenu->rotation(20,1.0,0.0,0.0);

    root=new NodeSceneGraph();
    root->add(positionMenu);
    root->add(rotationMenu);
    root->add(scaleMenu);
    root->add(currentMaterial);
    root->add(textObject);
    root->add(scaleMenuBack);
    root->add(materialBack);
    root->add(textObject);
    currentTime=SDL_GetTicks();
    menuDelay=currentTime;
}

//**********************************************************************//

Menu::~Menu()
{
    //dtor
}

//**********************************************************************//

void Menu::addOption(Texture * aTexture){
    options.push_back(aTexture);
}

//**********************************************************************//

void Menu::visualization(Context & cv){
    if(activateMenu)
        root->visualization(cv);
}

//**********************************************************************//

void Menu::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap){
    vec3f position;

    if(time-currentTime>200)
        currentTime=time-50;

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_ESCAPE)] && menuDelay<(time-600)){
        activateMenu=!activateMenu;
        menuDelay=time;
        if(activateMenu){
            position=rootMap->getHero()->getPosition();
            positionMenu->translation(position.x,position.y+3.25,position.z+8.0);
        }
    }
    if(activateMenu){ //If the menu is activated
        if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)] && menuDelay<(time-300)){ //If the user push the action move on the menu
            currentOption++;
            if(currentOption==options.size())
                currentOption=0;

            currentMaterial->setTexture(options[currentOption]);
            menuDelay=time;
        }
        else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)] && menuDelay<(time-300)){ //If the user push the action move on the menu
            currentOption-=1;
            if(currentOption==-1){
                currentOption=(options.size()-1);
            }

            currentMaterial->setTexture(options[currentOption]);
            menuDelay=time;
        }
        if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_p)] && menuDelay<(time-300)){ //If the user push the action intro
            if(currentOption==0){ //If option -> Resume
                activateMenu=false;
            }
            if(currentOption==1)//If option -> Quit
                exit(0);

            menuDelay=time;
        }
    }

    currentTime+=time-currentTime;
}

//**********************************************************************//

bool Menu::isActivate(){
    return activateMenu;
}
