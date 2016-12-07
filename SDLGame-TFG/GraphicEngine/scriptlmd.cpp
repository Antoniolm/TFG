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

#include "scriptlmd.h"

ScriptLMD::ScriptLMD()
{
    //ctor
}

//**********************************************************************//

ScriptLMD::~ScriptLMD()
{
    for(int i=0;i<script.size();i++)
        delete script[i];
}

//**********************************************************************//

 void ScriptLMD::add(Matrix4fDynamic * aMatrix){
    script.push_back(aMatrix);
 }

//**********************************************************************//

void ScriptLMD::updateState(float time){
    vector<Matrix4fDynamic*>::iterator it;

    for(it=script.begin();it!=script.end();it++){
            (*it)->updateState(time);
    }
}

//**********************************************************************//

Matrix4f ScriptLMD::readMatrix(int index){
    return script[index]->getMatrix();
}

//**********************************************************************//

void ScriptLMD::resetState(){
    vector<Matrix4fDynamic*>::iterator it;

    for(it=script.begin();it!=script.end();it++){
            (*it)->resetState();
    }
}
