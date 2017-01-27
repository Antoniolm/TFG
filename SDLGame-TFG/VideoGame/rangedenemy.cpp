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

#include "rangedenemy.h"

RangedEnemy::RangedEnemy(){

}

//**********************************************************************//

RangedEnemy::RangedEnemy(float aLife,vec3f aPosition,vec3f aRadioActivity)
{
    life=aLife;
    IA=new IARangedEnemy();
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

    //INIT PROJECTILES
    meshProjectile= meshCollect->getMesh(ARROW);
    materialProjectile=materialCollect->getMaterial(mARCHENEMY);


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
    legLeft->add(meshCollect->getMesh(RFOOT));

    //Leg Right
    NodeSceneGraph * legRight=new NodeSceneGraph();
    legRight->add(moveLegRight);
    legRight->add(transLeg);
    legRight->add(meshCollect->getMesh(RFOOT));

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

    Matrix4f * transWeapon=new Matrix4f();
    transWeapon->translation(0.0,-0.4,0.0);


    //Arms
    NodeSceneGraph * handRight=new NodeSceneGraph();
    handRight->add(transElbow);
    handRight->add(moveElbowRight);
    handRight->add(transHand);
    handRight->add(meshCollect->getMesh(RHAND));
    handRight->add(transWeapon);
    handRight->add(meshCollect->getMesh(CBOW));

    NodeSceneGraph * handLeft=new NodeSceneGraph();
    handLeft->add(transElbow);
    handLeft->add(moveElbowLeft);
    handLeft->add(transHandLeft);
    //handLeft->add(scaleHandInvert);
    handLeft->add(rotateYHand);
    handLeft->add(meshCollect->getMesh(RHAND));

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
    moveAvatar= new Matrix4f();
    moveAvatar->translation(position.x,position.y,position.z);
    root->add(moveAvatar);

    Matrix4f *transLegScene=new Matrix4f();
    transLegScene->translation(-0.4,0.0,0.0);

    Matrix4f *transLegSceneI=new Matrix4f();
    transLegSceneI->translation(0.2,0.0,0.0);

    Matrix4f * scaleHero=new Matrix4f();
    scaleHero->scale(0.5,0.5,0.5);

    Matrix4f * trasnArms=new Matrix4f();
    trasnArms->translation(-0.6,0.0,0.0);

    Matrix4f *trasnArmsI=new Matrix4f();
    trasnArmsI->translation(0.3,0.6,0.3);

    Matrix4f *transHead=new Matrix4f();
    transHead->translation(0.0,1.0,0.0);

    Matrix4f *transChest=new Matrix4f();
    transChest->translation(0.3,0.3,0.0);

    Matrix4f *transChestArm=new Matrix4f();
    transChestArm->translation(0.0,0.1,-0.3);

    NodeSceneGraph * chestNode=new NodeSceneGraph();
    chestNode->add(transChest);
    chestNode->add(meshCollect->getMesh(RCHEST));

    NodeSceneGraph * headNode=new NodeSceneGraph();
    headNode->add(transHead);
    headNode->add(meshCollect->getMesh(RHEAD));

    NodeSceneGraph * chest_ArmsNode=new NodeSceneGraph();
    chest_ArmsNode->add(transChestArm);
    chest_ArmsNode->add(chestNode);
    chest_ArmsNode->add(trasnArmsI);
    chest_ArmsNode->add(ArmLeft);
    chest_ArmsNode->add(trasnArms);
    chest_ArmsNode->add(ArmRight);

    root->add(scaleHero);
    root->add(materialCollect->getMaterial(mARCHENEMY));
    root->add(headNode);
    root->add(chest_ArmsNode);
    root->add(transLegSceneI);
    root->add(legLeft);
    root->add(transLegScene);
    root->add(legRight);
    currentTime=SDL_GetTicks();
    jumpDelay=currentTime;
    dmgDelay=currentTime;
    hitDelay=currentTime;
    IADelay=currentTime;
    currentMove.first=FORWARD;
    currentMove.second=vec3f();

    initAnimation();
}

//**********************************************************************//

RangedEnemy::~RangedEnemy()
{
    //dtor
}

//**********************************************************************//

void RangedEnemy::visualization(Context & cv){
    root->visualization(cv);

    if(activatedDialog){
        currentText->setPosition(vec3f(position.x,position.y+1.5f,position.z));
        currentText->visualization(cv);
    }

    vector<Projectile *>::iterator it;
    for(it=projectiles.begin();it!=projectiles.end();it++){
        (*it)->visualization(cv);
    }
}

