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
    vec3f newMovement,distance,beforeDistance;
    avatarDirection enemyDir;
    pair<avatarDirection,vec3f> result;

    newMovement.x=posEnemy.x-3.0;newMovement.y=posEnemy.y;newMovement.z=posEnemy.z;
    enemyDir=LEFTWARD;
    distance=newMovement-posHero;
    cout<< "Position"<< posEnemy.x<< " "<< posEnemy.y<< " "<< posEnemy.z<< endl;
    cout<< "Distance"<< distance.x<< " "<< distance.y<< " "<< distance.z<< endl;
    result.first=enemyDir;
    result.second=vec3f(-3.0,0.0,0.0);

    newMovement.x=posEnemy.x+3.0;newMovement.z=posEnemy.z;
    enemyDir=RIGHTWARD;
    beforeDistance=newMovement-posHero;
    if(beforeDistance.x<distance.x && beforeDistance.z<distance.z){
        distance=beforeDistance;
        result.first=enemyDir;
        result.second=vec3f(3.0,0.0,0.0);
    }

    newMovement.x=posEnemy.x;newMovement.z=posEnemy.z-3.0;
    enemyDir=BACKWARD;
    beforeDistance=newMovement-posHero;
    if(beforeDistance.x<distance.x && beforeDistance.z<distance.z){
        distance=beforeDistance;
        result.first=enemyDir;
        result.second=vec3f(0.0,0.0,-3.0);
    }

    newMovement.x=posEnemy.x;newMovement.z=posEnemy.z+3.0;
    enemyDir=FORWARD;
    beforeDistance=newMovement-posHero;
    if(beforeDistance.x<distance.x && beforeDistance.z<distance.z){
        distance=beforeDistance;
        result.first=enemyDir;
        result.second=vec3f(0.0,0.0,3.0);
    }

    newMovement.x=posEnemy.x-2.0;newMovement.z=posEnemy.z+2.0;
    enemyDir=FOR_LEFTWARD;
    beforeDistance=newMovement-posHero;
    if(beforeDistance.x<distance.x && beforeDistance.z<distance.z){
        distance=beforeDistance;
        result.first=enemyDir;
        result.second=vec3f(-2.0,0.0,2.0);
    }

    newMovement.x=posEnemy.x+2.0;newMovement.z=posEnemy.z+2.0;
    enemyDir=FOR_RIGHTWARD;
    beforeDistance=newMovement-posHero;
    if(beforeDistance.x<distance.x && beforeDistance.z<distance.z){
        distance=beforeDistance;
        result.first=enemyDir;;
        result.second=vec3f(+2.0,0.0,+2.0);
    }

    newMovement.x=posEnemy.x-2.0;newMovement.z=posEnemy.z-2.0;
    enemyDir=BACK_LEFTWARD;
    beforeDistance=newMovement-posHero;
    if(beforeDistance.x<distance.x && beforeDistance.z<distance.z){
        distance=beforeDistance;
        result.first=enemyDir;
        result.second=vec3f(-2.0,0.0,-2.0);
    }

    newMovement.x=posEnemy.x+2.0;newMovement.z=posEnemy.z-2.0;
    enemyDir=BACK_RIGHTWARD;
    beforeDistance=newMovement-posHero;
    if(beforeDistance.x<distance.x && beforeDistance.z<distance.z){
        distance=beforeDistance;
        result.first=enemyDir;
        result.second=vec3f(2.0,0.0,-2.0);
    }

    return result;
}
