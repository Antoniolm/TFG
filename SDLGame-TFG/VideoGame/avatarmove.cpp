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

#include "avatarmove.h"
#include "../GraphicEngine/rootmap.h"

AvatarMove::AvatarMove(){
}

AvatarMove::~AvatarMove(){
    //dtor
}

bool AvatarMove::moveBody(vec3f aMove,avatarDirection aDir){
    ObjectScene * hasCollision;
    bool result=false;
    float tenthValue,tenthValue2;
    vec3f posHero=getPosition();

    //Check the collision first
    switch(aDir){
        case FORWARD:
            tenthValue=posHero.x-(int)posHero.x;
            hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y,posHero.z+0.3));

            if(tenthValue<0.5 && hasCollision==0){
                hasCollision=rootMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z+0.3));
            }
            else if(tenthValue>0.6 && hasCollision==0){
                hasCollision=rootMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z+0.3));
            }
        break;
        case BACKWARD:
            tenthValue=posHero.x-(int)posHero.x;
            hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y,posHero.z-0.3));

            if(tenthValue<0.5 && hasCollision==0){
                hasCollision=rootMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z-0.3));
            }
            else if(tenthValue>0.6 && hasCollision==0){
                hasCollision=rootMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z-0.3));
            }
        break;
        case LEFTWARD:
            tenthValue=(int)posHero.z-posHero.z;

            hasCollision=rootMap->collision(vec3f(posHero.x-0.3,posHero.y,posHero.z));

            if(tenthValue<0.5 && hasCollision==0){
                hasCollision=rootMap->collision(vec3f(posHero.x-0.3,posHero.y,posHero.z+0.2));
            }
            else if(tenthValue>0.6 && hasCollision==0){
                hasCollision=rootMap->collision(vec3f(posHero.x-0.3,posHero.y,posHero.z-0.2));
            }
        break;
        case RIGHTWARD:
            tenthValue=(int)posHero.z-posHero.z;
            hasCollision=rootMap->collision(vec3f(posHero.x+0.3,posHero.y,posHero.z));

            if(tenthValue<0.5 && hasCollision==0){
                hasCollision=rootMap->collision(vec3f(posHero.x+0.3,posHero.y,posHero.z+0.2));
            }
            else if(tenthValue>0.6 && hasCollision==0){
                hasCollision=rootMap->collision(vec3f(posHero.x+0.3,posHero.y,posHero.z-0.2));
            }
        break;
        case FOR_LEFTWARD:
            tenthValue=(int)posHero.x-posHero.x;
            tenthValue2=(int)posHero.z-posHero.z;

            hasCollision=rootMap->collision(vec3f(posHero.x-0.3,posHero.y,posHero.z+0.3));
            if(tenthValue2<0.5 && hasCollision==0){
                hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y,posHero.z+0.3));
            }
            else if(tenthValue<0.5 && hasCollision==0){
                hasCollision=rootMap->collision(vec3f(posHero.x-0.3,posHero.y,posHero.z));
            }
        break;
        case FOR_RIGHTWARD:
            tenthValue=(int)posHero.x-posHero.x;
            tenthValue2=(int)posHero.z-posHero.z;

            hasCollision=rootMap->collision(vec3f(posHero.x+0.3,posHero.y,posHero.z+0.3));

            if(tenthValue2<0.5 && hasCollision==0){
                hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y,posHero.z+0.3));
            }
            else if(tenthValue<0.5 && hasCollision==0){
                hasCollision=rootMap->collision(vec3f(posHero.x+0.3,posHero.y,posHero.z));
            }
        break;
        case BACK_LEFTWARD:
            tenthValue=(int)posHero.x-posHero.x;
            tenthValue2=(int)posHero.z-posHero.z;

            hasCollision=rootMap->collision(vec3f(posHero.x-0.3,posHero.y,posHero.z-0.3));
            if(tenthValue2<0.5 && hasCollision==0){
                hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y,posHero.z-0.3));
            }
            else if(tenthValue<0.5 && hasCollision==0){
                hasCollision=rootMap->collision(vec3f(posHero.x-0.3,posHero.y,posHero.z));
            }
        break;
        case BACK_RIGHTWARD:
            tenthValue=(int)posHero.x-posHero.x;
            tenthValue2=(int)posHero.z-posHero.z;

            hasCollision=rootMap->collision(vec3f(posHero.x+0.3,posHero.y,posHero.z-0.3));

            if(tenthValue2>0.5 && hasCollision==0){
                hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y,posHero.z-0.3));
            }
            else if(tenthValue>0.5 && hasCollision==0){
                hasCollision=rootMap->collision(vec3f(posHero.x+0.3,posHero.y,posHero.z));
            }
        break;
    }

    float time=SDL_GetTicks();
    if(hasCollision==0){ //Case -> the hero can move = No collision
        if(direction!=aDir){
            vec4f position;
            position=moveAvatar->product(position);
            Matrix4f transHero;
            transHero.translation(position.x,position.y,position.z);
            LinearMovement lineMove(aMove);
            transHero.product(lineMove.updateState(time-currentTime).getMatrix());

            moveAvatar->rotation(45*aDir,0.0f,1.0f,0.0f);
            moveAvatar->product(transHero.getMatrix());

            direction=aDir;
        }
        else{
            LinearMovement lineMove(aMove);
            moveAvatar->product(lineMove.updateState(time-currentTime).getMatrix());
        }
        result=true;
    }
    else{   //Case -> not Move for colission but the hero change the rotation in the Y-axis
        if(direction!=aDir){
            vec4f position;
            position=moveAvatar->product(position);
            Matrix4f transHero;
            transHero.translation(position.x,position.y,position.z);

            moveAvatar->rotation(45*aDir,0.0f,1.0f,0.0f);
            moveAvatar->product(transHero.getMatrix());

            direction=aDir;

        }
    }

    isMoving=true;

    return result;
}


