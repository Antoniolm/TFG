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

#include "gamepadcontroller.h"

GamepadController::GamepadController()
{
    for(int i=0;i<10;i++)
        buttons[i]=false;
}

//**********************************************************************//

GamepadController::~GamepadController()
{
    //dtor
}

//**********************************************************************//

void GamepadController::setButton(bool value,Uint8 button){
    switch(button){
    case SDL_CONTROLLER_BUTTON_A:
        buttons[cACTION]=value;
        break;
    case SDL_CONTROLLER_BUTTON_B:
        buttons[cJUMP]=value;
        break;
    case SDL_CONTROLLER_BUTTON_Y:
        buttons[cSWAPWEAPON]=value;
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_UP:
        buttons[cUP]=value;
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
        buttons[cDOWN]=value;
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
        buttons[cLEFT]=value;
        break;
    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
        buttons[cRIGHT]=value;
        break;
    case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
        buttons[cSHIELD]=value;
        break;
    case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
        buttons[cATTACK]=value;
        break;
    case SDL_CONTROLLER_BUTTON_START:
        buttons[cPAUSE]=value;
        break;
    }
}

