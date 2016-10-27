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

#include "oscillaterotation.h"

OscillateRotation::OscillateRotation()
{
    //ctor
}

//**********************************************************************//

OscillateRotation::~OscillateRotation()
{
    //dtor
}

//**********************************************************************//

OscillateRotation::OscillateRotation(bool incre,float maxG,float minG,float initG,float velocity,vec3f dir){
    increment=incre;
    maxGrade=maxG;
    minGrade=minG;
    initialGrade=initG;
    angularVelocity=velocity;
    direction=dir;

    currentGrade=initialGrade;
    currentTime=0;
}

//**********************************************************************//
Matrix4f & OscillateRotation::updateState(float time){
    time=time/1000;


    float grade;

    if(currentGrade>= maxGrade){
        increment=false;
    }
    if(currentGrade<=minGrade){
        increment=true;
    }

    if(!increment){
        currentGrade-=angularVelocity*(time-currentTime);
    }
    else{
        currentGrade+=angularVelocity*(time-currentTime);
    }

    currentMatrix.rotation(currentGrade,direction.x,direction.y,direction.z);
    currentTime=time;
    return currentMatrix;


}

