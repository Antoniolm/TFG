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
#include "weapon.h"
#include "projectile.h"

Hero::Hero(vec3f aPos)
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
    isShielded=false;
    life=150;
    position=vec4f(aPos.x,aPos.y,aPos.z,1.0);
    currentCoin=0;

    MeshCollection * meshCollect =MeshCollection::getInstance();
    MaterialCollection * materialCollect =MaterialCollection::getInstance();
    SoundCollection * soundCollect =SoundCollection::getInstance();


    //Print a message for check
    cout<< "< Game is loading our hero >"<< endl;

    //////////////////////////////////////////////////////
    /////           Initialize weapons               /////
    //////////////////////////////////////////////////////
    currentWeapon=new Weapon(vec3f(0.05,-0.1,0.68),MELEE,-25,SWORD,mSWORD);
    meleeWeapon=new Weapon(vec3f(0.05,-0.1,0.68),MELEE,-25,SWORD,mSWORD);
    rangedWeapon=new Weapon(vec3f(0.0,-0.4,0.0),RANGED,-20,CBOW,mARCHENEMY);


    //////////////////////////////////////////////////////
    /////              All the sounds                /////
    //////////////////////////////////////////////////////
    Sound * sound=new Sound("sounds/walking.wav",1,40,3,-1);
    heroSound.push_back(sound);
    sound=new Sound("sounds/heroHit.wav",1,20,5,0);
    heroSound.push_back(sound);
    sound=new Sound("sounds/shield.wav",1,40,6,0);
    heroSound.push_back(sound);
    heroSound.push_back(soundCollect->getSound(SHOOT));
    heroSound.push_back(soundCollect->getSound(sSWORD));


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
    legLeft->add(materialCollect->getMaterial(mHERO));
    legLeft->add(meshCollect->getMesh(KNEE2));

    //Leg Right
    NodeSceneGraph * legRight=new NodeSceneGraph();
    legRight->add(moveLegRight);
    legRight->add(transLeg);
    legRight->add(materialCollect->getMaterial(mHERO));
    legRight->add(meshCollect->getMesh(KNEE));

    //////////////////////////////////////////////////////
    /////                  Arms                      /////
    //////////////////////////////////////////////////////


    //Create a new Movement
    Matrix4f * moveElbowRight=new Matrix4f();
    moveElbowRight->identity();
    moveMatrix.push_back(moveElbowRight);

    Matrix4f * moveElbowTRight=new Matrix4f();
    moveElbowTRight->identity();
    moveMatrix.push_back(moveElbowTRight);

    Matrix4f * moveElbowLeft=new Matrix4f();
    moveElbowLeft->identity();
    moveMatrix.push_back(moveElbowLeft);

    Matrix4f * moveElbowTLeft=new Matrix4f();
    moveElbowTLeft->identity();
    moveMatrix.push_back(moveElbowTLeft);

    Matrix4f * moveArmRight=new Matrix4f();
    moveArmRight->identity();
    moveMatrix.push_back(moveArmRight);

    Matrix4f * moveArmLeft=new Matrix4f();
    moveArmLeft->identity();
    moveMatrix.push_back(moveArmLeft);

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
    handRight->add(moveElbowTRight);
    handRight->add(transHand);
    handRight->add(meshCollect->getMesh(HAND));
    handRight->add(currentWeapon);

    NodeSceneGraph * handLeft=new NodeSceneGraph();
    handLeft->add(transElbow);
    handLeft->add(moveElbowLeft);
    handLeft->add(moveElbowTLeft);
    handLeft->add(transHandLeft);
    //handLeft->add(scaleHandInvert);
    handLeft->add(rotateYHand);
    handLeft->add(meshCollect->getMesh(HANDS));
    handLeft->add(tranShield);
    handLeft->add(materialCollect->getMaterial(mSHIELD));
    handLeft->add(meshCollect->getMesh(SHIELD));

    //Shoulder
    NodeSceneGraph * shoulderLeft=new NodeSceneGraph();
    shoulderLeft->add(meshCollect->getMesh(TOPARM));

    NodeSceneGraph * shoulderRight=new NodeSceneGraph();
    shoulderRight->add(rotateShoulder);
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
    moveAvatar= new Matrix4f();
    moveAvatar->translation(position.x,position.y,position.z);
    root->add(moveAvatar);

    Matrix4f *transLegScene=new Matrix4f();
    transLegScene->translation(-0.5,0.0,0.0);

    Matrix4f *transLegSceneI=new Matrix4f();
    transLegSceneI->translation(0.25,0.0,0.0);

    Matrix4f * scaleHero=new Matrix4f();
    scaleHero->scale(0.5,0.5,0.5);

    Matrix4f * trasnArms=new Matrix4f();
    trasnArms->translation(-1.0,0.0,0.0);

    Matrix4f *trasnArmsI=new Matrix4f();
    trasnArmsI->translation(0.5,0.83,0.2);

    Matrix4f *transHead=new Matrix4f();
    transHead->translation(0.0,1.4,0.0);

    Matrix4f *transChest=new Matrix4f();
    transChest->translation(0.0,0.1,0.0);

    NodeSceneGraph * headNode=new NodeSceneGraph();
    headNode->add(transHead);
    headNode->add(meshCollect->getMesh(HEAD));

    NodeSceneGraph * chest_Arms_HeadNode=new NodeSceneGraph();
    chest_Arms_HeadNode->add(transChest);
    chest_Arms_HeadNode->add(moveTBodyHead);
    chest_Arms_HeadNode->add(moveBodyHead);
    chest_Arms_HeadNode->add(headNode);
    chest_Arms_HeadNode->add(meshCollect->getMesh(CHEST));
    chest_Arms_HeadNode->add(trasnArmsI);
    chest_Arms_HeadNode->add(ArmLeft);
    chest_Arms_HeadNode->add(trasnArms);
    chest_Arms_HeadNode->add(ArmRight);

    root->add(scaleHero);
    root->add(materialCollect->getMaterial(mHERO));
    root->add(chest_Arms_HeadNode);
    root->add(transLegSceneI);
    root->add(legLeft);
    root->add(transLegScene);
    root->add(legRight);
    currentTime=SDL_GetTicks();
    jumpDelay=currentTime;
    hitDelay=currentTime;
    dmgDelay=currentTime;
    shieldDelay=currentTime;
    swapDelay=currentTime;
    shootDelay=currentTime;

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

    for(vector<Projectile *>::iterator it = projectiles.begin() ; it != projectiles.end(); ++it){
        delete (*it);
    }

}

