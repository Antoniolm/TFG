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

#include "matrixscriptloop.h"

MatrixScriptLoop::MatrixScriptLoop()
{
    currentMove=0;
    currentLoop=0;
}

//**********************************************************************//

MatrixScriptLoop::~MatrixScriptLoop()
{
    //dtor
}

//**********************************************************************//

void MatrixScriptLoop::add(int loop, Matrix4fDynamic * matrix){
    pair<int,Matrix4fDynamic*> newElement;
    newElement.first=loop;
    newElement.second=matrix;

    script.push_back(newElement);
}

//**********************************************************************//

Matrix4f & MatrixScriptLoop::updateState(float time){
    /*float auxTime=time/1000;

    currentTime+=auxTime;

    if(currentTime>script[currentMove].first){
        currentLoop=0;
        currentMove++;
        if(currentMove==script.size()){ //initial Case
            currentMove=0;
        }
        (script[currentMove].second)->resetState(); //Reset the state
    }
    currentMatrix=(script[currentMove].second)->updateState(time);
    return currentMatrix;*/
}

//**********************************************************************//

void MatrixScriptLoop::resetState(){
    currentMove=0;
    for(unsigned i=0;i<script.size();i++)
        (script[i].second)->resetState();
}
