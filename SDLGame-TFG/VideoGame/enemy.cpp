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

#include "enemy.h"

Enemy::Enemy(){

}

//**********************************************************************//

Enemy::Enemy(float aLife,vec3f aPosition,vec3f aRadioActivity)
{
}

//**********************************************************************//

Enemy::~Enemy()
{
    delete currentText;
    for(vector<Matrix4f *>::iterator it = moveMatrix.begin() ; it != moveMatrix.end(); ++it){
        delete (*it);
    }
}

//**********************************************************************//

void Enemy::visualization(Context & cv){
    root->visualization(cv);

    if(activatedDialog){
        currentText->setPosition(vec3f(position.x,position.y+1.5f,position.z));
        currentText->visualization(cv);
    }
}

//**********************************************************************//

void Enemy::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap){
    vec3f aux;
    currentMap=rootMap;
    Hero * hero=rootMap->getHero();
    vec3f posHero=hero->getPosition();
    avatarDirection dirHero=hero->getDirection();
    vec3f distance=vec3f(position.x,position.y,position.z)-posHero;

    if(time-currentTime>200)
        currentTime=time-50;

    //check if the enemy will be activated in this frame
    if((distance.x>-radioActivity.x && distance.x<radioActivity.x)&&(distance.y>-radioActivity.y && distance.y<radioActivity.y)&&(distance.z>-radioActivity.z && distance.z<radioActivity.z)){
        enemyActivate=true;
    }

    if(enemyActivate){ //If enemy is activated
        if(IADelay<(time-200)){ //Delay IA
            currentMove=IA->nextPosition(vec3f(position.x,position.y,position.z),posHero);
            IADelay=time;
        }
        if((currentMove.second.x!=0.0 || currentMove.second.y!=0.0 || currentMove.second.z!=0.0)&& !isImpacted){ //IA-> is not near of our hero
            if(!moveBody(currentMove.second,currentMove.first) && !isJumping && !isFalling && jumpDelay<(time-1000)){ //If not move -> enemy jump
                activeJump(vec3f(0.0,12.0,0.0),vec3f(0.0,5.0,0.0));
                jumpDelay=time;
            }
            if(isHitting) //If is hitting
                animations.resetAnimation(1);
            isHitting=false;

        }
        else{ //IA -> is near of our hero so the enemy doesn't move
            isHitting=true;
            changeDirection(currentMove.first);
            if(hero->isHit() && dmgDelay<(time-700)){ //If the hero is hitting
                takeDamage(posHero,dirHero,-10);
            }

            if(isImpacted) //if is impacted
                impactMove(time);
        }
        if(isJumping){
            jump(time);
        }
        else{
            ObjectScene * object=gravity(time);
            if(object!=0 && object->getDamage()!=0.0 && dmgDelay<(time-200)){ //If the object do damage
                takeDamage(object->getDamage());
                dmgDelay=time;
            }
        }
    }

    if(dmgDelay<(time-300))
        activatedDialog=false;


    //Update our vec4f position
    position=moveAvatar->product(vec4f());

    ////////////////////////////
    //UPDATE ANIMATION
    ////////////////////////////
    if(isMoving && !isFalling && !isJumping && !isHitting){
        animations.activate(0);
    }
    else if(isHitting){
        animations.activate(1);
        ScriptLMD * animationHit=animations.getAnimation();
        if((animationHit->getScriptState(2)==3 || animationHit->getScriptState(3)==1) && hitDelay<(time-700)){
            hero->takeDamage(position,direction,-10);
            hitDelay=time;
        }
    }

    animations.update(time-currentTime);

    ScriptLMD * animatio=animations.getAnimation();
    for(unsigned i=0;i<moveMatrix.size();i++)
        moveMatrix[i]->setMatrix(animatio->readMatrix(i).getMatrix());



    currentTime+=(time-currentTime);
}

//**********************************************************************//

void Enemy::activatedEnemy(bool value){
    enemyActivate=value;
}

//**********************************************************************//

bool Enemy::isActivate(){
    return enemyActivate;
}

//**********************************************************************//

vec3f Enemy::getRadioActivity(){
    return radioActivity;
}

//**********************************************************************//

 float Enemy::getLife(){
    return life;
 }

 //**********************************************************************//

 void Enemy::takeDamage(vec3f posAvatar,avatarDirection dirAvatar,float value){
     //check if the hero is shielding

    if(detectHit(posAvatar,dirAvatar)&& dmgDelay<(currentTime-700) ){
        addLife(value);
        stringstream convert;
        int lastValue;

        if(activatedDialog){
            string currentValue=currentText->getMessage();
            lastValue=atoi(currentValue.c_str());
            value+=lastValue;
        }
        convert << value;

        activatedDialog=true;
        currentText->setPosition(vec3f(position.x,position.y+1.5f,position.z));
        currentText->setMessage(convert.str());
        currentText->init();

        dmgDelay=currentTime;

        if(!isImpacted)
            activeImpact(dirAvatar);
        enemySound[1]->stop();
        enemySound[1]->play();
    }
 }

 //**********************************************************************//

void Enemy::takeDamage(float value){
    addLife(value);

    stringstream convert;
    int lastValue;

    if(activatedDialog){
        string currentValue=currentText->getMessage();
        lastValue=atoi(currentValue.c_str());
        value+=lastValue;
    }

    convert << value;

    activatedDialog=true;
    currentText->setPosition(vec3f(position.x,position.y+1.5f,position.z));
    currentText->setMessage(convert.str());
    currentText->init();

    enemySound[1]->stop();
    enemySound[1]->play();
 }


