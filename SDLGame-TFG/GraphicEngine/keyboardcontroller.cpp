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

#include "keyboardcontroller.h"

KeyboardController::KeyboardController()
{
    //ctor
}

//**********************************************************************//

KeyboardController::~KeyboardController()
{
    //dtor
}

//**********************************************************************//

bool KeyboardController::checkButton(ControllerIndex button){
    bool result;

    switch(button){
        case UP:
            result=buttonUp;
        break;
        case DOWN:
            result=buttonDown;
        break;
        case RIGHT:
            result=buttonRight;
        break;
        case LEFT:
            result=buttonLeft;
        break;
        case ACTION:
            result=buttonAct;
        break;
        case JUMP:
            result=buttonJmp;
        break;
        case ATTACK:
            result=buttonAtt;
        break;
        case SHIELD:
            result=buttonShield;
        break;
        case SWAPWEAPON:
            result=buttonSwap;
        break;

    }


    return result;
}

//**********************************************************************//

void KeyboardController::catchKeyBoardState(const Uint8* currentKeyStates){

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_w)]) buttonUp=true;
    else buttonUp=false;

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_s)]) buttonDown=true;
    else buttonDown=false;

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_a)]) buttonLeft=true;
    else buttonLeft=false;

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_d)]) buttonRight=true;
    else buttonRight=false;

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_e)]) buttonAct=true;
    else buttonAct=false;

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_i)]) buttonShield=true;
    else buttonShield=false;

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_k)]) buttonJmp=true;
    else buttonJmp=false;

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_l)]) buttonAtt=true;
    else buttonAtt=false;

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_q)]) buttonSwap=true;
    else buttonSwap=false;
}
