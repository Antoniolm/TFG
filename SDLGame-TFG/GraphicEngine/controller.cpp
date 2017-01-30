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
            result=buttonUp;
        break;
        case cDOWN:
            result=buttonDown;
        break;
        case cRIGHT:
            result=buttonRight;
        break;
        case cLEFT:
            result=buttonLeft;
        break;
        case cACTION:
            result=buttonAct;
        break;
        case cJUMP:
            result=buttonJmp;
        break;
        case cATTACK:
            result=buttonAtt;
        break;
        case cSHIELD:
            result=buttonShield;
        break;
        case cSWAPWEAPON:
            result=buttonSwap;
        break;
        case cPAUSE:
            result=buttonPause;
        break;

    }


    return result;}

//**********************************************************************//

void Controller::catchKeyBoardState(const Uint8* currentKeyStates){}
