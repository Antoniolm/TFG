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

#include "hero.h"

Hero::Hero()
{
    acceleratedMove=new AcceleratedMovement();
    acceleratedMove->resetState();
    direction=FORWARD;
    isMoving=false;
    isMoveCollision=false;
    isFalling=false;
    isJumping=false;
    isHitting=false;
    life=150;
    currentCoin=0;
    MeshCollection * meshCollect =MeshCollection::getInstance();
    MaterialCollection * materialCollect =MaterialCollection::getInstance();


    //Print a message for check
    cout<< "< Game is loading our hero >"<< endl;

    //////////////////////////////////////////////////////
    /////              All the sounds                /////
    //////////////////////////////////////////////////////
    Sound * walking=new Sound("sounds/walking.wav",1,40,3,-1);
    heroSound.push_back(walking);

    //////////////////////////////////////////////////////
    /////             Initialize text                /////
    //////////////////////////////////////////////////////
    //Dialog for speak
    TTF_Font *font=TTF_OpenFont( "font/Xolonium-Regular.ttf", 20);
    Text * currentText=new Text(mDIALOG,font);
    texts.push_back(currentText);
    activatedTexts.push_back(false);

    //Dialog for actions
    currentText=new Text(mADIALOG,font);
    texts.push_back(currentText);
    activatedTexts.push_back(false);

    //Coin Text
    font=TTF_OpenFont( "font/Xolonium-Regular.ttf", 40);
    currentText=new Text(mVOID,font,SDL_Color{0,255,0},false);
    texts.push_back(currentText);
    activatedTexts.push_back(false);

    //Damage text
    currentText=new Text(mVOID,font,SDL_Color{255,0,0},false);
    texts.push_back(currentText);
    activatedTexts.push_back(false);

    //////////////////////////////////////////////////////
    /////              Some The matrix               /////
    //////////////////////////////////////////////////////

    Matrix4f *scaleFoot=new Matrix4f();
    scaleFoot->scale(0.7,0.7,0.6);

    Matrix4f *rotateFoot=new Matrix4f();
    rotateFoot->rotation(-90,0.0,1.0,0.0);

    Matrix4f *scaleSphere=new Matrix4f();
    scaleSphere->scale(0.15,0.15,0.15);

    Matrix4f *scaleKnee=new Matrix4f();
    scaleKnee->scale(0.7,0.7,0.7);

    Matrix4f *scalePill=new Matrix4f();
    scalePill->scale(0.3,0.5,0.3);

    Matrix4f *transCylinder=new Matrix4f();
    transCylinder->translation(0.0,-0.7,0.0);

    Matrix4f *transLeg=new Matrix4f();
    transLeg->translation(0.0,-0.6,0.0);

    Matrix4f *rotateCylinder=new Matrix4f();
    rotateCylinder->rotation(90,1.0,0.0,0.0);

    Matrix4f *transMatrix=new Matrix4f();
    transMatrix->translation(0.0,0.0,0.5);

    Matrix4f *transFoot=new Matrix4f();
    transFoot->translation(0.0,-0.8,0.4);

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

    //Ankle + foot
    NodeSceneGraph * foot=new NodeSceneGraph();
    foot->add(transFoot);
    foot->add(scaleFoot);
    foot->add(materialCollect->getMaterial(mWOOD));
    foot->add(meshCollect->getMesh(FOOT));

    //knee + ankle
    NodeSceneGraph * knee_ankle=new NodeSceneGraph();

    //knee_ankle->add(transCylinder);
    //knee_ankle->add(moveKnee);
    knee_ankle->add(transCylinder);
    knee_ankle->add(foot);
    knee_ankle->add(scaleKnee);
    knee_ankle->add(meshCollect->getMesh(KNEE));

    //Leg
    NodeSceneGraph * knee_ankleRight=new NodeSceneGraph();
    knee_ankleRight->add(transCylinder);
    //knee_ankleRight->add(moveKneeRight);
    knee_ankleRight->add(knee_ankle);

    NodeSceneGraph * knee_ankleLeft=new NodeSceneGraph();
    knee_ankleLeft->add(transCylinder);
    //knee_ankleLeft->add(moveKneeLeft);
    knee_ankleLeft->add(knee_ankle);

    //Leg Left
    NodeSceneGraph * legLeft=new NodeSceneGraph();
    legLeft->add(moveLegLeft);
    legLeft->add(transLeg);
    //legLeft->add(knee_ankleLeft);
    legLeft->add(scaleKnee);
    legLeft->add(materialCollect->getMaterial(mARMOUR));
    legLeft->add(meshCollect->getMesh(KNEE2));

    //Leg Right
    NodeSceneGraph * legRight=new NodeSceneGraph();
    legRight->add(moveLegRight);
    legRight->add(transLeg);
    //legRight->add(knee_ankleRight);
    legRight->add(scaleKnee);
    legRight->add(materialCollect->getMaterial(mARMOUR));
    legRight->add(meshCollect->getMesh(KNEE));

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

    Matrix4f * scaleHand=new Matrix4f();
    scaleHand->scale(0.4,0.3,0.4);

    Matrix4f * scaleHandInvert=new Matrix4f();
    scaleHandInvert->scale(1.0,1.0,-1.0);

    Matrix4f * transHand=new Matrix4f();
    transHand->translation(0.0,-1.1,-0.1);

    Matrix4f * transHandLeft=new Matrix4f();
    transHandLeft->translation(0.0,-1.1,-0.2);

    Matrix4f * rotateXHand=new Matrix4f();
    rotateXHand->rotation(30,1,0,0);

    Matrix4f * rotateYHand=new Matrix4f();
    rotateYHand->rotation(180,0,1,0);

    Matrix4f * scaleElbowCylin=new Matrix4f();
    scaleElbowCylin->scale(0.2,0.3,0.2);

    Matrix4f * scaleArmTop=new Matrix4f();
    scaleArmTop->scale(0.2,0.4,0.2);

    Matrix4f * scaleShoulder=new Matrix4f();
    scaleShoulder->scale(0.8,0.6,0.8);

    Matrix4f * rotateShoulder=new Matrix4f();
    rotateShoulder->rotation(180,0.0,1.0,0.0);

    Matrix4f * rotateXShoulder=new Matrix4f();
    rotateXShoulder->rotation(-5,1,0,0);

    Matrix4f * transElbow=new Matrix4f();
    transElbow->translation(0.0,-0.4,0.0);

    Matrix4f * transArms=new Matrix4f();
    transArms->translation(0.0,-0.5,-0.2);

    //wrist + hand
    NodeSceneGraph * handLeft=new NodeSceneGraph(true);
    handLeft->add(transHandLeft);
    //handLeft->add(scaleHandInvert);
    handLeft->add(scaleHand);
    handLeft->add(rotateYHand);
    handLeft->add(materialCollect->getMaterial(mHAND));
    handLeft->add(meshCollect->getMesh(HAND));

    NodeSceneGraph * handRight=new NodeSceneGraph();
    handRight->add(transHand);
    handRight->add(scaleHand);
    handRight->add(materialCollect->getMaterial(mHAND));
    handRight->add(meshCollect->getMesh(HAND));

    //elbow + wrist

    //Arms
    NodeSceneGraph * elbow_wristRight=new NodeSceneGraph();
    elbow_wristRight->add(transElbow);
    elbow_wristRight->add(moveElbowRight);
    elbow_wristRight->add(rotateXHand);
    elbow_wristRight->add(handRight);

    NodeSceneGraph * elbow_wristLeft=new NodeSceneGraph();
    elbow_wristLeft->add(transElbow);
    elbow_wristLeft->add(moveElbowLeft);
    elbow_wristLeft->add(rotateXHand);
    elbow_wristLeft->add(handLeft);

    //Shoulder
    NodeSceneGraph * shoulderLeft=new NodeSceneGraph();
    shoulderLeft->add(scaleShoulder);
    shoulderLeft->add(rotateXShoulder);
    shoulderLeft->add(materialCollect->getMaterial(mARMOUR));
    shoulderLeft->add(meshCollect->getMesh(TOPARM));

    NodeSceneGraph * shoulderRight=new NodeSceneGraph();
    shoulderRight->add(rotateXShoulder);
    shoulderRight->add(rotateShoulder);
    shoulderRight->add(scaleShoulder);
    shoulderRight->add(materialCollect->getMaterial(mARMOUR));
    shoulderRight->add(meshCollect->getMesh(TOPARM));

    //Arm left
    NodeSceneGraph * ArmLeft=new NodeSceneGraph();
    ArmLeft->add(moveArmLeft);
    ArmLeft->add(transArms);
    //ArmLeft->add(elbow_wristLeft);
    ArmLeft->add(shoulderLeft);


    //Arm Right
    NodeSceneGraph * ArmRight=new NodeSceneGraph();
    ArmRight->add(moveArmRight);
    ArmRight->add(transArms);
    //ArmRight->add(elbow_wristRight);
    ArmRight->add(shoulderRight);

    //////////////////////////////////////////////////////
    /////         Construction of the hero           /////
    //////////////////////////////////////////////////////

    //Movement for our hero
    AvatarMove::moveAvatar= new Matrix4f();
    AvatarMove::moveAvatar->translation(1.5,2.5,-2.5);
    root->add(AvatarMove::moveAvatar);

    Matrix4f *mat=new Matrix4f();
    mat->translation(-0.4,0.0,0.0);

    Matrix4f *mat2=new Matrix4f();
    mat2->translation(0.2,1.0,0.0);

    Matrix4f * scaleHero=new Matrix4f();
    scaleHero->scale(0.5,0.5,0.5);

    Matrix4f *trasn2Arms=new Matrix4f();
    trasn2Arms->translation(-1.2,0.0,0.0);

    Matrix4f *trasn2Arms2=new Matrix4f();
    trasn2Arms2->translation(0.6,0.55,0.18);

    Matrix4f *scaleHead=new Matrix4f();
    scaleHead->scale(1.0,1.0,1.0);

    Matrix4f *transHead=new Matrix4f();
    transHead->translation(0.0,2.5,0.0);

    Matrix4f *transChest=new Matrix4f();
    transChest->translation(0.0,1.1,0.0);

    NodeSceneGraph * chestNode=new NodeSceneGraph();
    chestNode->add(materialCollect->getMaterial(mARMOUR));
    chestNode->add(meshCollect->getMesh(CHEST));

    NodeSceneGraph * headNode=new NodeSceneGraph();
    headNode->add(transHead);
    headNode->add(materialCollect->getMaterial(mARMOUR));
    headNode->add(meshCollect->getMesh(HEAD));

    NodeSceneGraph * chest_ArmsNode=new NodeSceneGraph();
    chest_ArmsNode->add(transChest);
    chest_ArmsNode->add(chestNode);
    chest_ArmsNode->add(trasn2Arms2);
    chest_ArmsNode->add(ArmLeft);
    chest_ArmsNode->add(trasn2Arms);
    chest_ArmsNode->add(ArmRight);

    root->add(scaleHero);
    root->add(materialCollect->getMaterial(mWOOD));
    root->add(headNode);
    root->add(chest_ArmsNode);
    root->add(mat2);
    root->add(materialCollect->getMaterial(mWOOD));
    root->add(legLeft);
    root->add(mat);
    root->add(legRight);
    currentTime=SDL_GetTicks();
    jumpDelay=currentTime;
    hitDelay=currentTime;

    //Init all animations of our hero
    initAnimation();
}

