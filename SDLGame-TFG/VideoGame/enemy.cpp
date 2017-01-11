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

Enemy::Enemy(float aLife,vec3f aPosition,vec3f aRadioActivity)
{
    life=aLife;
    position=vec4f(aPosition.x,aPosition.y,aPosition.z,1.0);
    radioActivity=aRadioActivity;

    acceleratedMove=new AcceleratedMovement();
    acceleratedMove->resetState();
    direction=FORWARD;
    isMoving=false;
    isFalling=false;
    isJumping=false;
    isHitting=false;
    isImpacted=false;
    isShielded=false;
    enemyActivate=false;
    MeshCollection * meshCollect =MeshCollection::getInstance();
    MaterialCollection * materialCollect =MaterialCollection::getInstance();

    //Print a message for check
    cout<< "< Game is loading our enemy >"<< endl;
    //////////////////////////////////////////////////////
    /////              All the sounds                /////
    //////////////////////////////////////////////////////
    SoundCollection * soundCollect =SoundCollection::getInstance();

    enemySound.push_back(soundCollect->getSound(EMOVE));
    enemySound.push_back(soundCollect->getSound(EHIT));
    //////////////////////////////////////////////////////
    /////             Initialize text                /////
    //////////////////////////////////////////////////////
    TTF_Font *font=TTF_OpenFont( "font/Xolonium-Regular.ttf", 40);
    SDL_Color color= {255,0,0};
    currentText=new Text(mVOID,font,color,false);
    activatedDialog=false;

    //////////////////////////////////////////////////////
    /////                  LEGS                      /////
    //////////////////////////////////////////////////////

    //Create a new Movement
    Matrix4f * moveLegRight=new Matrix4f();
    moveLegRight->identity();
    moveMatrix.push_back(moveLegRight);

    Matrix4f * moveLegLeft=new Matrix4f();
    moveLegLeft->identity();
    moveMatrix.push_back(moveLegLeft);

    Matrix4f *transLeg=new Matrix4f();
    transLeg->translation(0.0,-0.6,0.0);

    //Leg Left
    NodeSceneGraph * legLeft=new NodeSceneGraph();
    legLeft->add(moveLegLeft);
    legLeft->add(transLeg);
    legLeft->add(materialCollect->getMaterial(mENEMY));
    legLeft->add(meshCollect->getMesh(EFOOT));

    //Leg Right
    NodeSceneGraph * legRight=new NodeSceneGraph();
    legRight->add(moveLegRight);
    legRight->add(transLeg);
    legRight->add(materialCollect->getMaterial(mENEMY));
    legRight->add(meshCollect->getMesh(EFOOT));

    //////////////////////////////////////////////////////
    /////                  Arms                      /////
    //////////////////////////////////////////////////////


    //Create a new Movement
    Matrix4f * moveElbowRight=new Matrix4f();
    moveElbowRight->identity();
    moveMatrix.push_back(moveElbowRight);

    Matrix4f * moveElbowLeft=new Matrix4f();
    moveElbowLeft->identity();
    moveMatrix.push_back(moveElbowLeft);

    Matrix4f * moveArmRight=new Matrix4f();
    moveArmRight->identity();
    moveMatrix.push_back(moveArmRight);

    Matrix4f * moveArmLeft=new Matrix4f();
    moveArmLeft->identity();
    moveMatrix.push_back(moveArmLeft);


    //Material * materialArmour=new Material(vec3f(0.8f, 0.8f, 0.8f),vec3f(0.8f, 0.8f, 0.8f),vec3f(0.8f, 0.8f, 0.8f),32.0f,"./textures/plateArmor.png");

    Matrix4f * scaleHandInvert=new Matrix4f();
    scaleHandInvert->scale(1.0,1.0,-1.0);

    Matrix4f * transHand=new Matrix4f();
    transHand->translation(-0.15,-0.2,0.0);

    Matrix4f * transHandLeft=new Matrix4f();
    transHandLeft->translation(0.15,-0.2,0.0);

    Matrix4f * rotateXHand=new Matrix4f();
    rotateXHand->rotation(30,1,0,0);

    Matrix4f * rotateYHand=new Matrix4f();
    rotateYHand->rotation(180,0,1,0);

    Matrix4f * rotateShoulder=new Matrix4f();
    rotateShoulder->rotation(180,0.0,1.0,0.0);

    Matrix4f * transElbow=new Matrix4f();
    transElbow->translation(0.0,-0.4,0.0);

    Matrix4f * transArms=new Matrix4f();
    transArms->translation(0.0,-0.3,-0.2);

    //Arms
    NodeSceneGraph * handRight=new NodeSceneGraph();
    handRight->add(transElbow);
    handRight->add(moveElbowRight);
    handRight->add(transHand);
    handRight->add(materialCollect->getMaterial(mENEMY));
    handRight->add(meshCollect->getMesh(EHAND));

    NodeSceneGraph * handLeft=new NodeSceneGraph();
    handLeft->add(transElbow);
    handLeft->add(moveElbowLeft);
    handLeft->add(transHandLeft);
    //handLeft->add(scaleHandInvert);
    handLeft->add(rotateYHand);
    handLeft->add(materialCollect->getMaterial(mENEMY));
    handLeft->add(meshCollect->getMesh(EHAND));

    //Arm left
    NodeSceneGraph * ArmLeft=new NodeSceneGraph();
    ArmLeft->add(transArms);
    ArmLeft->add(moveArmLeft);
    ArmLeft->add(handLeft);


    //Arm Right
    NodeSceneGraph * ArmRight=new NodeSceneGraph();
    ArmRight->add(transArms);
    ArmRight->add(moveArmRight);
    ArmRight->add(handRight);

    //////////////////////////////////////////////////////
    /////         Construction of the hero           /////
    //////////////////////////////////////////////////////

    //Movement for our hero
    AvatarMove::moveAvatar= new Matrix4f();
    AvatarMove::moveAvatar->translation(position.x,position.y,position.z);
    root->add(AvatarMove::moveAvatar);

    Matrix4f *transLegScene=new Matrix4f();
    transLegScene->translation(-0.4,0.0,0.0);

    Matrix4f *transLegSceneI=new Matrix4f();
    transLegSceneI->translation(0.2,0.97,0.0);

    Matrix4f * scaleHero=new Matrix4f();
    scaleHero->scale(0.5,0.5,0.5);

    Matrix4f * trasnArms=new Matrix4f();
    trasnArms->translation(-0.6,0.0,0.0);

    Matrix4f *trasnArmsI=new Matrix4f();
    trasnArmsI->translation(0.3,0.3,0.3);

    Matrix4f *transHead=new Matrix4f();
    transHead->translation(0.0,1.8,0.0);

    Matrix4f *transChest=new Matrix4f();
    transChest->translation(0.0,1.3,-0.3);

    NodeSceneGraph * chestNode=new NodeSceneGraph();
    chestNode->add(materialCollect->getMaterial(mENEMY));
    chestNode->add(meshCollect->getMesh(ECHEST));

    NodeSceneGraph * headNode=new NodeSceneGraph();
    headNode->add(transHead);
    headNode->add(materialCollect->getMaterial(mENEMY));
    headNode->add(meshCollect->getMesh(EHEAD));

    NodeSceneGraph * chest_ArmsNode=new NodeSceneGraph();
    chest_ArmsNode->add(transChest);
    chest_ArmsNode->add(chestNode);
    chest_ArmsNode->add(trasnArmsI);
    chest_ArmsNode->add(ArmLeft);
    chest_ArmsNode->add(trasnArms);
    chest_ArmsNode->add(ArmRight);

    root->add(scaleHero);
    root->add(materialCollect->getMaterial(mWOOD));
    root->add(headNode);
    root->add(chest_ArmsNode);
    root->add(transLegSceneI);
    root->add(materialCollect->getMaterial(mWOOD));
    root->add(legLeft);
    root->add(transLegScene);
    root->add(legRight);
    currentTime=SDL_GetTicks();
    jumpDelay=currentTime;
    dmgDelay=currentTime;

    //Init all animations of our hero
    initAnimation();
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

    if(activatedDialog)
        currentText->visualization(cv);
}

