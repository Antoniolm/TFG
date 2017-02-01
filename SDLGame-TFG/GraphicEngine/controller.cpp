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

#include "controller.h"

Controller::Controller()
{
    //ctor
}

//**********************************************************************//

Controller::~Controller()
{
    //dtor
}

//**********************************************************************//

void Controller::setButton(bool value,Uint8 button){}

//**********************************************************************//

bool Controller::checkButton(ControllerIndex button){
    bool result=false;

    switch(button){
        case cUP:
            result=buttons[cUP];
        break;
        case cDOWN:
            result=buttons[cDOWN];
        break;
        case cRIGHT:
            result=buttons[cRIGHT];
        break;
        case cLEFT:
            result=buttons[cLEFT];
        break;
        case cACTION:
            result=buttons[cACTION];
        break;
        case cJUMP:
            result=buttons[cJUMP];
        break;
        case cATTACK:
            result=buttons[cATTACK];
        break;
        case cSHIELD:
            result=buttons[cSHIELD];
        break;
        case cSWAPWEAPON:
            result=buttons[cSWAPWEAPON];
        break;
        case cPAUSE:
            result=buttons[cPAUSE];
        break;

    }


    return result;}

//**********************************************************************//

void Controller::catchKeyBoardState(const Uint8* currentKeyStates){}
