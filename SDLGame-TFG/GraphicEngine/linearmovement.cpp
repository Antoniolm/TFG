// *********************************************************************
// **
// ** Copyright (C) 2016 Antonio David L�pez Machado
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
#include "linearmovement.h"

LinearMovement::LinearMovement()
{
    //dtor
}

//**********************************************************************//

LinearMovement::LinearMovement(float x,float y,float z){
    velocity.x=x;
    velocity.y=y;
    velocity.z=z;
}

//**********************************************************************//

LinearMovement::LinearMovement(vec3f aVelocity)
{
    velocity=aVelocity;
}

//**********************************************************************//

LinearMovement::~LinearMovement()
{
    //dtor
}

//**********************************************************************//

Matrix4f & LinearMovement::updateState(float time){
    time=time/1000;

    cout<< "Time --> "<< time;
    velocity.x*=time;
    velocity.y*=time;
    velocity.z*=time;

    currentMatrix.translation(velocity.x,velocity.y,velocity.z);

    return currentMatrix;
}