//**********************************************************************//

void Hero::visualization(Context & cv){
    root->visualization(cv);

    ////////////////////////////
    //DRAW texts
    ////////////////////////////
    for(unsigned i=0;i<texts.size();i++)
        if(activatedTexts[i])
            texts[i]->visualization(cv);

    ////////////////////////////
    //DRAW PROJECTILES
    ////////////////////////////
    vector<Projectile *>::iterator it;
    for(it=projectiles.begin();it!=projectiles.end();it++){
        (*it)->visualization(cv);
    }
}

//**********************************************************************//

void Hero::updateState(float time,ControllerManager * controller,RootMap * rootMap){
    bool hasMove=true;

    avatarDirection heroDir=direction;
    vec3f moveHero,velocityHero,accelerationHero;
    currentMap=rootMap;

    if(time-currentTime>200)
        currentTime=time-50;

    //Case-> Push Left bottom
    if(controller->checkButton(cLEFT) && !controller->checkButton(cDOWN) && !controller->checkButton(cUP)){
        if(!isJumping && !isFalling){
            moveHero.x=-3.0;moveHero.z=0.0;
        }
        else{
            moveHero.x=-5.0;moveHero.z=0.0;
        }
        heroDir=LEFTWARD;
    }
    //Case-> Push Right bottom
    else if(controller->checkButton(cRIGHT) && !controller->checkButton(cDOWN) && !controller->checkButton(cUP)){
        if(!isJumping && !isFalling){
            moveHero.x=3.0;moveHero.z=0.0;
        }
        else{
            moveHero.x=5.0;moveHero.z=0.0;
        }
        heroDir=RIGHTWARD;
    }
    //Case-> Push Up bottom
    else if(controller->checkButton(cUP) && !controller->checkButton(cLEFT) && !controller->checkButton(cRIGHT)){
        if(!isJumping && !isFalling){
            moveHero.x=0.0;moveHero.z=-3.0;
        }
        else{
            moveHero.x=0.0;moveHero.z=-5.0;
        }
        heroDir=BACKWARD;
    }
    //Case-> Push Down bottom
    else if(controller->checkButton(cDOWN) && !controller->checkButton(cLEFT) && !controller->checkButton(cRIGHT)){
        if(!isJumping && !isFalling){
            moveHero.x=0.0;moveHero.z=3.0;
        }
        else{
            moveHero.x=0.0;moveHero.z=5.0;
        }
        heroDir=FORWARD;
    }
    //Case-> Push Dowm-Left bottoms
    else if(controller->checkButton(cDOWN) && controller->checkButton(cLEFT) ){
        if(!isJumping && !isFalling){
            moveHero.x=-2.0;moveHero.z=2.0;
        }
        else{
            moveHero.x=-4.0;moveHero.z=4.0;
        }
        heroDir=FOR_LEFTWARD;
    }
    //Case-> Push Dowm-Right bottoms
    else if(controller->checkButton(cDOWN) && controller->checkButton(cRIGHT) ){
        if(!isJumping && !isFalling){
            moveHero.x=2.0;moveHero.z=2.0;
        }
        else{
            moveHero.x=4.0;moveHero.z=4.0;
        }
        heroDir=FOR_RIGHTWARD;
    }
    //Case-> Push Up-Left bottoms
    else if(controller->checkButton(cUP) && controller->checkButton(cLEFT)){
        if(!isJumping && !isFalling){
            moveHero.x=-2.0;moveHero.z=-2.0;
        }
        else{
            moveHero.x=-4.0;moveHero.z=-4.0;
        }
        heroDir=BACK_LEFTWARD;
    }
    //Case-> Push Up-Right bottoms
    else if(controller->checkButton(cUP) && controller->checkButton(cRIGHT) ){
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

    //Case-> Push S bottom to jump
    if(controller->checkButton(cJUMP) && !isJumping && !isFalling && !isImpacted && !isShielded && jumpDelay<(time-600) ){
        activeJump(vec3f(velocityHero.x,15.0,velocityHero.y),vec3f(accelerationHero.x,5.0,accelerationHero.z));
        jumpDelay=time;
    }

    //Case-> Push L bottom to hit
    if(controller->checkButton(cATTACK) && !isShielded){ //If hero is hitting
        if(!isHitting){
            animations.resetAnimation(1);
            animations.resetAnimation(5);
            //heroSound[4]->stop();
            //heroSound[4]->play();
        }
        isHitting=true;
        hitDelay=time;
    }
    else { // If hero is not hitting -> resetAnimation
        if(hitDelay<(time-250) && currentWeapon->getType()==MELEE){
            hitDelay=time;
            isHitting=false;
        }
        else if(hitDelay<(time-750) && currentWeapon->getType()==RANGED){
            hitDelay=time;
            isHitting=false;
        }
    }

    //Case-> Push W bottom to shield
    if(controller->checkButton(cSHIELD) && !isHitting){ //If hero is shielding
        isShielded=true;
        animations.activate(2); //Activate animation
    }
    else { //if not
        isShielded=false;
    }

    //Case-> Push Q bottom to swap weapon
    if(controller->checkButton(cSWAPWEAPON) && !isHitting && swapDelay<(time-500) ){ //If hero is shielding
        switch(currentWeapon->getType()){
            case MELEE:
                currentWeapon->setWeapon((*rangedWeapon));
            break;
            case RANGED:
                currentWeapon->setWeapon((*meleeWeapon));
            break;
        }
        swapDelay=time;
    }


    //Move the body
    if(hasMove && !isImpacted && !isHitting){
        avatarDirection lastDir=direction;
        moveBody(moveHero,heroDir);
        heroSound[0]->play();
        if(isShielded)
            changeDirection(lastDir);
    }
    //If the jump is activate
    if(isJumping){
        jump(time);
        animations.activate(3);
        if(heroSound[0]->isPlaying())
            heroSound[0]->stop();
    }
    //If the jump is not activate
    else {
        ObjectScene * object=gravity(time);
        if(!isShielded)
            animations.activate(4);
        if(object!=0 && object->getDamage()!=0.0 && dmgDelay<(time-200)){ //If the object do damage
            takeDamage(object->getDamage());
            dmgDelay=time;
        }
    }

    //If the jump is activate
    if(isImpacted){
        impactMove(time);
    }

    //Check enemies
    if(isHitting){
        vector<Enemy *> enemies=rootMap->getEnemyList()->getEnemies();
        vec3f posEnemy;float distance;
        switch(currentWeapon->getType()){
            case MELEE: //If is the sword
                animations.activate(1);
                for(unsigned i=0;i<enemies.size();i++){ //Loop for all the enemies
                    posEnemy=enemies[i]->getPosition(); //Calculate the distance
                    distance=sqrt(pow(position.x-posEnemy.x,2.0)+pow(position.z-posEnemy.z,2.0));

                    if(distance<=1.0 && (position.y>posEnemy.y-1 && position.y<posEnemy.y+1)){//If is near
                        enemies[i]->takeDamage(position,direction,currentWeapon->getDamage(),enemies); //Hit enemy
                    }
                }
            break;
            case RANGED: //if is the crossbow
                animations.activate(5);
                ScriptLMD * animationHit=animations.getAnimation();
                if(animationHit->getScriptState(6)==1 && shootDelay<(time-700)){
                    shootDelay=time;
                    createProjectile();
                    heroSound[3]->stop();
                    heroSound[3]->play();
                }
            break;
        }
    }


    //Update our vec4f position
    position=moveAvatar->product(vec4f());

    ////////////////////////////
    //UPDATE ANIMATION
    ////////////////////////////
    if(isMoving && !isFalling && !isJumping && !isHit() && !isImpacted && !isShielded){
        animations.activate(0);
    }
    if(!isMoving && !isFalling && !isJumping && !isHitting && !isImpacted && !isShielded){
        animations.activate(-1);
    }
    if(isHitting){
        switch(currentWeapon->getType()){
            case MELEE: animations.activate(1);
            break;
            case RANGED: animations.activate(5);
            break;
        }
    }

    if(animations.getState()!=-1){
        animations.update(time-currentTime);
        ScriptLMD * animation=animations.getAnimation();
        for(unsigned i=0;i<moveMatrix.size();i++)
                moveMatrix[i]->setMatrix(animation->readMatrix(i).getMatrix());
    }
    else noMove();

    ////////////////////////////
    //UPDATE TEXT
    ////////////////////////////
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

    ////////////////////////////
    //UPDATE PROJECTILES
    ////////////////////////////
    vector<Projectile *>::iterator it=projectiles.begin();

    while(it!=projectiles.end()){

        (*it)->updateState(time,controller,rootMap);
        if(!(*it)->isLive()){
            it=projectiles.erase(it);
        }
        else
            it++;
    }
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
    animations.resetAnimation(0);
    for(unsigned i=0;i<moveMatrix.size();i++)
        moveMatrix[i]->identity();
    isMoving=false;
    animations.activate(-1);
}

//**********************************************************************//

bool Hero::isHit(){
    return isHitting;
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
     //check if the hero is shielding
     bool canShield=false;
    if(isShielded && detectShield(posAvatar,direction)) canShield=true;

    //check Distance
    float distance=sqrt(pow(position.x-posAvatar.x,2.0)+pow(position.z-posAvatar.z,2.0));

    if(detectHit(posAvatar,dirAvatar)&& dmgDelay<(currentTime-700) && !canShield && distance<1.0){
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
        if(!isImpacted) //if hero is not impacted in this moment
            activeImpact(dirAvatar);
        heroSound[1]->stop();
        heroSound[1]->play();
    }
    if(detectHit(posAvatar,dirAvatar) && shieldDelay<(currentTime-700) && canShield && distance<1.0){
        heroSound[2]->stop();
        heroSound[2]->play();
        shieldDelay=currentTime;
    }
 }

 //**********************************************************************//

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

    heroSound[1]->stop();
    heroSound[1]->play();
 }