//**********************************************************************//

Hero::~Hero()
{
    for(vector<Text *>::iterator it = texts.begin() ; it != texts.end(); ++it){
        delete (*it);
    }

    for(vector<Matrix4f *>::iterator it = moveMatrix.begin() ; it != moveMatrix.end(); ++it){
        delete (*it);
    }

    for(vector<Sound *>::iterator it = heroSound.begin() ; it != heroSound.end(); ++it){
        delete (*it);
    }
}

//**********************************************************************//

void Hero::visualization(Context & cv){
    root->visualization(cv);

    for(unsigned i=0;i<texts.size();i++)
        if(activatedTexts[i])
            texts[i]->visualization(cv);
}

//**********************************************************************//

void Hero::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap){
    bool hasMove=true;

    avatarDirection heroDir;
    vec3f moveHero,velocityHero,accelerationHero;
    currentMap=rootMap;

    if(time-currentTime>200)
        currentTime=time-50;

    //Case-> Push Left bottom
    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)] && !currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)] &&
    !currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)]){
        if(!isJumping && !isFalling){
            moveHero.x=-3.0;moveHero.z=0.0;
        }
        else{
            moveHero.x=-5.0;moveHero.z=0.0;
        }
        heroDir=LEFTWARD;
    }
    //Case-> Push Right bottom
    else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)]&& !currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)] &&
    !currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)]){
        if(!isJumping && !isFalling){
            moveHero.x=3.0;moveHero.z=0.0;
        }
        else{
            moveHero.x=5.0;moveHero.z=0.0;
        }
        heroDir=RIGHTWARD;
    }
    //Case-> Push Up bottom
    else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)]&& !currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)] &&
    !currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)]){
        if(!isJumping && !isFalling){
            moveHero.x=0.0;moveHero.z=-3.0;
        }
        else{
            moveHero.x=0.0;moveHero.z=-5.0;
        }
        heroDir=BACKWARD;
    }
    //Case-> Push Down bottom
    else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)]&& !currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)] &&
    !currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)]){
        if(!isJumping && !isFalling){
            moveHero.x=0.0;moveHero.z=3.0;
        }
        else{
            moveHero.x=0.0;moveHero.z=5.0;
        }
        heroDir=FORWARD;
    }
    //Case-> Push Dowm-Left bottoms
    else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)] && currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)] ){
        if(!isJumping && !isFalling){
            moveHero.x=-2.0;moveHero.z=2.0;
        }
        else{
            moveHero.x=-4.0;moveHero.z=4.0;
        }
        heroDir=FOR_LEFTWARD;
    }
    //Case-> Push Dowm-Right bottoms
    else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)] && currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)] ){
        if(!isJumping && !isFalling){
            moveHero.x=2.0;moveHero.z=2.0;
        }
        else{
            moveHero.x=4.0;moveHero.z=4.0;
        }
        heroDir=FOR_RIGHTWARD;
    }
    //Case-> Push Up-Left bottoms
    else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)] && currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)]){
        if(!isJumping && !isFalling){
            moveHero.x=-2.0;moveHero.z=-2.0;
        }
        else{
            moveHero.x=-4.0;moveHero.z=-4.0;
        }
        heroDir=BACK_LEFTWARD;
    }
    //Case-> Push Up-Right bottoms
    else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)] && currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)] ){
        if(!isJumping && !isFalling){
            moveHero.x=2.0;moveHero.z=-2.0;
        }
        else{
            moveHero.x=4.0;moveHero.z=-4.0;
        }
        heroDir=BACK_RIGHTWARD;
    }
    else{ //Case-> If not move
        hasMove=false;
        if(!isJumping && !isFalling){
            noMove();
        }
        if(heroSound[0]->isPlaying())
            heroSound[0]->stop();
    }

    //Case-> Push Scape bottom to jump
    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_s)] && !isJumping && !isFalling && jumpDelay<(time-600)){
        activeJump(vec3f(velocityHero.x,15.0,velocityHero.y),vec3f(accelerationHero.x,5.0,accelerationHero.z));
        jumpDelay=time;
    }
    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_d)]){ //If hero is hitting
        isHitting=true;
        hitDelay=time;
    }
    else { // If hero is not hitting -> resetAnimation
        if(hitDelay<(time-1000)){
            animationHit.resetState();
            for(unsigned i=0;i<moveMatrix.size();i++)
                moveMatrix[i]->identity();
            hitDelay=time;
            isHitting=false;
        }
    }

    //Move the body
    if(hasMove){
        moveBody(moveHero,heroDir);
        heroSound[0]->play();
    }
    //If the jump is activate
    if(isJumping){
        jump(time);
        if(heroSound[0]->isPlaying())
            heroSound[0]->stop();
    }

    //If the jump is not activate
    else gravity(time);

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
    }

    for(unsigned i=0;i<texts.size();i++)
        if(activatedTexts[i])
            texts[i]->setPosition(vec3f(position.x,position.y+1.5f,position.z));

    //If hero does not take a coin in the last 300 ms
    if(coinDelay<time-700)
        activateDialog(false,2);
    currentTime+=(time-currentTime);
}

