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
    //ctor
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
            currentOption++;
            if(currentOption==options.size())
                currentOption=0;

            currentMaterial->setTexture(options[currentOption]);
            menuDelay=time;
            //moveSound->play();
        }
        else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)] && menuDelay<(time-300)){ //If the user push the action move on the menu
            currentOption-=1;
            if(currentOption==-1){
                currentOption=(options.size()-1);
            }

            currentMaterial->setTexture(options[currentOption]);
            menuDelay=time;
            //moveSound->play();
        }
        if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_p)] && menuDelay<(time-300)){ //If the user push the action intro
            if(currentOption==0){ //If option -> Resume
                activateMenu=false;
                openSound->play();
            }
            if(currentOption==1)//If option -> Quit
                exit(0);

            menuDelay=time;
        }
    }

    currentTime+=time-currentTime;
}

//**********************************************************************//

void MainMenu::activate(){
    activateMenu=true;
}


