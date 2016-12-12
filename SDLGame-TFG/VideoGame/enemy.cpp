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
    enemyActivate=false;

    //Print a message for check
    cout<< "< Game is loading our enemy >"<< endl;

    //////////////////////////////////////////////////////
    /////             Initialize text                /////
    //////////////////////////////////////////////////////
    TTF_Font *font=TTF_OpenFont( "font/lazy.ttf", 40);
    SDL_Color color= {255,0,0};
    currentText=new Text("",font,color,false);
    activatedDialog=false;

    //////////////////////////////////////////////////////
    /////                All the mesh                /////
    //////////////////////////////////////////////////////
    Mesh * armourObject=new Mesh("geometries/armour.obj");
    armourObject->init();

    Mesh * armour2Object=new Mesh("geometries/armour2.obj");
    armour2Object->init();

    Mesh * armourChestObject=new Mesh("geometries/armourChest.obj");
    armourChestObject->init();

    /*Mesh * armourTestObject=new Mesh("geometries/armourTest.obj");
    armourTestObject->init();*/

    Mesh * kneeObject=new Mesh("geometries/knee.obj");
    kneeObject->init();

    Mesh * pillLegObject=new Mesh("geometries/pillLeg.obj");
    pillLegObject->init();

    Mesh * handObject=new Mesh("geometries/hand.obj");
    handObject->init();

    Mesh * shoulderObject=new Mesh("geometries/topArm.obj");
    shoulderObject->init();

    Mesh * chestObject=new Mesh("geometries/chest.obj");
    chestObject->init();

    Mesh * footObject=new Mesh("geometries/foot.obj");
    footObject->init();

    Mesh * hipObject=new Mesh("geometries/hip.obj");
    hipObject->init();

    Mesh * headObject=new Mesh("geometries/head.obj");
    headObject->init();

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
    Matrix4f * moveKneeRight=new Matrix4f();
    moveKneeRight->identity();
    moveMatrix.push_back(moveKneeRight);

    Matrix4f * moveKneeLeft=new Matrix4f();
    moveKneeLeft->identity();
    moveMatrix.push_back(moveKneeLeft);

    Matrix4f * moveLegRight=new Matrix4f();
    moveLegRight->identity();
    moveMatrix.push_back(moveLegRight);

    Matrix4f * moveLegLeft=new Matrix4f();
    moveLegLeft->identity();
    moveMatrix.push_back(moveLegLeft);

    OscillateRotation * oscillateKnee=new OscillateRotation(false,0,-40,1,150,vec3f(1,0,0),2);
    OscillateRotation * oscillateLeg=new OscillateRotation(true,40,0,1,150,vec3f(1,0,0),2);
    OscillateRotation * oscillateLegSecond=new OscillateRotation(false,0,-20,1,50,vec3f(1,0,0),1);
    MatrixStatic * notMove=new MatrixStatic();

    //Movement to the first leg
    MatrixScript * KneeScriptLeft=new MatrixScript();
    MatrixScript * LegScriptLeft=new MatrixScript();
    KneeScriptLeft->add(0.5,oscillateKnee);
    KneeScriptLeft->add(0.5,notMove);
    LegScriptLeft->add(0.5,oscillateLeg);
    LegScriptLeft->add(0.5,oscillateLegSecond);


    //Movement to the second leg
    MatrixScript * KneeScriptRight=new MatrixScript();
    MatrixScript * LegScriptRight=new MatrixScript();
    KneeScriptRight->add(0.5,notMove);
    KneeScriptRight->add(0.5,oscillateKnee);
    LegScriptRight->add(0.5,oscillateLegSecond);
    LegScriptRight->add(0.5,oscillateLeg);

    //Add the script to our animation
    animation.add(KneeScriptRight);
    animation.add(KneeScriptLeft);
    animation.add(LegScriptRight);
    animation.add(LegScriptLeft);

    //Ankle + foot
    NodeSceneGraph * foot=new NodeSceneGraph();
    foot->add(transFoot);
    foot->add(scaleFoot);
    Material * materialFoot=new Material(vec3f(0.3f, 0.3f, 0.3f),vec3f(0.3f, 0.3f, 0.3f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/wood.png");
    foot->add(materialFoot);
    foot->add(footObject);

    //knee + ankle
    NodeSceneGraph * knee_ankle=new NodeSceneGraph();

    //knee_ankle->add(transCylinder);
    //knee_ankle->add(moveKnee);
    knee_ankle->add(transCylinder);
    knee_ankle->add(foot);
    knee_ankle->add(scaleKnee);
    knee_ankle->add(kneeObject);

    //Leg
    NodeSceneGraph * knee_ankleRight=new NodeSceneGraph();
    knee_ankleRight->add(transCylinder);
    knee_ankleRight->add(moveKneeRight);
    knee_ankleRight->add(knee_ankle);

    NodeSceneGraph * knee_ankleLeft=new NodeSceneGraph();
    knee_ankleLeft->add(transCylinder);
    knee_ankleLeft->add(moveKneeLeft);
    knee_ankleLeft->add(knee_ankle);

    Material * materialLeg=new Material(vec3f(0.3f, 0.3f, 0.3f),vec3f(0.3f, 0.3f, 0.3f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/textureLeg.png");

    //Leg Left
    NodeSceneGraph * legLeft=new NodeSceneGraph();
    legLeft->add(moveLegLeft);
    legLeft->add(transLeg);
    legLeft->add(knee_ankleLeft);
    legLeft->add(scaleKnee);
    legLeft->add(materialFoot);
    legLeft->add(kneeObject);

    //Leg Right
    NodeSceneGraph * legRight=new NodeSceneGraph();
    legRight->add(moveLegRight);
    legRight->add(transLeg);
    legRight->add(knee_ankleRight);
    legRight->add(scaleKnee);
    legRight->add(materialFoot);
    legRight->add(kneeObject);

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

    Material * materialWood=new Material(vec3f(0.3f, 0.3f, 0.3f),vec3f(0.3f, 0.3f, 0.3f),vec3f(0.5f, 0.5f, 0.5f),90.0f,"./textures/wood.png");
    Material * materialTest=new Material(vec3f(0.3f, 0.3f, 0.3f),vec3f(0.3f, 0.3f, 0.3f),vec3f(0.3f, 0.3f, 0.3f),32.0f,"./textures/leaf.jpg");
    //Material * materialArmour=new Material(vec3f(0.8f, 0.8f, 0.8f),vec3f(0.8f, 0.8f, 0.8f),vec3f(0.8f, 0.8f, 0.8f),32.0f,"./textures/plateArmor.png");

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
    handLeft->add(materialLeg);
    handLeft->add(handObject);

    NodeSceneGraph * handRight=new NodeSceneGraph();
    handRight->add(transHand);
    handRight->add(scaleHand);
    handRight->add(materialLeg);
    handRight->add(handObject);

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
    shoulderLeft->add(materialLeg);
    shoulderLeft->add(shoulderObject);

    NodeSceneGraph * shoulderRight=new NodeSceneGraph();
    shoulderRight->add(rotateXShoulder);
    shoulderRight->add(rotateShoulder);
    shoulderRight->add(scaleShoulder);
    shoulderRight->add(materialLeg);
    shoulderRight->add(shoulderObject);

    //Arm left
    NodeSceneGraph * ArmLeft=new NodeSceneGraph();
    ArmLeft->add(moveArmLeft);
    ArmLeft->add(transArms);
    ArmLeft->add(elbow_wristLeft);
    //ArmLeft->add(scaleArmTop);
    ArmLeft->add(shoulderLeft);


    //Arm Right
    NodeSceneGraph * ArmRight=new NodeSceneGraph();
    ArmRight->add(moveArmRight);
    ArmRight->add(transArms);
    ArmRight->add(elbow_wristRight);
    //ArmRight->add(scaleArmTop);
    ArmRight->add(shoulderRight);

    //////////////////////////////////////////////////////
    /////         Construction of the hero           /////
    //////////////////////////////////////////////////////

    //Movement for our hero
    AvatarMove::moveAvatar= new Matrix4f();
    AvatarMove::moveAvatar->translation(position.x,position.y,position.z);
    root->add(AvatarMove::moveAvatar);

    Matrix4f *mat=new Matrix4f();
    mat->translation(-0.8,0.0,0.0);

    Matrix4f *mat2=new Matrix4f();
    mat2->translation(0.4,0.0,0.0);

    Matrix4f * scaleHero=new Matrix4f();
    scaleHero->scale(0.25,0.25,0.25);

    Matrix4f *trasn2Arms=new Matrix4f();
    trasn2Arms->translation(-1.8,0.0,0.0);

    Matrix4f *trasn2Arms2=new Matrix4f();
    trasn2Arms2->translation(0.9,0.7,0.0);

    Matrix4f *scaleArmour=new Matrix4f();
    scaleArmour->scale(0.3,0.3,0.25);

    Matrix4f *scaleArmour2=new Matrix4f();
    scaleArmour2->scale(0.3,0.3,0.3);

    Matrix4f *transArmourChest=new Matrix4f();
    transArmourChest->translation(0.0,1.3,0.0);

    Matrix4f *scaleArmourChest=new Matrix4f();
    scaleArmourChest->scale(0.25,0.28,0.28);
    //scaleArmourChest->scale(1.2,1.2,1.4);

    Matrix4f *transArmour=new Matrix4f();
    transArmour->translation(0.0,1.8,0.0);

    Matrix4f *scaleHip=new Matrix4f();
    scaleHip->scale(0.9,0.5,0.6);

    Matrix4f *scaleHead=new Matrix4f();
    scaleHead->scale(3.5,3.5,3.5);

    Matrix4f *transHead=new Matrix4f();
    transHead->translation(0.0,2.5,0.2);

    Matrix4f *transChest=new Matrix4f();
    transChest->translation(0.0,1.1,0.0);

    Matrix4f *transHip=new Matrix4f();
    transHip->translation(0.0,0.0,0.0);

    Matrix4f *scaleChest=new Matrix4f();
    scaleChest->scale(1.0,0.9,0.6);

    NodeSceneGraph * armourNode=new NodeSceneGraph();
    armourNode->add(transArmour);
    armourNode->add(scaleArmour);
    armourNode->add(materialTest);
    armourNode->add(armourObject);

    NodeSceneGraph * armour2Node=new NodeSceneGraph();
    armour2Node->add(scaleArmour2);
    armour2Node->add(materialTest);
    armour2Node->add(armour2Object);

    NodeSceneGraph * armourChestNode=new NodeSceneGraph();
    armourChestNode->add(transArmourChest);
    armourChestNode->add(scaleArmourChest);
    armourChestNode->add(materialTest);
    armourChestNode->add(armourChestObject);

    NodeSceneGraph * chestNode=new NodeSceneGraph();
    chestNode->add(scaleChest);
    chestNode->add(materialWood);
    chestNode->add(chestObject);

    NodeSceneGraph * headNode=new NodeSceneGraph();
    headNode->add(transHead);
    headNode->add(scaleHead);
    headNode->add(materialWood);
    headNode->add(headObject);

    NodeSceneGraph * chest_ArmsNode=new NodeSceneGraph();
    chest_ArmsNode->add(transChest);
    chest_ArmsNode->add(chestNode);
    chest_ArmsNode->add(trasn2Arms2);
    chest_ArmsNode->add(ArmLeft);
    chest_ArmsNode->add(trasn2Arms);
    chest_ArmsNode->add(ArmRight);

    Material * material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/wood.png");
    root->add(scaleHero);
    root->add(material);
    root->add(armourChestNode);
    //root->add(armourChestTestNode);
    root->add(armour2Node);
    root->add(armourNode);
    root->add(headNode);
    root->add(chest_ArmsNode);
    root->add(mat2);
    root->add(materialWood);
    root->add(legLeft);
    root->add(mat);
    root->add(legRight);
    currentTime=SDL_GetTicks();
    jumpDelay=currentTime;
    hitDelay=currentTime;
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
    if(life>0){
        root->visualization(cv);

        if(activatedDialog)
            currentText->visualization(cv);
    }
}

//**********************************************************************//

void Enemy::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap){
    pair<avatarDirection,vec3f> moveHero;
    vec3f aux;
    currentMap=rootMap;

    if(time-currentTime>200)
        currentTime=time-50;

    if(enemyActivate){ //If enemy is activated
        moveHero=IA.nextPosition(vec3f(position.x,position.y,position.z),rootMap->getHero()->getPosition());

        if(moveHero.second.x!=0.0 || moveHero.second.y!=0.0 || moveHero.second.z!=0.0){ //IA-> is not near of our hero
            if(!moveBody(moveHero.second,moveHero.first) && !isJumping && !isFalling && jumpDelay<(time-1000)){
                activeJump(vec3f(0.0,15.0,0.0),vec3f(0.0,5.0,0.0));
                jumpDelay=time;
            }
        }
        else{ //IA -> is near of our hero so the enemy doesn't move
            if(rootMap->getHero()->isHit() && hitDelay<(time-1000)){ //If the hero is hitting
                addLife(-10);
                activatedDialog=true;
                currentText->setPosition(vec3f(position.x,position.y+1.5f,position.z));
                currentText->setMessage("-10");
                currentText->init();
                hitDelay=time;
            }
            else { //If the hero is not hitting
                if(hitDelay<(time-300))
                    activatedDialog=false;
            }
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
    if(isMoving && !isFalling && !isJumping){
        animation.updateState(time-currentTime);
        for(unsigned i=0;i<moveMatrix.size();i++)
            moveMatrix[i]->setMatrix(animation.readMatrix(i).getMatrix());
    }
    else if(isFalling){
        for(unsigned i=0;i<moveMatrix.size();i++)
            moveMatrix[i]->identity();
        Matrix4f rot;
        rot.rotation(30,0,0,1);
        moveMatrix[6]->setMatrix(rot.getMatrix());
        rot.rotation(-30,0,0,1);
        moveMatrix[7]->setMatrix(rot.getMatrix());
    }
    else if(isJumping){
        for(unsigned i=0;i<moveMatrix.size();i++)
            moveMatrix[i]->identity();
        Matrix4f rot;
        rot.rotation(30,1,0,0);
        moveMatrix[6]->setMatrix(rot.getMatrix());
        moveMatrix[7]->setMatrix(rot.getMatrix());
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