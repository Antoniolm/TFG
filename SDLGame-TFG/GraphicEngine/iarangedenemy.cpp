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

#include "iarangedenemy.h"

IARangedEnemy::IARangedEnemy()
{
    //ctor
}

//**********************************************************************//

IARangedEnemy::~IARangedEnemy()
{
    //dtor
}

//**********************************************************************//

pair<avatarDirection,vec3f> IARangedEnemy::nextPosition(vec3f posEnemy,vec3f posHero){
    vec3f newMovement;
    float distance,minDistance;
    avatarDirection enemyDir;
    pair<avatarDirection,vec3f> result;

    //If the enemy is near of our hero. The enemy stop the movement
    if(sqrt(pow(posEnemy.x-posHero.x,2.0)+pow(posEnemy.y-posHero.y,2.0)+pow(posEnemy.z-posHero.z,2.0))<0.7){

        if(posEnemy.z>posHero.z && (posEnemy.x>=posHero.x-0.3 && posEnemy.x<=posHero.x+0.3))
            result.first=BACKWARD;
        else if(posEnemy.z<posHero.z && (posEnemy.x>=posHero.x-0.3 && posEnemy.x<=posHero.x+0.3))
            result.first=FORWARD;
        else if(posEnemy.x<posHero.x && (posEnemy.z>=posHero.z-0.3 && posEnemy.z<=posHero.z+0.3))
                result.first=RIGHTWARD;
        else if(posEnemy.x>posHero.x && (posEnemy.z>=posHero.z-0.3 && posEnemy.z<=posHero.z+0.3))
                result.first=LEFTWARD;
        else if(posEnemy.x<posHero.x && posEnemy.z>posHero.z)
                result.first=BACK_RIGHTWARD;
        else if(posEnemy.x>posHero.x && posEnemy.z>posHero.z)
                result.first=BACK_LEFTWARD;
        else if(posEnemy.x<posHero.x && posEnemy.z<posHero.z)
                result.first=FOR_RIGHTWARD;
        else if(posEnemy.x>posHero.x && posEnemy.z<posHero.z)
                result.first=FOR_LEFTWARD;
        result.second=vec3f(0.0f,0.0f,0.0f);
        return result;
    }

    //Else
    //Case -> Leftward will be the movement of our enemy
    newMovement.x=posEnemy.x-2.0;newMovement.y=posEnemy.y;newMovement.z=posEnemy.z;
    enemyDir=LEFTWARD;
    result.first=enemyDir;
    result.second=vec3f(-2.0f,0.0f,0.0f);
    minDistance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));

    //Case -> Rightward
    newMovement.x=posEnemy.x+2.0;newMovement.z=posEnemy.z;
    enemyDir=RIGHTWARD;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance){ //If Rightward will be our move -> The distance is smallest between them
        result.first=enemyDir;
        result.second=vec3f(2.0f,0.0f,0.0f);
        minDistance=distance;
    }

    //Case -> Backward
    newMovement.x=posEnemy.x;newMovement.z=posEnemy.z-2.0;
    enemyDir=BACKWARD;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance){ //If Backward will be our move -> The distance is smallest between them
        result.first=enemyDir;
        result.second=vec3f(0.0f,0.0f,-2.0f);
        minDistance=distance;
    }

    //Case -> Forward
    newMovement.x=posEnemy.x;newMovement.z=posEnemy.z+2.0;
    enemyDir=FORWARD;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance){ //If Forward will be our move -> The distance is smallest between them
        result.first=enemyDir;
        result.second=vec3f(0.0f,0.0f,2.0f);
        minDistance=distance;
    }

    //Case -> Left-forward
    newMovement.x=posEnemy.x-1.0;newMovement.z=posEnemy.z+1.0;
    enemyDir=FOR_LEFTWARD;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance){ //If Left-forward will be our move -> The distance is smallest between them
        result.first=enemyDir;
        result.second=vec3f(-1.0f,0.0f,1.0f);
        minDistance=distance;
    }

    //Case -> Right-forward
    newMovement.x=posEnemy.x+1.0;newMovement.z=posEnemy.z+1.0;
    enemyDir=FOR_RIGHTWARD;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance){ //If Right-forward will be our move -> The distance is smallest between them
        result.first=enemyDir;;
        result.second=vec3f(+1.0f,0.0f,+1.0f);
        minDistance=distance;
    }

    //Case -> Left-backward
    newMovement.x=posEnemy.x-1.0;newMovement.z=posEnemy.z-1.0;
    enemyDir=BACK_LEFTWARD;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance){ //If Left-backward will be our move -> The distance is smallest between them
        result.first=enemyDir;
        result.second=vec3f(-1.0f,0.0f,-1.0f);
        minDistance=distance;
    }

    //Case -> Right-backward
    newMovement.x=posEnemy.x+1.0;newMovement.z=posEnemy.z-1.0;
    enemyDir=BACK_RIGHTWARD;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(minDistance>distance){ //If Right-backward will be our move -> The distance is smallest between them
        result.first=enemyDir;
        result.second=vec3f(1.0f,0.0f,-1.0f);
        minDistance=distance;
    }

    return result;
}