bool AvatarMove::gravity(float time){
    ObjectScene * hasCollision;
    bool result=true;
    float tenthValueX,tenthValueZ;

    if(!isJumping){
    GLfloat * moveGravity=acceleratedMove->updateState(time-currentTime).getMatrix();

    vec3f posHero=getPosition();
    posHero.y-=0.51;

    //Get the tenth of our position
    tenthValueX=posHero.x-(int)posHero.x;
    tenthValueZ=(int)posHero.z-posHero.z;

    //Check the collision in the center
    hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y,posHero.z));

    //Check the collision in the area
    if(tenthValueX>0.5 && hasCollision==0){ //Case tenth in x >0.5
        if( tenthValueZ<0.5){ //case Tenth in x >0.5 and tenth in z <0.5
            hasCollision=rootMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z));
            if(hasCollision==0)
                hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y,posHero.z-0.2));
            if(hasCollision==0)
                hasCollision=rootMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z-0.2));
        }else{  //case Tenth in x >0.5 and tenth in z >= 0.5
            hasCollision=rootMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z));
            if(hasCollision==0)
                hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y,posHero.z+0.2));
            if(hasCollision==0)
                hasCollision=rootMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z+0.2));
        }
    }
    else if(tenthValueX<0.5 && hasCollision==0){ //Case tenth in x <0.5
        if( tenthValueZ<0.5){ //case Tenth in x <0.5 and tenth in z <0.5
            hasCollision=rootMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z));
            if(hasCollision==0)
                hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y,posHero.z-0.2));
            if(hasCollision==0)
                hasCollision=rootMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z-0.2));
        }else{ //case Tenth in x <0.5 and tenth in z >= 0.5
            hasCollision=rootMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z));
            if(hasCollision==0)
                hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y,posHero.z+0.2));
            if(hasCollision==0)
            hasCollision=rootMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z+0.2));
        }
    }

    if(hasCollision==0){ //if not collision
        moveAvatar->product(moveGravity);
        isFalling=true;
    }
    else {
        if(isFalling){
            vec3f positionObs=hasCollision->getPosition();
            BoundingBox box=hasCollision->getBoundingBox();
            Matrix4f trans;
            trans.translation(0.0,(positionObs.y+box.maxValue.y)-(posHero.y-0.23),0.0);

            moveAvatar->product(trans.getMatrix());
        }
        isFalling=false;
        acceleratedMove->resetState();
        result=false;
    }
    }
    else {
        result=false;
    }

    return result;
}

//**********************************************************************//

void AvatarMove::activeJump(float velocity,float acceleration){
    acceleratedMove=new AcceleratedMovement(0.0f,velocity,0.0f,0.0f,acceleration-G,0.0f);
    isJumping=true;
}

//**********************************************************************//

bool AvatarMove::jump(float time){
    ObjectScene * hasCollision;
    bool result=true;
    float tenthValueX,tenthValueZ;

    GLfloat * moveGravity=acceleratedMove->updateState(time-currentTime).getMatrix();

    vec3f posHero=getPosition();
    posHero.y+=(0.22+moveGravity[13]);

    if(moveGravity[13]>0){
        //Get the tenth of our position
        tenthValueX=posHero.x-(int)posHero.x;
        tenthValueZ=(int)posHero.z-posHero.z;

        //Check the collision in the center
        hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y,posHero.z));

        //Check the collision in the area
        if(tenthValueX>0.5 && hasCollision==0){ //Case tenth in x >0.5
            if( tenthValueZ<0.5){ //case Tenth in x >0.5 and tenth in z <0.5
                hasCollision=rootMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z));
                if(hasCollision==0)
                    hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y,posHero.z-0.2));
                if(hasCollision==0)
                    hasCollision=rootMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z-0.2));
            }else{  //case Tenth in x >0.5 and tenth in z >= 0.5
                hasCollision=rootMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z));
                if(hasCollision==0)
                    hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y,posHero.z+0.2));
                if(hasCollision==0)
                    hasCollision=rootMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z+0.2));
            }
        }
        else if(tenthValueX<0.5 && hasCollision==0){ //Case tenth in x <0.5
            if( tenthValueZ<0.5){ //case Tenth in x <0.5 and tenth in z <0.5
                hasCollision=rootMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z));
                if(hasCollision==0)
                    hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y,posHero.z-0.2));
                if(hasCollision==0)
                    hasCollision=rootMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z-0.2));
            }else{ //case Tenth in x <0.5 and tenth in z >= 0.5
                hasCollision=rootMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z));
                if(hasCollision==0)
                    hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y,posHero.z+0.2));
                if(hasCollision==0)
                hasCollision=rootMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z+0.2));
            }
        }

        if(hasCollision==0){ //if not collision
            moveAvatar->product(moveGravity);
            isJumping=true;
        }
        else {
            isJumping=false;
            isFalling=true;
            acceleratedMove->resetState();
            result=false;
        }
    }else{
        isJumping=false;
        isFalling=true;
        acceleratedMove->resetState();
        result=false;
    }

    return result;
}

//**********************************************************************//

vec3f AvatarMove::getPosition(){
    vec4f position;
    position=moveAvatar->product(position);
    return vec3f(position.x,position.y,position.z);
}

