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
    isFalling=false;
    isJumping=false;

    //Print a message for check
    cout<< "< Game is loading our hero >"<< endl;

    //////////////////////////////////////////////////////
    /////           All the meshMaterial             /////
    //////////////////////////////////////////////////////
    string file=string("geometries/armour.obj");
    Mesh * armourObject=new Mesh(file);
    armourObject->init();

    file=string("geometries/armour2.obj");
    Mesh * armour2Object=new Mesh(file);
    armour2Object->init();

    file=string("geometries/armourChest.obj");
    Mesh * armourChestObject=new Mesh(file);
    armourChestObject->init();

    file=string("geometries/knee.obj");
    Mesh * kneeObject=new Mesh(file);
    kneeObject->init();

    file=string("geometries/pillLeg.obj");
    Mesh * pillLegObject=new Mesh(file);
    pillLegObject->init();

    file=string("geometries/hand.obj");
    Mesh * handObject=new Mesh(file);
    handObject->init();

    file=string("geometries/topArm.obj");
    Mesh * shoulderObject=new Mesh(file);
    shoulderObject->init();

    file=string("geometries/chest.obj");
    Mesh * chestObject=new Mesh(file);
    chestObject->init();

    file=string("geometries/foot.obj");
    Mesh * footObject=new Mesh(file);
    footObject->init();

    file=string("geometries/hip.obj");
    Mesh * hipObject=new Mesh(file);
    hipObject->init();

    file=string("geometries/head.obj");
    Mesh * headObject=new Mesh(file);
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
    Material * materialFoot=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/wood.png");
    foot->add(materialFoot);
    foot->add(static_cast<Object3D*>(footObject));

    //knee + ankle
    NodeSceneGraph * knee_ankle=new NodeSceneGraph();

    //knee_ankle->add(transCylinder);
    //knee_ankle->add(moveKnee);
    knee_ankle->add(transCylinder);
    knee_ankle->add(static_cast<Object3D*>(foot));
    knee_ankle->add(scaleKnee);
    knee_ankle->add(static_cast<Object3D*>(kneeObject));

    //Leg
    NodeSceneGraph * knee_ankleRight=new NodeSceneGraph();
    knee_ankleRight->add(transCylinder);
    knee_ankleRight->add(moveKneeRight);
    knee_ankleRight->add(static_cast<Object3D*>(knee_ankle));

    NodeSceneGraph * knee_ankleLeft=new NodeSceneGraph();
    knee_ankleLeft->add(transCylinder);
    knee_ankleLeft->add(moveKneeLeft);
    knee_ankleLeft->add(static_cast<Object3D*>(knee_ankle));

    Material * materialLeg=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/textureLeg.png");

    //Leg Left
    NodeSceneGraph * legLeft=new NodeSceneGraph();
    legLeft->add(moveLegLeft);
    legLeft->add(transLeg);
    legLeft->add(static_cast<Object3D*>(knee_ankleLeft));
    legLeft->add(scaleKnee);
    legLeft->add(materialFoot);
    legLeft->add(static_cast<Object3D*>(kneeObject));

    //Leg Right
    NodeSceneGraph * legRight=new NodeSceneGraph();
    legRight->add(moveLegRight);
    legRight->add(transLeg);
    legRight->add(static_cast<Object3D*>(knee_ankleRight));
    legRight->add(scaleKnee);
    legRight->add(materialFoot);
    legRight->add(static_cast<Object3D*>(kneeObject));

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

    Material * materialWood=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),90.0f,"./textures/wood.png");
    Material * materialChest=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/woodChest.png");
    Material * materialTest=new Material(vec3f(0.3f, 0.3f, 0.3f),vec3f(0.3f, 0.3f, 0.3f),vec3f(0.3f, 0.3f, 0.3f),32.0f,"./textures/leaf.jpg");

    //Matrix4fDinamic
    OscillateRotation * oscillateElbow=new OscillateRotation(true,120,0,1,350,vec3f(0.75,0.5,0),2);
    OscillateRotation * oscillateElbow2=new OscillateRotation(true,120,0,1,350,vec3f(0.75,-0.5,0),2);
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
    NodeSceneGraph * handLeft=new NodeSceneGraph();
    handLeft->add(transHandLeft);
    handLeft->add(scaleHand);
    handLeft->add(rotateYHand);
    handLeft->add(materialLeg);
    handLeft->add(static_cast<Object3D*>(handObject));

    NodeSceneGraph * handRight=new NodeSceneGraph();
    handRight->add(transHand);
    handRight->add(scaleHand);
    handRight->add(materialLeg);
    handRight->add(static_cast<Object3D*>(handObject));

    //elbow + wrist

    //Arms
    NodeSceneGraph * elbow_wristRight=new NodeSceneGraph();
    elbow_wristRight->add(transElbow);
    elbow_wristRight->add(moveElbowRight);
    elbow_wristRight->add(rotateXHand);
    elbow_wristRight->add(static_cast<Object3D*>(handRight));

    NodeSceneGraph * elbow_wristLeft=new NodeSceneGraph();
    elbow_wristLeft->add(transElbow);
    elbow_wristLeft->add(moveElbowLeft);
    elbow_wristLeft->add(rotateXHand);
    elbow_wristLeft->add(static_cast<Object3D*>(handLeft));

    //Shoulder
    NodeSceneGraph * shoulderLeft=new NodeSceneGraph();
    shoulderLeft->add(scaleShoulder);
    shoulderLeft->add(rotateXShoulder);
    shoulderLeft->add(materialLeg);
    shoulderLeft->add(static_cast<Object3D*>(shoulderObject));

    NodeSceneGraph * shoulderRight=new NodeSceneGraph();
    shoulderRight->add(rotateXShoulder);
    shoulderRight->add(rotateShoulder);
    shoulderRight->add(scaleShoulder);
    shoulderRight->add(materialLeg);
    shoulderRight->add(static_cast<Object3D*>(shoulderObject));

    //Arm left
    NodeSceneGraph * ArmLeft=new NodeSceneGraph();
    ArmLeft->add(moveArmLeft);
    ArmLeft->add(transArms);
    ArmLeft->add(static_cast<Object3D*>(elbow_wristLeft));
    //ArmLeft->add(scaleArmTop);
    ArmLeft->add(static_cast<Object3D*>(shoulderLeft));


    //Arm Right
    NodeSceneGraph * ArmRight=new NodeSceneGraph();
    ArmRight->add(moveArmRight);
    ArmRight->add(transArms);
    ArmRight->add(static_cast<Object3D*>(elbow_wristRight));
    //ArmRight->add(scaleArmTop);
    ArmRight->add(static_cast<Object3D*>(shoulderRight));

    //////////////////////////////////////////////////////
    /////         Construction of the hero           /////
    //////////////////////////////////////////////////////

    //Movement for our hero
    AvatarMove::moveAvatar= new Matrix4f();
    AvatarMove::moveAvatar->translation(1.5,4.8,-1.5);
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
    armourNode->add(static_cast<Object3D*>(armourObject));

    NodeSceneGraph * armour2Node=new NodeSceneGraph();
    armour2Node->add(scaleArmour2);
    armour2Node->add(materialTest);
    armour2Node->add(static_cast<Object3D*>(armour2Object));

    NodeSceneGraph * armourChestNode=new NodeSceneGraph();
    armourChestNode->add(transArmourChest);
    armourChestNode->add(scaleArmourChest);
    armourChestNode->add(materialTest);
    armourChestNode->add(static_cast<Object3D*>(armourChestObject));

    NodeSceneGraph * chestNode=new NodeSceneGraph();
    chestNode->add(scaleChest);
    chestNode->add(materialWood);
    chestNode->add(static_cast<Object3D*>(chestObject));

    NodeSceneGraph * headNode=new NodeSceneGraph();
    Material * materialHead=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/woodHead.png");
    headNode->add(transHead);
    headNode->add(scaleHead);
    headNode->add(materialHead);
    headNode->add(static_cast<Object3D*>(headObject));

    NodeSceneGraph * chest_ArmsNode=new NodeSceneGraph();
    chest_ArmsNode->add(transChest);
    chest_ArmsNode->add(static_cast<Object3D*>(chestNode));
    chest_ArmsNode->add(trasn2Arms2);
    chest_ArmsNode->add(static_cast<Object3D*>(ArmLeft));
    chest_ArmsNode->add(trasn2Arms);
    chest_ArmsNode->add(static_cast<Object3D*>(ArmRight));

    Material * material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/wood.png");
    root->add(scaleHero);
    root->add(material);
    root->add((static_cast<Object3D*>(armourChestNode)));
    root->add((static_cast<Object3D*>(armour2Node)));
    root->add((static_cast<Object3D*>(armourNode)));
    root->add((static_cast<Object3D*>(headNode)));
    root->add((static_cast<Object3D*>(chest_ArmsNode)));
    root->add(mat2);
    root->add(materialWood);
    root->add(static_cast<Object3D*>(legLeft));
    root->add(mat);
    root->add(static_cast<Object3D*>(legRight));
    currentTime=SDL_GetTicks();
}