//**********************************************************************//

void Enemy::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap){
    pair<avatarDirection,vec3f> moveHero;
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
        moveHero=IA.nextPosition(vec3f(position.x,position.y,position.z),posHero);

        if((moveHero.second.x!=0.0 || moveHero.second.y!=0.0 || moveHero.second.z!=0.0)&& !isImpacted){ //IA-> is not near of our hero
            if(!moveBody(moveHero.second,moveHero.first) && !isJumping && !isFalling && jumpDelay<(time-1000)){
                activeJump(vec3f(0.0,12.0,0.0),vec3f(0.0,5.0,0.0));
                jumpDelay=time;
            }
        }
        else{ //IA -> is near of our hero so the enemy doesn't move
            isHitting=true;
            if(hero->isHit() && dmgDelay<(time-700) && detectHit(posHero,dirHero)){ //If the hero is hitting
                addLife(-10);
                activatedDialog=true;
                currentText->setPosition(vec3f(position.x,position.y+1.5f,position.z));
                currentText->setMessage("-10");
                currentText->init();
                dmgDelay=time;
                activeImpact(dirHero);
            }
            else { //If the hero is not hitting
                if(dmgDelay<(time-300))
                    activatedDialog=false;
            }
            if(isImpacted) //if is impacted
                impactMove(time);
        }
        if(isJumping){
            jump(time);
        }
        else
            gravity(time);
    }

    //Update our vec4f position
    position=moveAvatar->product(vec4f());
    //Update Animation
    if(isMoving && !isFalling && !isJumping && !isHitting){
        animation.updateState(time-currentTime);
        for(unsigned i=0;i<moveMatrix.size();i++)
            moveMatrix[i]->setMatrix(animation.readMatrix(i).getMatrix());
    }
    else if(isFalling){
        for(unsigned i=0;i<moveMatrix.size();i++)
            moveMatrix[i]->identity();
        Matrix4f rot;
        rot.rotation(30,0,0,1);
        moveMatrix[4]->setMatrix(rot.getMatrix());
        rot.rotation(-30,0,0,1);
        moveMatrix[5]->setMatrix(rot.getMatrix());
    }
    else if(isJumping){
        for(unsigned i=0;i<moveMatrix.size();i++)
            moveMatrix[i]->identity();
        Matrix4f rot;
        rot.rotation(30,1,0,0);
        moveMatrix[4]->setMatrix(rot.getMatrix());
        moveMatrix[5]->setMatrix(rot.getMatrix());
    }
    else if(isHitting){
        animationHit.updateState(time-currentTime);
        for(unsigned i=0;i<moveMatrix.size();i++)
            moveMatrix[i]->setMatrix(animationHit.readMatrix(i).getMatrix());

        if(animationHit.getScriptState(3)==3 || animationHit.getScriptState(4)==1){
            isHitting=false;
            hero->takeDamage(position,direction,-10);
        }
    }

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
//                              PRIVATE                                 //
//**********************************************************************//

 void Enemy::initAnimation(){
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
    animation.add(LegScriptRight);
    animation.add(LegScriptLeft);

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
    animation.add(ElbowScriptRight);
    animation.add(ElbowScriptLeft);
    animation.add(ArmScriptRight);
    animation.add(ArmScriptLeft);

    /////////////////////////////////
    // ANIMATION HIT
    /////////////////////////////////
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
    animationHit.add(LegScriptRight);
    animationHit.add(LegScriptLeft);

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
    animationHit.add(ElbowScriptRight); //4
    animationHit.add(ElbowScriptLeft);  //5
    animationHit.add(ArmScriptRight);   //6
    animationHit.add(ArmScriptLeft);    //7
 }