//**********************************************************************//

void Hero::enableSound(bool value){
    for(int i=0;i<heroSound.size();i++)
    if(value)
        heroSound[i]->resume();
    else{
        heroSound[i]->pause();
    }
}

//**********************************************************************//

void Hero::setDialog(string message,int index){
    texts[index]->setPosition(vec3f(position.x,position.y+1.5f,position.z));
    texts[index]->setMessage(message);
    texts[index]->init();
}

//**********************************************************************//

void Hero::activateDialog(bool value,int index){
    activatedTexts[index]=value;
}

//**********************************************************************//

void Hero::noMove(){
    animation.resetState();
    for(unsigned i=0;i<moveMatrix.size();i++)
        moveMatrix[i]->identity();
    isMoving=false;
}

//**********************************************************************//

bool Hero::isHit(){
    bool result=false;
    if(animationHit.getScriptState(4)==3 || animationHit.getScriptState(5)==1)
        result=true;

    return result;
}

//**********************************************************************//

 float Hero::getLife(){
    return life;
 }

 //**********************************************************************//

 int Hero::getCoin(){
    return currentCoin;
 }

 //**********************************************************************//

 void Hero::addCoin(int value){
    currentCoin+=value;
    int lastValue;
    coinDelay=currentTime;
    stringstream convert;

    if(activatedTexts[2]){ //if is activate the text ->//Join values
        string currentValue=texts[2]->getMessage();
        lastValue=atoi(currentValue.c_str());
        value+=lastValue;
    }

    convert << value;
    setDialog("+"+convert.str(),2);

    activateDialog(true,2);
 }

//**********************************************************************//
//                              PRIVATE                                 //
//**********************************************************************//

 void Hero::initAnimation(){
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
    OscillateRotation * oscillateKnee=new OscillateRotation(false,0,-40,1,150,vec3f(1,0,0),2);
    oscillateLeg=new OscillateRotation(true,40,0,1,150,vec3f(1,0,0),2);
    oscillateLegSecond=new OscillateRotation(false,0,-20,1,50,vec3f(1,0,0),1);
    notMove=new MatrixStatic();

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