//**********************************************************************//

Hero::~Hero()
{
    //dtor
}

//**********************************************************************//

void Hero::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void Hero::updateState(float time){
    bool hasMove=false;
    avatarDirection heroDir;
    vec3f moveHero;
    //case: Player push a bottom
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

    //Case-> Push Left bottom
    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)] && !currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)] &&
    !currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)]){
        moveHero.x=-3.0;moveHero.y=0.0;moveHero.z=0.0;
        heroDir=LEFTWARD;
        hasMove=true;
    }
    //Case-> Push Right bottom
    else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)]&& !currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)] &&
    !currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)]){
        moveHero.x=3.0;moveHero.y=0.0;moveHero.z=0.0;
        heroDir=RIGHTWARD;
        hasMove=true;
    }
    //Case-> Push Up bottom
    else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)]&& !currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)] &&
    !currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)]){
        moveHero.x=0.0;moveHero.y=0.0;moveHero.z=-3.0;
        heroDir=BACKWARD;
        hasMove=true;
    }
    //Case-> Push Down bottom
    else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)]&& !currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)] &&
    !currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)]){
        moveHero.x=0.0;moveHero.y=0.0;moveHero.z=3.0;
        heroDir=FORWARD;
        hasMove=true;
    }
    //Case-> Push Dowm-Left bottoms
    else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)] && currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)] ){
        moveHero.x=-2.0;moveHero.y=0.0;moveHero.z=2.0;
        heroDir=FOR_LEFTWARD;
        hasMove=true;
    }
    //Case-> Push Dowm-Right bottoms
    else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)] && currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)] ){
        moveHero.x=2.0;moveHero.y=0.0;moveHero.z=2.0;
        heroDir=FOR_RIGHTWARD;
        hasMove=true;
    }
    //Case-> Push Up-Left bottoms
    else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)] && currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)]){
        moveHero.x=-2.0;moveHero.y=0.0;moveHero.z=-2.0;
        heroDir=BACK_LEFTWARD;
        hasMove=true;
    }
    //Case-> Push Up-Right bottoms
    else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)] && currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)] ){
        moveHero.x=2.0;moveHero.y=0.0;moveHero.z=-2.0;
        heroDir=BACK_RIGHTWARD;
        hasMove=true;
    }
    else{ //Case-> If not move
        hasMove=false;
        if(!isJumping && !isFalling){
            noMove();
        }
    }

    //Case-> Push Scape bottom to jump
    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_s)] && !isJumping && !isFalling)
        activeJump(10.0,5.0);

    //Move the body
    if(hasMove)
        moveBody(moveHero,heroDir);

    //If the jump is activate
    if(isJumping)
        jump();

    //If the jump is not activate
    else gravity(-5.0);


    //Update Animation
    if(isMoving && !isFalling && !isJumping){
        animation.updateState(time-currentTime);
        for(int i=0;i<moveMatrix.size();i++)
            moveMatrix[i]->setMatrix(animation.readMatrix(i).getMatrix());
    }
    /*else if(isFalling){
        for(int i=0;i<moveMatrix.size();i++)
            moveMatrix[i]->identity();
        Matrix4f rot;
        rot.rotation(30,0,0,1);
        moveMatrix[6]->setMatrix(rot.getMatrix());
        rot.rotation(-30,0,0,1);
        moveMatrix[7]->setMatrix(rot.getMatrix());
    }
    else if(isJumping){
        for(int i=0;i<moveMatrix.size();i++)
            moveMatrix[i]->identity();
        Matrix4f rot;
        rot.rotation(30,1,0,0);
        moveMatrix[6]->setMatrix(rot.getMatrix());
        moveMatrix[7]->setMatrix(rot.getMatrix());
    }*/
    currentTime+=(time-currentTime);
}

//**********************************************************************//

void Hero::setMap(RootMap * aMap){
    rootMap=aMap;
}

//**********************************************************************//

void Hero::noMove(){
    animation.resetState();
    for(int i=0;i<moveMatrix.size();i++)
            moveMatrix[i]->identity();
    isMoving=false;
}

//**********************************************************************//
