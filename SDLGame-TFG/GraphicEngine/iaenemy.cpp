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

#include "iaenemy.h"

IAEnemy::IAEnemy()
{
    //ctor
}

//**********************************************************************//

IAEnemy::~IAEnemy()
{
    //dtor
}

//**********************************************************************//

pair<avatarDirection,vec3f> IAEnemy::nextPosition(vec3f posEnemy,vec3f posHero){
    vec3f newMovement;
    float distancia,minDistancia;
    avatarDirection enemyDir;
    pair<avatarDirection,vec3f> result;

    newMovement.x=posEnemy.x-3.0;newMovement.y=posEnemy.y;newMovement.z=posEnemy.z;
    enemyDir=LEFTWARD;
    result.first=enemyDir;
    result.second=vec3f(-3.0,0.0,0.0);
    minDistancia=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));

    newMovement.x=posEnemy.x+3.0;newMovement.z=posEnemy.z;
    enemyDir=RIGHTWARD;
    distancia=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistancia>distancia){
        result.first=enemyDir;
        result.second=vec3f(3.0,0.0,0.0);
        minDistancia=distancia;
    }

    newMovement.x=posEnemy.x;newMovement.z=posEnemy.z-3.0;
    enemyDir=BACKWARD;
    distancia=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistancia>distancia){
        result.first=enemyDir;
        result.second=vec3f(0.0,0.0,-3.0);
        minDistancia=distancia;
    }

    newMovement.x=posEnemy.x;newMovement.z=posEnemy.z+3.0;
    enemyDir=FORWARD;
    distancia=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistancia>distancia){
        result.first=enemyDir;
        result.second=vec3f(0.0,0.0,3.0);
        minDistancia=distancia;
    }

    newMovement.x=posEnemy.x-2.0;newMovement.z=posEnemy.z+2.0;
    enemyDir=FOR_LEFTWARD;
    distancia=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistancia>distancia){
        result.first=enemyDir;
        result.second=vec3f(-2.0,0.0,2.0);
        minDistancia=distancia;
    }

    newMovement.x=posEnemy.x+2.0;newMovement.z=posEnemy.z+2.0;
    enemyDir=FOR_RIGHTWARD;
    distancia=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistancia>distancia){
        result.first=enemyDir;;
        result.second=vec3f(+2.0,0.0,+2.0);
        minDistancia=distancia;
    }

    newMovement.x=posEnemy.x-2.0;newMovement.z=posEnemy.z-2.0;
    enemyDir=BACK_LEFTWARD;
    distancia=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistancia>distancia){
        result.first=enemyDir;
        result.second=vec3f(-2.0,0.0,-2.0);
        minDistancia=distancia;
    }

    newMovement.x=posEnemy.x+2.0;newMovement.z=posEnemy.z-2.0;
    enemyDir=BACK_RIGHTWARD;
    distancia=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistancia>distancia){
        result.first=enemyDir;
        result.second=vec3f(2.0,0.0,-2.0);
        minDistancia=distancia;
    }

    return result;
}
