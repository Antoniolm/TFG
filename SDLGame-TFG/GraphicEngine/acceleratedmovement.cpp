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

#include "acceleratedmovement.h"

AcceleratedMovement::AcceleratedMovement()
{
    //ctor
}

//**********************************************************************//

AcceleratedMovement::AcceleratedMovement(float x,float y,float z,float aAccel,bool incre){
    velocity.x=x;
    velocity.y=y;
    velocity.z=z;
    acceleration=aAccel;
    currentTime=SDL_GetTicks()/1000;
    increment=incre;
    currentMatrix.identity();
}

//**********************************************************************//

AcceleratedMovement::AcceleratedMovement(const vec3f & aVelocity,float aAccel,bool incre)
{
    velocity=aVelocity;
    acceleration=aAccel;
    currentTime=SDL_GetTicks()/1000;
    increment=incre;
    currentMatrix.identity();;
}

//**********************************************************************//

AcceleratedMovement::~AcceleratedMovement()
{
    //dtor
}

//**********************************************************************//

void AcceleratedMovement::setParameters(float x,float y,float z,float aAccel,bool incre){
    velocity.x=x;
    velocity.y=y;
    velocity.z=z;
    acceleration=aAccel;
    increment=incre;
    currentTime=SDL_GetTicks()/1000;
    currentMatrix.identity();
}

//**********************************************************************//

void AcceleratedMovement::setParameters(const vec3f & aVelocity,float aAccel,bool incre){
    velocity=aVelocity;
    acceleration=aAccel;
    increment=incre;
    currentTime=SDL_GetTicks()/1000;
    currentMatrix.identity();
}

//**********************************************************************//

Matrix4f & AcceleratedMovement::updateState(float time){
    time=time/1000.0;

    float value;
    //Check the velocity
    if(increment){
        value=+(acceleration*time*10);
    }
    else
        value=-(acceleration*time*10);

    if(velocity.x>0)
        velocity.x=velocity.x+value;
    if(velocity.y>0)
        velocity.y=velocity.y+value;
    if(velocity.z>0)
        velocity.z=velocity.z+value;

    //Update our matrix with that new velocity
    currentMatrix.translation(velocity.x*time,velocity.y*time,velocity.z*time);

    currentTime+=time;
    return currentMatrix;
}

//**********************************************************************//

void AcceleratedMovement::resetState(){

}
