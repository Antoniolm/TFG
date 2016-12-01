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

AcceleratedMovement::AcceleratedMovement(float xVelo,float yVelo,float zVelo,float xAccel,float yAccel,float zAccel,bool incre){
    velocity=vec3f(xVelo,yVelo,zVelo);
    acceleration=vec3f(xAccel,yAccel,zAccel);
    currentTime=SDL_GetTicks()/1000;
    increment=incre;
    currentMatrix.identity();
}

//**********************************************************************//

AcceleratedMovement::AcceleratedMovement(const vec3f & aVelocity,const vec3f & aAcceleration,bool incre){
    velocity=aVelocity;
    acceleration=aAcceleration;
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

void AcceleratedMovement::setParameters(float xVelo,float yVelo,float zVelo,float xAccel,float yAccel,float zAccel,bool incre){
    velocity=vec3f(xVelo,yVelo,zVelo);
    acceleration=vec3f(xAccel,yAccel,zAccel);
    increment=incre;
    currentTime=SDL_GetTicks()/1000;
    currentMatrix.identity();
}

//**********************************************************************//

void AcceleratedMovement::setParameters(const vec3f & aVelocity,const vec3f & aAcceleration,bool incre){
    velocity=aVelocity;
    acceleration=aAcceleration;
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
        velocity=velocity+(acceleration*time*10);
    }
    else
        velocity=velocity-(acceleration*time*10);

    //Update our matrix with that new velocity
    currentMatrix.translation(velocity.x*time,velocity.y*time,velocity.z*time);

    currentTime+=time;
    return currentMatrix;
}

//**********************************************************************//

void AcceleratedMovement::resetState(){

}

