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

#include "ianpc.h"

IANpc::IANpc()
{
    //ctor
}

//**********************************************************************//

IANpc::~IANpc()
{
    //dtor
}

//**********************************************************************//

void IANpc::addState(const string & state){
    states.push_back(state);
}

//**********************************************************************//

string & IANpc::getCurrentState(){
    return states[currentState];
}

//**********************************************************************//

int IANpc::getNumState(){
    return states.size();
}

//**********************************************************************//

void IANpc::clean(){
    states.clear();
}

//**********************************************************************//

void IANpc::firstState(){
    currentState=0;

}

//**********************************************************************//

void IANpc::nextState(){
    currentState++;
}

//**********************************************************************//

void IANpc::beforeState(){
    currentState--;

}

//**********************************************************************//

bool IANpc::isLastState(){
    bool result=false;

    if(currentState==states.size()-1)
        result=true;

    return result;
}