//**********************************************************************//
//                              PRIVATE                                 //
//**********************************************************************//

 void Hero::initAnimation(){

    //////////////////////////////////
    // Move Animation
    /////////////////////////////////
    ScriptLMD * animation=new ScriptLMD();
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
    MatrixScript * ElbowScriptTLeft=new MatrixScript();
    ElbowScriptLeft->add(0.5,notMove);
    ElbowScriptLeft->add(0.5,notMove);
    ArmScriptLeft->add(0.5,oscillateShoulder);
    ArmScriptLeft->add(0.5,notMove);
    ElbowScriptTLeft->add(0.5,notMove);

    //Movement to the second arm
    MatrixScript * ElbowScriptRight=new MatrixScript();
    MatrixScript * ArmScriptRight=new MatrixScript();
    MatrixScript * ElbowScriptTRight=new MatrixScript();
    ElbowScriptRight->add(0.5,notMove);
    ElbowScriptRight->add(0.5,notMove);
    ArmScriptRight->add(0.5,notMove);
    ArmScriptRight->add(0.5,oscillateShoulder);
    ElbowScriptTRight->add(0.5,notMove);


    //Add the script to our animation
    animation->add(ElbowScriptRight);
    animation->add(ElbowScriptTRight);
    animation->add(ElbowScriptLeft);
    animation->add(ElbowScriptTLeft);
    animation->add(ArmScriptRight);
    animation->add(ArmScriptLeft);


    ///////////////////
    // BODY
    //////////////////
    //Matrix4fDinamic
    OscillateRotation * oscillateBody=new OscillateRotation(true,5,0,1,25,vec3f(0,1,0),1);
    OscillateRotation * oscillateBodySecond=new OscillateRotation(false,0,-5,1,25,vec3f(0,1,0),1);

    Matrix4f * transBody=new Matrix4f();
    transBody->translation(0,0.05,0);
    MatrixStatic * staticBody=new MatrixStatic(*transBody);

    Matrix4f * transBodySecond=new Matrix4f();
    transBodySecond->translation(0,-0.05,0);
    MatrixStatic * staticBodySecond=new MatrixStatic(*transBodySecond);

    //Movement to the first arm
    MatrixScript * bodyScript=new MatrixScript();
    bodyScript->add(0.3,oscillateBody);
    bodyScript->add(0.3,oscillateBodySecond);

    //Movement to the first arm
    MatrixScript * bodyTScript=new MatrixScript();
    bodyTScript->add(0.15,staticBody);
    bodyTScript->add(0.15,staticBodySecond);
    bodyTScript->add(0.15,staticBody);
    bodyTScript->add(0.15,staticBodySecond);

    animation->add(bodyScript);
    animation->add(bodyTScript);

    animations.add(animation);

    /////////////////////////////////
    // ANIMATION HIT
    /////////////////////////////////
    animation=new ScriptLMD();
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
    animation->add(LegScriptRight);
    animation->add(LegScriptLeft);

    //Matrix4fDinamic
    ///////////////////
    // ARM
    //////////////////
    OscillateRotation * shoulderCharge=new OscillateRotation(false,140,0,140,500,vec3f(1.0,0.0,0),1);
    //OscillateRotation * shoulderCharge2=new OscillateRotation(false,140,0,140,500,vec3f(0.0,1.0,0),1);
    OscillateRotation * oscillateElbow=new OscillateRotation(true,60,0,1,250,vec3f(1.0,0.0,0),1);
    Matrix4f * rotateShoulder=new Matrix4f();
    rotateShoulder->rotation(90,1.0,0.0,0.0);

    Matrix4f * rotateElbow=new Matrix4f();
    rotateElbow->rotation(90,1.0,0.0,0.0);

    Matrix4f * transElbow=new Matrix4f();
    transElbow->translation(0.0,-0.5,0.0);

    rotateElbow->product(transElbow->getMatrix());


    MatrixStatic *staticShoulder=new MatrixStatic(*rotateShoulder);
    MatrixStatic *staticElbow=new MatrixStatic(*rotateElbow);
    MatrixStatic *staticTransElbow=new MatrixStatic(*rotateElbow);

    //Movement to the first arm
    ElbowScriptLeft=new MatrixScript();
    ArmScriptLeft=new MatrixScript();
    ElbowScriptLeft->add(0.5,notMove);
    ElbowScriptLeft->add(0.5,notMove);
    ArmScriptLeft->add(0.5,notMove);
    ArmScriptLeft->add(0.5,notMove);

    //Movement to the second arm
    ElbowScriptRight=new MatrixScript();
    ArmScriptRight=new MatrixScript();
    ElbowScriptTRight=new MatrixScript();

    ElbowScriptRight->add(0.65,notMove);
    //ElbowScriptRight->add(0.25,shoulderCharge2);
    //ElbowScriptRight->add(0.4,notMove);

    ElbowScriptTRight->add(0.65,notMove);
    //ElbowScriptTRight->add(0.25,staticTransElbow);
    //ElbowScriptTRight->add(0.4,notMove);

    ArmScriptRight->add(0.25,shoulderCharge);
    ArmScriptRight->add(0.25,notMove);
    //ArmScriptRight->add(0.30,staticShoulder);
    //ArmScriptRight->add(0.4,notMove);

    //Add the script to our animation
    animation->add(ElbowScriptRight);  //2
    animation->add(ElbowScriptTRight); //3
    animation->add(ElbowScriptLeft);   //4
    animation->add(ElbowScriptTLeft);  //5
    animation->add(ArmScriptRight);    //6
    animation->add(ArmScriptLeft);     //7


    ///////////////////
    // BODY
    //////////////////
    //Movement to the first arm
    bodyScript=new MatrixScript();
    bodyScript->add(0.3,notMove);

    bodyTScript=new MatrixScript();
    bodyTScript->add(0.3,notMove);

    animation->add(bodyScript);
    animation->add(bodyTScript);

    animations.add(animation);

    /////////////////////////////////
    // ANIMATION SHIELD
    /////////////////////////////////
    animation=new ScriptLMD();
    ///////////////////
    // LEG
    //////////////////
    oscillateLeg=new OscillateRotation(true,30,0,1,150,vec3f(1,0,0),2);
    oscillateLegSecond=new OscillateRotation(false,0,-30,1,150,vec3f(1,0,0),1);

    //Movement to the first leg
    LegScriptLeft=new MatrixScript();
    LegScriptLeft->add(0.3,oscillateLeg);
    LegScriptLeft->add(0.3,oscillateLegSecond);


    //Movement to the second leg
    LegScriptRight=new MatrixScript();
    LegScriptRight->add(0.3,oscillateLegSecond);
    LegScriptRight->add(0.3,oscillateLeg);

    //Add the script to our animation
    animation->add(LegScriptRight);
    animation->add(LegScriptLeft);

    ///////////////////
    // ARM
    //////////////////
    //Matrix4fDinamic
    shoulderCharge=new OscillateRotation(false,0,-40,1,250,vec3f(1.0,0.0,0),1);
    oscillateElbow=new OscillateRotation(true,60,0,1,250,vec3f(1.0,0.0,0),1);
    rotateShoulder=new Matrix4f();
    rotateShoulder->rotation(90,1.0,0.0,0.0);

    rotateElbow=new Matrix4f();
    rotateElbow->rotation(60,0.0,0.0,1.0);

    Matrix4f * TransElbow=new Matrix4f();
    TransElbow->translation(-0.5,-0.3,-0.3);

    staticShoulder=new MatrixStatic(*rotateShoulder);
    staticElbow=new MatrixStatic(*rotateElbow);
    MatrixStatic * staticTrans=new MatrixStatic(*TransElbow);

    //Movement to the first arm
    ElbowScriptLeft=new MatrixScript();
    ArmScriptLeft=new MatrixScript();
    ElbowScriptTLeft=new MatrixScript();

    ElbowScriptLeft->add(0.5,staticElbow);
    ArmScriptLeft->add(0.5,staticShoulder);
    ElbowScriptTLeft->add(0.5,staticTrans);

    //Movement to the second arm
    ElbowScriptRight=new MatrixScript();
    ArmScriptRight=new MatrixScript();
    ElbowScriptRight->add(0.5,notMove);
    ArmScriptRight->add(0.5,notMove);


    //Add the script to our animation
    animation->add(ElbowScriptRight);  //4
    animation->add(ElbowScriptTRight); //7
    animation->add(ElbowScriptLeft);   //5
    animation->add(ElbowScriptTLeft);  //7
    animation->add(ArmScriptRight);
    animation->add(ArmScriptLeft);     //7


    ///////////////////
    // BODY
    //////////////////
    //Matrix4fDinamic

    //Movement to the first arm
    bodyScript=new MatrixScript();
    bodyScript->add(0.3,oscillateBody);
    bodyScript->add(0.3,oscillateBodySecond);

    //Movement to the first arm
    bodyTScript=new MatrixScript();
    bodyTScript->add(0.15,staticBody);
    bodyTScript->add(0.15,staticBodySecond);
    bodyTScript->add(0.15,staticBody);
    bodyTScript->add(0.15,staticBodySecond);

    animation->add(bodyScript);
    animation->add(bodyTScript);

    animations.add(animation);

    /////////////////////////////////
    // ANIMATION JUMP
    /////////////////////////////////
    animation=new ScriptLMD();
    ///////////////////
    // LEG
    //////////////////
    oscillateLeg=new OscillateRotation(true,30,0,1,300,vec3f(1,0,0),2);
    oscillateLegSecond=new OscillateRotation(false,0,-30,1,300,vec3f(1,0,0),1);

    //Movement to the first leg
    LegScriptLeft=new MatrixScript();
    LegScriptLeft->add(0.15,oscillateLeg);
    LegScriptLeft->add(0.15,oscillateLegSecond);


    //Movement to the second leg
    LegScriptRight=new MatrixScript();
    LegScriptRight->add(0.15,oscillateLegSecond);
    LegScriptRight->add(0.15,oscillateLeg);

    //Add the script to our animation
    animation->add(LegScriptRight);
    animation->add(LegScriptLeft);

    ///////////////////
    // ARM
    //////////////////
    Matrix4f * armJumpMatrix=new Matrix4f();
    armJumpMatrix->rotation(60,1,0,0);
    MatrixStatic * staticArm=new MatrixStatic(*armJumpMatrix);

    //Movement to the first arm
    ElbowScriptLeft=new MatrixScript();
    ArmScriptLeft=new MatrixScript();
    ElbowScriptTLeft=new MatrixScript();

    ElbowScriptLeft->add(0.5,notMove);
    ArmScriptLeft->add(0.5,staticArm);
    ElbowScriptTLeft->add(0.5,notMove);

    //Movement to the second arm
    ElbowScriptRight=new MatrixScript();
    ArmScriptRight=new MatrixScript();
    ElbowScriptRight->add(0.5,notMove);
    ArmScriptRight->add(0.5,staticArm);


    //Add the script to our animation
    animation->add(ElbowScriptRight);  //4
    animation->add(ElbowScriptTRight); //7
    animation->add(ElbowScriptLeft);   //5
    animation->add(ElbowScriptTLeft);  //7
    animation->add(ArmScriptRight);
    animation->add(ArmScriptLeft);     //7


    ///////////////////
    // BODY
    //////////////////
    //Matrix4fDinamic

    //Movement to the first arm
    bodyScript=new MatrixScript();
    bodyScript->add(0.3,notMove);


    //Movement to the first arm
    bodyTScript=new MatrixScript();
    bodyTScript->add(0.15,notMove);


    animation->add(bodyScript);
    animation->add(bodyTScript);

    animations.add(animation);


    /////////////////////////////////
    // ANIMATION GRAVITY
    /////////////////////////////////
    animation=new ScriptLMD();
    ///////////////////
    // LEG
    //////////////////
    oscillateLeg=new OscillateRotation(true,30,0,1,300,vec3f(1,0,0),2);
    oscillateLegSecond=new OscillateRotation(false,0,-30,1,300,vec3f(1,0,0),1);

    //Movement to the first leg
    LegScriptLeft=new MatrixScript();
    LegScriptLeft->add(0.15,oscillateLeg);
    LegScriptLeft->add(0.15,oscillateLegSecond);


    //Movement to the second leg
    LegScriptRight=new MatrixScript();
    LegScriptRight->add(0.15,oscillateLegSecond);
    LegScriptRight->add(0.15,oscillateLeg);

    //Add the script to our animation
    animation->add(LegScriptRight);
    animation->add(LegScriptLeft);

    ///////////////////
    // ARM
    //////////////////
    armJumpMatrix=new Matrix4f();
    armJumpMatrix->rotation(30,0,0,1);
    MatrixStatic * staticArmRight=new MatrixStatic(*armJumpMatrix);

    armJumpMatrix=new Matrix4f();
    armJumpMatrix->rotation(-30,0,0,1);
    MatrixStatic * staticArmLeft=new MatrixStatic(*armJumpMatrix);

    //Movement to the first arm
    ElbowScriptLeft=new MatrixScript();
    ArmScriptLeft=new MatrixScript();
    ElbowScriptTLeft=new MatrixScript();

    ElbowScriptLeft->add(0.5,notMove);
    ArmScriptLeft->add(0.5,staticArmLeft);
    ElbowScriptTLeft->add(0.5,notMove);

    //Movement to the second arm
    ElbowScriptRight=new MatrixScript();
    ArmScriptRight=new MatrixScript();
    ElbowScriptRight->add(0.5,notMove);
    ArmScriptRight->add(0.5,staticArmRight);


    //Add the script to our animation
    animation->add(ElbowScriptRight);  //4
    animation->add(ElbowScriptTRight); //7
    animation->add(ElbowScriptLeft);   //5
    animation->add(ElbowScriptTLeft);  //7
    animation->add(ArmScriptRight);
    animation->add(ArmScriptLeft);     //7


    ///////////////////
    // BODY
    //////////////////
    //Matrix4fDinamic

    //Movement to the first arm
    bodyScript=new MatrixScript();
    bodyScript->add(0.3,notMove);


    //Movement to the first arm
    bodyTScript=new MatrixScript();
    bodyTScript->add(0.15,notMove);


    animation->add(bodyScript);
    animation->add(bodyTScript);

    animations.add(animation);


    /////////////////////////////////
    // ANIMATION HIT-RANGED
    /////////////////////////////////
    animation=new ScriptLMD();
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
    animation->add(LegScriptRight);
    animation->add(LegScriptLeft);

    //Matrix4fDinamic
    ///////////////////
    // ARM
    //////////////////
    shoulderCharge=new OscillateRotation(true,160,90,90,500,vec3f(1.0,0.0,0),1);
    Matrix4f * rotShoulder=new Matrix4f();
    rotShoulder->rotation(90,1.0,0.0,0.0);

    staticShoulder=new MatrixStatic(*rotShoulder);

    //Movement to the first arm
    ElbowScriptLeft=new MatrixScript();
    ArmScriptLeft=new MatrixScript();
    ElbowScriptLeft->add(0.5,notMove);
    ElbowScriptLeft->add(0.5,notMove);
    ArmScriptLeft->add(0.5,notMove);
    ArmScriptLeft->add(0.5,notMove);

    //Movement to the second arm
    ElbowScriptRight=new MatrixScript();
    ArmScriptRight=new MatrixScript();
    ElbowScriptTRight=new MatrixScript();

    ElbowScriptRight->add(0.65,notMove);
    ElbowScriptTRight->add(0.65,notMove);
    ArmScriptRight->add(0.5,staticShoulder);
    ArmScriptRight->add(0.25,shoulderCharge);
    ArmScriptRight->add(0.25,staticShoulder);

    //Add the script to our animation
    animation->add(ElbowScriptRight);  //2
    animation->add(ElbowScriptTRight); //3
    animation->add(ElbowScriptLeft);   //4
    animation->add(ElbowScriptTLeft);  //5
    animation->add(ArmScriptRight);    //6
    animation->add(ArmScriptLeft);     //7


    ///////////////////
    // BODY
    //////////////////
    //Movement to the first arm
    bodyScript=new MatrixScript();
    bodyScript->add(0.3,notMove);

    bodyTScript=new MatrixScript();
    bodyTScript->add(0.3,notMove);

    animation->add(bodyScript);
    animation->add(bodyTScript);

    animations.add(animation);
 }

