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

void KeyboardController::catchKeyBoardState(const Uint8* currentKeyStates){

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_w)]) buttons[cUP]=true;
    else buttons[cUP]=false;

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_s)]) buttons[cDOWN]=true;
    else buttons[cDOWN]=false;

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_a)]) buttons[cLEFT]=true;
    else buttons[cLEFT]=false;

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_d)]) buttons[cRIGHT]=true;
    else buttons[cRIGHT]=false;

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_e)]) buttons[cACTION]=true;
    else buttons[cACTION]=false;

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_i)]) buttons[cSHIELD]=true;
    else buttons[cSHIELD]=false;

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_k)]) buttons[cJUMP]=true;
    else buttons[cJUMP]=false;

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_l)]) buttons[cATTACK]=true;
    else buttons[cATTACK]=false;

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_q)]) buttons[cSWAPWEAPON]=true;
    else buttons[cSWAPWEAPON]=false;

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_ESCAPE)]) buttons[cPAUSE]=true;
    else buttons[cPAUSE]=false;
}