//**********************************************************************//

void RangedEnemy::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap){
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
            currentMove=IA->nextPosition(vec3f(position.x,position.y,position.z),posHero,rootMap->getEnemyList());
            IADelay=time;
        }
        if((currentMove.second.x!=0.0 || currentMove.second.y!=0.0 || currentMove.second.z!=0.0)&& !isImpacted){ //IA-> is not near of our hero
            if(!moveBody(currentMove.second,currentMove.first) && !isJumping && !isFalling && jumpDelay<(time-1000)){ //If not move -> enemy jump
                activeJump(vec3f(0.0,12.0,0.0),vec3f(0.0,5.0,0.0));
                jumpDelay=time;
            }
        }
        else {  //If is not near of the target
            //shot arrow
            changeDirection(currentMove.first);
            if(hitDelay<(time-3000)){
                createProjectile(posHero);
                hitDelay=time;
            }
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

    ////////////////////////////
    //UPDATE PROJECTILES
    ////////////////////////////
    vector<Projectile *>::iterator it=projectiles.begin();
    while(it!=projectiles.end()){
        (*it)->updateState(time,currentKeyStates,rootMap);
        if(!(*it)->isLive()){
            it=projectiles.erase(it);
        }
        else
            it++;
    }


    currentTime+=(time-currentTime);
}

//**********************************************************************//

void RangedEnemy::createProjectile(vec3f posAvatar){
    vec3f posProject;
    vec3f velocityProject;
    avatarDirection dirProject=RIGHTWARD;
    //case FORWARD:
    if(position.z>posAvatar.z && (position.x>=posAvatar.x-0.6 && position.x<=posAvatar.x+0.6)){
        posProject=vec3f(position.x,position.y,position.z-0.5);
        velocityProject=vec3f(0.0,0.0,-2.0);
        dirProject=BACKWARD;

    }
    //case BACKWARD:
    else if(position.z<posAvatar.z && (position.x>=posAvatar.x-0.6 && position.x<=posAvatar.x+0.6)){
        posProject=vec3f(position.x,position.y,position.z+0.5);
        velocityProject=vec3f(0.0,0.0,2.0);
        dirProject=FORWARD;
    }
    //case LEFTWARD:
    else if(position.x<posAvatar.x && (position.z>=posAvatar.z-0.6 && position.z<=posAvatar.z+0.6)){
        posProject=vec3f(position.x+0.5,position.y,position.z);
        velocityProject=vec3f(2.0,0.0,0.0);
        dirProject=RIGHTWARD;
    }

    //case RIGHTWARD:
    else if(position.x>posAvatar.x && (position.z>=posAvatar.z-0.6 && position.z<=posAvatar.z+0.6)){
        posProject=vec3f(position.x-0.5,position.y,position.z);
        velocityProject=vec3f(-2.0,0.0,0.0);
        dirProject=LEFTWARD;
    }

    //case FOR_LEFTWARD:
    else if(position.x<posAvatar.x && position.z>posAvatar.z){
        posProject=vec3f(position.x+0.5,position.y,position.z-0.5);
        velocityProject=vec3f(2.0,0.0,-2.0);
        dirProject=BACK_RIGHTWARD;
    }

    //case FOR_RIGHTWARD:
    else if(position.x>posAvatar.x && position.z>posAvatar.z){
        posProject=vec3f(position.x-0.5,position.y,position.z-0.5);
        velocityProject=vec3f(-2.0,0.0,-2.0);
        dirProject=BACK_LEFTWARD;
    }

    //case BACK_LEFTWARD:
    else if(position.x<posAvatar.x && position.z<posAvatar.z){
        posProject=vec3f(position.x+0.5,position.y,position.z+0.5);
        velocityProject=vec3f(2.0,0.0,2.0);
        dirProject=FOR_RIGHTWARD;
    }

    //case BACK_RIGHTWARD:
    else if(position.x>posAvatar.x && position.z<posAvatar.z){
        posProject=vec3f(position.x-0.5,position.y,position.z+0.5);
        velocityProject=vec3f(-2.0,0.0,2.0);
        dirProject=FOR_LEFTWARD;

    }

    projectiles.push_back(new Projectile(posProject,velocityProject,dirProject,meshProjectile,materialProjectile));
}