//**********************************************************************//

void Hero::createProjectile(){
    vec3f posProject;
    vec3f velocityProject;
    avatarDirection dirProject=RIGHTWARD;

    switch(direction){
        case FORWARD:
                posProject=vec3f(position.x,position.y,position.z+0.5);
                velocityProject=vec3f(0.0,0.0,4.0);
                dirProject=FORWARD;
            break;
        case BACKWARD:
                posProject=vec3f(position.x,position.y,position.z-0.5);
                velocityProject=vec3f(0.0,0.0,-4.0);
                dirProject=BACKWARD;
            break;
        case LEFTWARD:
                posProject=vec3f(position.x-0.5,position.y,position.z);
                velocityProject=vec3f(-4.0,0.0,0.0);
                dirProject=LEFTWARD;
            break;
        case RIGHTWARD:
                posProject=vec3f(position.x+0.5,position.y,position.z);
                velocityProject=vec3f(4.0,0.0,0.0);
                dirProject=RIGHTWARD;
            break;
        case FOR_LEFTWARD:
                posProject=vec3f(position.x-0.5,position.y,position.z+0.5);
                velocityProject=vec3f(-3.0,0.0,3.0);
                dirProject=FOR_LEFTWARD;
            break;
        case FOR_RIGHTWARD:
                posProject=vec3f(position.x+0.5,position.y,position.z+0.5);
                velocityProject=vec3f(3.0,0.0,3.0);
                dirProject=FOR_RIGHTWARD;
            break;
        case BACK_LEFTWARD:
                posProject=vec3f(position.x-0.5,position.y,position.z-0.5);
                velocityProject=vec3f(-3.0,0.0,-3.0);
                dirProject=BACK_LEFTWARD;
            break;
        case BACK_RIGHTWARD:
                posProject=vec3f(position.x+0.5,position.y,position.z-0.5);
                velocityProject=vec3f(3.0,0.0,-3.0);
                dirProject=BACK_RIGHTWARD;

            break;
    }

    projectiles.push_back(new Projectile(posProject,velocityProject,dirProject,currentWeapon->getDamage(),"ARROW","mARCHENEMY"));
}
