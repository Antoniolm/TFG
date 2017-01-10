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
    isImpacted=false;
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
    legLeft->add(materialCollect->getMaterial(mARMOUR));
    legLeft->add(meshCollect->getMesh(KNEE2));

    //Leg Right
    NodeSceneGraph * legRight=new NodeSceneGraph();
    legRight->add(moveLegRight);
    legRight->add(transLeg);
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
    transArms->translation(0.0,-0.5,-0.2);

    Matrix4f * tranSword=new Matrix4f();
    tranSword->translation(0.05,-0.1,0.68);

    Matrix4f * tranShield=new Matrix4f();
    tranShield->translation(-0.275,0.0,0.0);

    //Arms
    NodeSceneGraph * handRight=new NodeSceneGraph();
    handRight->add(transElbow);
    handRight->add(moveElbowRight);
    handRight->add(transHand);
    handRight->add(materialCollect->getMaterial(mARMOUR));
    handRight->add(meshCollect->getMesh(HAND));
    handRight->add(tranSword);
    handRight->add(materialCollect->getMaterial(mSWORD));
    handRight->add(meshCollect->getMesh(SWORD));

    NodeSceneGraph * handLeft=new NodeSceneGraph();
    handLeft->add(transElbow);
    handLeft->add(moveElbowLeft);
    handLeft->add(transHandLeft);
    //handLeft->add(scaleHandInvert);
    handLeft->add(rotateYHand);
    handLeft->add(materialCollect->getMaterial(mARMOUR));
    handLeft->add(meshCollect->getMesh(HANDS));
    handLeft->add(tranShield);
    handLeft->add(materialCollect->getMaterial(mSHIELD));
    handLeft->add(meshCollect->getMesh(SHIELD));

    //Shoulder
    NodeSceneGraph * shoulderLeft=new NodeSceneGraph();
    shoulderLeft->add(materialCollect->getMaterial(mARMOUR));
    shoulderLeft->add(meshCollect->getMesh(TOPARM));

    NodeSceneGraph * shoulderRight=new NodeSceneGraph();
    shoulderRight->add(rotateShoulder);
    shoulderRight->add(materialCollect->getMaterial(mARMOUR));
    shoulderRight->add(meshCollect->getMesh(TOPARM));

    //Arm left
    NodeSceneGraph * ArmLeft=new NodeSceneGraph();
    ArmLeft->add(transArms);
    ArmLeft->add(moveArmLeft);
    ArmLeft->add(handLeft);
    ArmLeft->add(shoulderLeft);


    //Arm Right
    NodeSceneGraph * ArmRight=new NodeSceneGraph();
    ArmRight->add(transArms);
    ArmRight->add(moveArmRight);
    ArmRight->add(handRight);
    ArmRight->add(shoulderRight);

    //////////////////////////////////////////////////////
    /////         Construction of the hero           /////
    //////////////////////////////////////////////////////

    Matrix4f * moveBodyHead=new Matrix4f();
    moveBodyHead->identity();
    moveMatrix.push_back(moveBodyHead);

    Matrix4f * moveTBodyHead=new Matrix4f();
    moveTBodyHead->identity();
    moveMatrix.push_back(moveTBodyHead);

    //Movement for our hero
    AvatarMove::moveAvatar= new Matrix4f();
    AvatarMove::moveAvatar->translation(1.5,2.5,-2.5);
    root->add(AvatarMove::moveAvatar);

    Matrix4f *transLegScene=new Matrix4f();
    transLegScene->translation(-0.5,0.0,0.0);

    Matrix4f *transLegSceneI=new Matrix4f();
    transLegSceneI->translation(0.25,0.97,0.0);

    Matrix4f * scaleHero=new Matrix4f();
    scaleHero->scale(0.5,0.5,0.5);

    Matrix4f * trasnArms=new Matrix4f();
    trasnArms->translation(-1.0,0.0,0.0);

    Matrix4f *trasnArmsI=new Matrix4f();
    trasnArmsI->translation(0.5,0.83,0.2);

    Matrix4f *transHead=new Matrix4f();
    transHead->translation(0.0,1.4,0.0);

    Matrix4f *transChest=new Matrix4f();
    transChest->translation(0.0,1.1,0.0);

    NodeSceneGraph * chestNode=new NodeSceneGraph();
    chestNode->add(materialCollect->getMaterial(mARMOUR));
    chestNode->add(meshCollect->getMesh(CHEST));

    NodeSceneGraph * headNode=new NodeSceneGraph();
    headNode->add(transHead);
    headNode->add(materialCollect->getMaterial(mARMOUR));
    headNode->add(meshCollect->getMesh(HEAD));

    NodeSceneGraph * chest_Arms_HeadNode=new NodeSceneGraph();
    chest_Arms_HeadNode->add(transChest);
    chest_Arms_HeadNode->add(moveTBodyHead);
    chest_Arms_HeadNode->add(moveBodyHead);
    chest_Arms_HeadNode->add(headNode);
    chest_Arms_HeadNode->add(chestNode);
    chest_Arms_HeadNode->add(trasnArmsI);
    chest_Arms_HeadNode->add(ArmLeft);
    chest_Arms_HeadNode->add(trasnArms);
    chest_Arms_HeadNode->add(ArmRight);

    root->add(scaleHero);
    root->add(materialCollect->getMaterial(mWOOD));
    root->add(chest_Arms_HeadNode);
    root->add(transLegSceneI);
    root->add(materialCollect->getMaterial(mWOOD));
    root->add(legLeft);
    root->add(transLegScene);
    root->add(legRight);
    currentTime=SDL_GetTicks();
    jumpDelay=currentTime;
    hitDelay=currentTime;
    dmgDelay=currentTime;

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
    if(hasMove && !isImpacted){
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

    //If the jump is activate
    if(isImpacted){
        impactMove(time);
    }


    //Update our vec4f position
    position=moveAvatar->product(vec4f());

    //Update Animation
    if(isMoving && !isFalling && !isJumping && !isHitting && !isImpacted){
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
            texts[i]->setPosition(vec3f(position.x,position.y+2.0f,position.z));

    //If hero does not take a coin in the last 300 ms
    if(coinDelay<time-700)
        activateDialog(false,2);
    currentTime+=(time-currentTime);

    //If hero does not take a coin in the last 300 ms
    if(dmgDelay<time-1200)
        activateDialog(false,3);
}

//**********************************************************************//

void Hero::enableSound(bool value){
    for(unsigned i=0;i<heroSound.size();i++)
    if(value)
        heroSound[i]->resume();
    else{
        heroSound[i]->pause();
    }
}

//**********************************************************************//

void Hero::setDialog(string message,int index){
    texts[index]->setPosition(vec3f(position.x,position.y+2.0f,position.z));
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

 void Hero::takeDamage(vec3f posAvatar,avatarDirection dirAvatar,float value){

    if(detectHit(posAvatar,dirAvatar)&& dmgDelay<(currentTime-700)){
        addLife(value);
        stringstream convert;
        if(activatedTexts[3]){ //if is activate the text ->//Join values
            int lastValue;
            string currentValue=texts[3]->getMessage();
            lastValue=atoi(currentValue.c_str());
            value+=lastValue;
        }
        dmgDelay=currentTime;

        convert << value;
        setDialog(convert.str(),3);

        activateDialog(true,3);
        if(!isImpacted)
            activeImpact(dirAvatar);
    }
 }

 void Hero::takeDamage(float value){

    addLife(value);
    stringstream convert;
    if(activatedTexts[3]){  //if is activate the text ->//Join values
        int lastValue;
        string currentValue=texts[3]->getMessage();
        lastValue=atoi(currentValue.c_str());
        value+=lastValue;
    }
    dmgDelay=currentTime;

    convert << value;
    setDialog(convert.str(),3);

    activateDialog(true,3);
 }
//**********************************************************************//
//                              PRIVATE                                 //
//**********************************************************************//

 void Hero::initAnimation(){

    //////////////////////////////////
    // Move Animation
    /////////////////////////////////

    ///////////////////
    // LEG
    //////////////////
    OscillateRotation * oscillateLeg=new OscillateRotation(true,30,0,1,150,vec3f(1,0,0),2);
    OscillateRotation * oscillateLegSecond=new OscillateRotation(false,0,-30,1,150,vec3f(1,0,0),1);
    MatrixStatic * notMove=new MatrixStatic();

    //Movement to the first leg
    MatrixScript * LegScriptLeft=new MatrixScript();
    LegScriptLeft->add(0.3,oscillateLeg);
    LegScriptLeft->add(0.3,oscillateLegSecond);


    //Movement to the second leg
    MatrixScript * LegScriptRight=new MatrixScript();
    LegScriptRight->add(0.3,oscillateLegSecond);
    LegScriptRight->add(0.3,oscillateLeg);

    //Add the script to our animation
    animation.add(LegScriptRight);
    animation.add(LegScriptLeft);

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
    animation.add(ElbowScriptRight);
    animation.add(ElbowScriptLeft);
    animation.add(ArmScriptRight);
    animation.add(ArmScriptLeft);

    ///////////////////
    // BODY
    //////////////////
    //Matrix4fDinamic
    OscillateRotation * oscillateBody=new OscillateRotation(true,5,0,1,25,vec3f(0,1,0),1);
    OscillateRotation * oscillateBodySecond=new OscillateRotation(false,0,-5,1,25,vec3f(0,1,0),1);
    LinearMovement * transBody=new LinearMovement(vec3f(0,2.0,0));
    LinearMovement * transBodySecond=new LinearMovement(vec3f(0,-2.0,0));

    //Movement to the first arm
    MatrixScript * bodyScript=new MatrixScript();
    bodyScript->add(0.3,oscillateBody);
    bodyScript->add(0.3,oscillateBodySecond);

    //Movement to the first arm
    MatrixScript * bodyTScript=new MatrixScript();
    bodyTScript->add(0.15,transBody);
    bodyTScript->add(0.15,transBodySecond);
    bodyTScript->add(0.15,transBody);
    bodyTScript->add(0.15,transBodySecond);

    animation.add(bodyScript);
    animation.add(bodyTScript);

    /////////////////////////////////
    // ANIMATION HIT
    /////////////////////////////////
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

    ///////////////////
    // BODY
    //////////////////
    //Movement to the first arm
    bodyScript=new MatrixScript();
    bodyScript->add(0.3,notMove);

    bodyTScript=new MatrixScript();
    bodyTScript->add(0.3,notMove);

    animationHit.add(bodyScript);
    animationHit.add(bodyTScript);
 }