//**********************************************************************//
//                              PRIVATE                                 //
//**********************************************************************//

 void Enemy::initAnimation(){

    /////////////////////////////////
    // ANIMATION MOVE
    /////////////////////////////////
    ///////////////////
    // LEG
    //////////////////
    ScriptLMD * animation=new ScriptLMD();
    OscillateRotation * oscillateLeg=new OscillateRotation(true,40,0,1,150,vec3f(1,0,0),2);
    OscillateRotation * oscillateLegSecond=new OscillateRotation(false,0,-20,1,50,vec3f(1,0,0),1);
    MatrixStatic * notMove=new MatrixStatic();

    //Movement to the first leg
    MatrixScript * LegScriptLeft=new MatrixScript();
    LegScriptLeft->add(0.5,oscillateLeg);
    LegScriptLeft->add(0.5,oscillateLegSecond);


    //Movement to the second leg
    MatrixScript * LegScriptRight=new MatrixScript();
    LegScriptRight->add(0.5,oscillateLegSecond);
    LegScriptRight->add(0.5,oscillateLeg);

    //Add the script to our animation
    animation->add(LegScriptRight);
    animation->add(LegScriptLeft);

    ///////////////////
    // ARM
    //////////////////
    //Matrix4fDinamic
    OscillateRotation * oscillateShoulder=new OscillateRotation(true,60,0,1,250,vec3f(1.0,0.0,0),2);

    //Movement to the first arm
    MatrixScript * ElbowScriptLeft=new MatrixScript();
    MatrixScript * ArmScriptLeft=new MatrixScript();
    ElbowScriptLeft->add(0.5,notMove);
    ElbowScriptLeft->add(0.5,notMove);
    ArmScriptLeft->add(0.5,oscillateShoulder);
    ArmScriptLeft->add(0.5,notMove);

    //Movement to the second arm
    MatrixScript * ElbowScriptRight=new MatrixScript();
    MatrixScript * ArmScriptRight=new MatrixScript();
    ElbowScriptRight->add(0.5,notMove);
    ElbowScriptRight->add(0.5,notMove);
    ArmScriptRight->add(0.5,notMove);
    ArmScriptRight->add(0.5,oscillateShoulder);


    //Add the script to our animation
    animation->add(ElbowScriptRight);
    animation->add(ElbowScriptLeft);
    animation->add(ArmScriptRight);
    animation->add(ArmScriptLeft);

    animations.add(animation);

    /////////////////////////////////
    // ANIMATION HIT
    /////////////////////////////////
    ///////////////////
    // LEG
    //////////////////
    animation=new ScriptLMD();
    oscillateLeg=new OscillateRotation(true,40,0,1,150,vec3f(1,0,0),2);
    oscillateLegSecond=new OscillateRotation(false,0,-20,1,50,vec3f(1,0,0),1);

    //Movement to the first leg
    LegScriptLeft=new MatrixScript();
    LegScriptLeft->add(0.5,notMove);
    LegScriptLeft->add(0.5,notMove);


    //Movement to the second leg
    LegScriptRight=new MatrixScript();
    LegScriptRight->add(0.5,notMove);
    LegScriptRight->add(0.5,notMove);

    //Add the script to our animation
    animation->add(LegScriptRight);
    animation->add(LegScriptLeft);

    ///////////////////
    // ARM
    //////////////////
    //Matrix4fDinamic
    OscillateRotation * shoulderCharge=new OscillateRotation(false,0,-40,1,250,vec3f(1.0,0.0,0),1);
    OscillateRotation * oscillateElbow=new OscillateRotation(true,60,0,1,250,vec3f(1.0,0.0,0),1);
    Matrix4f * rotateShoulder=new Matrix4f();
    rotateShoulder->rotation(90,1.0,0.0,0.0);

    Matrix4f * rotateElbow=new Matrix4f();
    rotateElbow->rotation(-30,1.0,0.0,0.0);

    MatrixStatic *staticShoulder=new MatrixStatic(*rotateShoulder);
    MatrixStatic *staticElbow=new MatrixStatic(*rotateElbow);

    //Movement to the first arm
    ElbowScriptLeft=new MatrixScript();
    ArmScriptLeft=new MatrixScript();
    ElbowScriptLeft->add(0.5,oscillateElbow);
    ElbowScriptLeft->add(0.5,staticElbow);
    ElbowScriptLeft->add(0.5,notMove);
    ElbowScriptLeft->add(0.5,notMove);
    ArmScriptLeft->add(0.5,shoulderCharge);
    ArmScriptLeft->add(0.5,staticShoulder);
    ArmScriptLeft->add(0.5,notMove);
    ArmScriptLeft->add(0.5,notMove);

    //Movement to the second arm
    ElbowScriptRight=new MatrixScript();
    ArmScriptRight=new MatrixScript();
    ElbowScriptRight->add(0.5,notMove);
    ElbowScriptRight->add(0.5,notMove);
    ElbowScriptRight->add(0.5,oscillateElbow);
    ElbowScriptRight->add(0.5,staticElbow);
    ArmScriptRight->add(0.5,notMove);
    ArmScriptRight->add(0.5,notMove);
    ArmScriptRight->add(0.5,shoulderCharge);
    ArmScriptRight->add(0.5,staticShoulder);


    //Add the script to our animation
    animation->add(ElbowScriptRight); //4
    animation->add(ElbowScriptLeft);  //5
    animation->add(ArmScriptRight);   //6
    animation->add(ArmScriptLeft);    //7

    animations.add(animation);
 }

