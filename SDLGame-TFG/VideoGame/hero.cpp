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
    direction=FORWARD;
    isMoving=true;

    //////////////////////////////////////////////////////
    /////           All the meshMaterial             /////
    //////////////////////////////////////////////////////
    string file=string("geometries/sphere.obj");
    Mesh * sphereObject=new Mesh(file);
    sphereObject->init();

    file=string("geometries/pill.obj");
    Mesh * pillObject=new Mesh(file);
    pillObject->init();

    file=string("geometries/pillLeg.obj");
    Mesh * pillLegObject=new Mesh(file);
    pillLegObject->init();

    file=string("geometries/hand.obj");
    Mesh * handObject=new Mesh(file);
    handObject->init();

    file=string("geometries/shoulder.obj");
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
    scaleFoot->scale(0.5,0.5,0.5);

    Matrix4f *rotateFoot=new Matrix4f();
    rotateFoot->rotation(-90,0.0,1.0,0.0);

    Matrix4f *scaleSphere=new Matrix4f();
    scaleSphere->scale(0.15,0.15,0.15);

    Matrix4f *scalePillKnee=new Matrix4f();
    scalePillKnee->scale(0.3,0.6,0.3);

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

    Matrix4f *AnkFootransMatrix=new Matrix4f();
    AnkFootransMatrix->translation(0.0,-0.8,0.2);

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
    NodeSceneGraph * ankle=new NodeSceneGraph();
    NodeSceneGraph * ankle_foot=new NodeSceneGraph();
    ankle->add(scaleSphere);
    ankle->add(static_cast<Object3D*>(sphereObject));
    ankle_foot->add(AnkFootransMatrix);
    ankle_foot->add(rotateFoot);
    ankle_foot->add(scaleFoot);
    Material * materialFoot=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/textureFoot.png");
    ankle_foot->add(materialFoot);
    ankle_foot->add(static_cast<Object3D*>(footObject));

    //knee + ankle
    NodeSceneGraph * knee_ankle=new NodeSceneGraph();

    //knee_ankle->add(transCylinder);
    //knee_ankle->add(moveKnee);
    knee_ankle->add(static_cast<Object3D*>(ankle));
    knee_ankle->add(transCylinder);
    knee_ankle->add(static_cast<Object3D*>(ankle_foot));
    knee_ankle->add(scalePillKnee);
    knee_ankle->add(static_cast<Object3D*>(pillObject));

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
    legLeft->add(static_cast<Object3D*>(ankle));
    legLeft->add(transLeg);
    legLeft->add(static_cast<Object3D*>(knee_ankleLeft));
    legLeft->add(scalePill);
    legLeft->add(materialLeg);
    legLeft->add(static_cast<Object3D*>(pillLegObject));

    //Leg Right
    NodeSceneGraph * legRight=new NodeSceneGraph();
    legRight->add(moveLegRight);
    legRight->add(static_cast<Object3D*>(ankle));
    legRight->add(transLeg);
    legRight->add(static_cast<Object3D*>(knee_ankleRight));
    legRight->add(scalePill);
    legRight->add(materialLeg);
    legRight->add(static_cast<Object3D*>(pillLegObject));

    //////////////////////////////////////////////////////
    /////                  Arms                      /////
    //////////////////////////////////////////////////////


    //Create a new Movement
    Matrix4f * moveElbowLeft=new Matrix4f();
    moveElbowLeft->identity();
    moveMatrix.push_back(moveElbowLeft);

    Matrix4f * moveElbowRight=new Matrix4f();
    moveElbowRight->identity();
    moveMatrix.push_back(moveElbowRight);

    Matrix4f * moveArmLeft=new Matrix4f();
    moveArmLeft->identity();
    moveMatrix.push_back(moveArmLeft);

    Matrix4f * moveArmRight=new Matrix4f();
    moveArmRight->identity();
    moveMatrix.push_back(moveArmRight);

    //Matrix4fDinamic
    OscillateRotation * oscillateElbow=new OscillateRotation(true,120,0,1,350,vec3f(0.75,0.5,0),2);
    OscillateRotation * oscillateElbow2=new OscillateRotation(true,120,0,1,350,vec3f(0.75,-0.5,0),2);
    OscillateRotation * oscillateShoulder=new OscillateRotation(true,40,0,1,80,vec3f(1.0,0.0,0),2);

    //Movement to the first arm
    MatrixScript * ElbowScriptLeft=new MatrixScript();
    MatrixScript * ArmScriptLeft=new MatrixScript();
    ElbowScriptLeft->add(0.9,oscillateElbow);
    ElbowScriptLeft->add(0.9,notMove);
    ArmScriptLeft->add(0.9,oscillateShoulder);
    ArmScriptLeft->add(0.9,notMove);

    //Movement to the second arm
    MatrixScript * ElbowScriptRight=new MatrixScript();
    MatrixScript * ArmScriptRight=new MatrixScript();
    ElbowScriptRight->add(0.9,notMove);
    ElbowScriptRight->add(0.9,oscillateElbow2);
    ArmScriptRight->add(0.9,notMove);
    ArmScriptRight->add(0.9,oscillateShoulder);


    //Add the script to our animation
    animation.add(ElbowScriptLeft);
    animation.add(ElbowScriptRight);
    animation.add(ArmScriptLeft);
    animation.add(ArmScriptRight);

    Matrix4f * scaleHand=new Matrix4f();
    scaleHand->scale(0.24,0.18,0.2);

    Matrix4f * transHand=new Matrix4f();
    transHand->translation(0.0,-0.1,0.0);

    Matrix4f * wristHandTransMatrix=new Matrix4f();
    wristHandTransMatrix->translation(0.0,-0.5,0.0);

    Matrix4f * elbowWristTransMatrix=new Matrix4f();
    elbowWristTransMatrix->translation(0.0,-0.4,0.0);

    Matrix4f * rotateXHand=new Matrix4f();
    rotateXHand->rotation(180,1,0.0,0);

    Matrix4f * rotateZHand=new Matrix4f();
    rotateZHand->rotation(90,0,1,0);

    Matrix4f * scaleElbowCylin=new Matrix4f();
    scaleElbowCylin->scale(0.2,0.3,0.2);

    Matrix4f * scaleArmTop=new Matrix4f();
    scaleArmTop->scale(0.2,0.4,0.2);

    Matrix4f * scaleShoulder=new Matrix4f();
    scaleShoulder->scale(0.2,0.2,0.2);

    Matrix4f * rotateShoulder=new Matrix4f();
    rotateShoulder->rotation(180,0.0,1.0,0.0);

    Matrix4f * transElbow=new Matrix4f();
    transElbow->translation(0.0,-0.4,0.0);

    Matrix4f * transArms=new Matrix4f();
    transArms->translation(0.0,-0.45,0.0);

    //wrist + hand
    NodeSceneGraph * wrist=new NodeSceneGraph();
    NodeSceneGraph * hand=new NodeSceneGraph();
    NodeSceneGraph * wrist_hand=new NodeSceneGraph();
    wrist->add(scaleSphere);
    wrist->add(static_cast<Object3D*>(sphereObject));
    hand->add(transHand);
    hand->add(scaleHand);
    hand->add(static_cast<Object3D*>(handObject));
    wrist_hand->add(wristHandTransMatrix);
    //wrist_hand->add(static_cast<Object3D*>(wrist));
    wrist_hand->add(materialFoot);
    wrist_hand->add(static_cast<Object3D*>(hand));

    //elbow + wrist
    NodeSceneGraph * elbow_wrist=new NodeSceneGraph();
    elbow_wrist->add(static_cast<Object3D*>(wrist));
    elbow_wrist->add(elbowWristTransMatrix);
    elbow_wrist->add(static_cast<Object3D*>(wrist_hand));
    elbow_wrist->add(scaleElbowCylin);
    elbow_wrist->add(static_cast<Object3D*>(pillObject));

    //Arms
    NodeSceneGraph * elbow_wristRight=new NodeSceneGraph();
    elbow_wristRight->add(transElbow);
    elbow_wristRight->add(moveElbowRight);
    elbow_wristRight->add(static_cast<Object3D*>(elbow_wrist));

    NodeSceneGraph * elbow_wristLeft=new NodeSceneGraph();
    elbow_wristLeft->add(transElbow);
    elbow_wristLeft->add(moveElbowLeft);
    elbow_wristLeft->add(static_cast<Object3D*>(elbow_wrist));

    //Shoulder
    NodeSceneGraph * shoulderLeft=new NodeSceneGraph();
    shoulderLeft->add(rotateShoulder);
    shoulderLeft->add(scaleShoulder);
    shoulderLeft->add(static_cast<Object3D*>(shoulderObject));

    NodeSceneGraph * shoulderRight=new NodeSceneGraph();
    shoulderRight->add(scaleShoulder);
    shoulderRight->add(static_cast<Object3D*>(shoulderObject));

    //Arm left
    NodeSceneGraph * ArmLeft=new NodeSceneGraph();
    ArmLeft->add(moveArmLeft);
    ArmLeft->add(static_cast<Object3D*>(shoulderLeft));
    ArmLeft->add(transArms);
    ArmLeft->add(static_cast<Object3D*>(elbow_wristLeft));
    ArmLeft->add(scaleArmTop);
    ArmLeft->add(static_cast<Object3D*>(pillObject));


    //Arm Right
    NodeSceneGraph * ArmRight=new NodeSceneGraph();
    ArmRight->add(moveArmRight);
    ArmRight->add(static_cast<Object3D*>(shoulderRight));
    ArmRight->add(transArms);
    ArmRight->add(static_cast<Object3D*>(elbow_wristRight));
    ArmRight->add(scaleArmTop);
    ArmRight->add(static_cast<Object3D*>(pillObject));

    //////////////////////////////////////////////////////
    /////         Construction of the hero           /////
    //////////////////////////////////////////////////////

    //Movement for our hero
    moveHero=new Matrix4f();
    moveHero->identity();
    moveHero->translation(1.5,4.8,-1.5);
    root->add(moveHero);

    Matrix4f *mat=new Matrix4f();
    mat->translation(-0.8,0.0,0.0);

    Matrix4f *mat2=new Matrix4f();
    mat2->translation(0.4,0.0,0.0);

    Matrix4f * scaleHero=new Matrix4f();
    scaleHero->scale(0.25,0.25,0.25);

    Matrix4f *trasn2Arms=new Matrix4f();
    trasn2Arms->translation(-2.0,0.0,0.0);

    Matrix4f *trasn2Arms2=new Matrix4f();
    trasn2Arms2->translation(1.0,0.7,0.0);

    Matrix4f *scaleHip=new Matrix4f();
    scaleHip->scale(0.4,0.4,0.3);

    Matrix4f *scaleHead=new Matrix4f();
    scaleHead->scale(0.5,0.5,0.5);

    Matrix4f *transHead=new Matrix4f();
    transHead->translation(0.0,2.8,0.4);

    Matrix4f *transChest=new Matrix4f();
    transChest->translation(0.0,1.15,0.0);

    Matrix4f *scaleChest=new Matrix4f();
    scaleChest->scale(0.9,0.9,0.6);

    NodeSceneGraph * hipNode=new NodeSceneGraph();
    hipNode->add(scaleHip);
    Material * material4=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/prueba.png");
    hipNode->add(material4);
    hipNode->add(static_cast<Object3D*>(hipObject));

    NodeSceneGraph * chestNode=new NodeSceneGraph();
    chestNode->add(scaleChest);
    chestNode->add(static_cast<Object3D*>(chestObject));

    NodeSceneGraph * headNode=new NodeSceneGraph();
    headNode->add(transHead);
    //headNode->add(scaleHead);
    headNode->add(static_cast<Object3D*>(headObject));

    NodeSceneGraph * chest_ArmsNode=new NodeSceneGraph();
    chest_ArmsNode->add(transChest);
    chest_ArmsNode->add(static_cast<Object3D*>(chestNode));
    chest_ArmsNode->add(trasn2Arms2);
    chest_ArmsNode->add(static_cast<Object3D*>(ArmLeft));
    chest_ArmsNode->add(trasn2Arms);
    chest_ArmsNode->add(static_cast<Object3D*>(ArmRight));

    Material * material=new Material(vec3f(1.0f, 0.5f, 0.5f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/bricks.jpg");
    root->add(scaleHero);
    root->add((static_cast<Object3D*>(headNode)));
    root->add(material);
    root->add((static_cast<Object3D*>(hipNode)));
    root->add((static_cast<Object3D*>(chest_ArmsNode)));
    root->add(mat2);
    Material * material2=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/wood.jpg");
    root->add(material2);
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
    cv.visualization_mode=2;
    float time=SDL_GetTicks();

    if(isMoving)
        animation.updateState(time-currentTime);
    GLfloat * matrix;

    for(int i=0;i<moveMatrix.size();i++)
        moveMatrix[i]->setMatrix(animation.readMatrix(i).getMatrix());

    root->visualization(cv);

    currentTime+=(time-currentTime);
}

//**********************************************************************//

void Hero::setMap(RootMap * aMap){
    rootMap=aMap;
}

//**********************************************************************//

bool Hero::moveBody(vec3f aMove,avatarDirection aDir){
    bool hasCollision=false;
    float tenthValue;
    vec3f posHero=getPosition();

    //Check the collision first
    switch(aDir){
        case FORWARD:
            tenthValue=posHero.x-(int)posHero.x;
            hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y,posHero.z+0.3),posHero);

            if(tenthValue<0.5 && !hasCollision){
                hasCollision=rootMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z+0.3),posHero);
            }
            else if(tenthValue>0.6 && !hasCollision){
                hasCollision=rootMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z+0.3),posHero);
            }
        break;
        case BACKWARD:
            tenthValue=posHero.x-(int)posHero.x;
            hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y,posHero.z-0.3),posHero);

            if(tenthValue<0.5 && !hasCollision){
                hasCollision=rootMap->collision(vec3f(posHero.x-0.2,posHero.y,posHero.z-0.3),posHero);
            }
            else if(tenthValue>0.6 && !hasCollision){
                hasCollision=rootMap->collision(vec3f(posHero.x+0.2,posHero.y,posHero.z-0.3),posHero);
            }
        break;
        case LEFTWARD:
            tenthValue=(int)posHero.z-posHero.z;

            hasCollision=rootMap->collision(vec3f(posHero.x-0.3,posHero.y,posHero.z),posHero);

            if(tenthValue<0.5 && !hasCollision){
                hasCollision=rootMap->collision(vec3f(posHero.x-0.3,posHero.y,posHero.z+0.2),posHero);
            }
            else if(tenthValue>0.6 && !hasCollision){
                hasCollision=rootMap->collision(vec3f(posHero.x-0.3,posHero.y,posHero.z-0.2),posHero);
            }
        break;
        case RIGHTWARD:
            tenthValue=(int)posHero.z-posHero.z;
            hasCollision=rootMap->collision(vec3f(posHero.x+0.3,posHero.y,posHero.z),posHero);

            if(tenthValue<0.5 && !hasCollision){
                hasCollision=rootMap->collision(vec3f(posHero.x+0.3,posHero.y,posHero.z+0.2),posHero);
            }
            else if(tenthValue>0.6 && !hasCollision){
                hasCollision=rootMap->collision(vec3f(posHero.x+0.3,posHero.y,posHero.z-0.2),posHero);
            }
        break;
    }

    float time=SDL_GetTicks();
    if(!hasCollision){ //Case -> the hero can move = No collision
        if(direction!=aDir){
            vec4f position;
            position=moveHero->product(position);
            Matrix4f transHero;
            transHero.translation(position.x,position.y,position.z);
            LinearMovement lineMove(aMove);
            transHero.product(lineMove.updateState(time-currentTime).getMatrix());


            int diferentDir=FORWARD-aDir;
            moveHero->identity();
            moveHero->rotation(90*diferentDir,0.0f,1.0f,0.0f);
            moveHero->product(transHero.getMatrix());

            direction=aDir;
        }
        else{
            LinearMovement lineMove(aMove);
            moveHero->product(lineMove.updateState(time-currentTime).getMatrix());
        }

    }
    else{   //Case -> not Move for colission but the hero change the rotation in the Y-axis
        if(direction!=aDir){
            vec4f position;
            position=moveHero->product(position);
            Matrix4f transHero;
            transHero.translation(position.x,position.y,position.z);

            int diferentDir=FORWARD-aDir;
            moveHero->identity();
            moveHero->rotation(45*diferentDir,0.0f,1.0f,0.0f);
            moveHero->product(transHero.getMatrix());

            direction=aDir;

        }
    }

    isMoving=true;

    return !hasCollision;
}

//**********************************************************************//

void Hero::noMove(){
    animation.resetState();
    if(isMoving){
        float time=SDL_GetTicks();
        animation.updateState(time-currentTime);
        currentTime+=(time-currentTime);
    }
    isMoving=false;
}

//**********************************************************************//

void Hero::gravity(float velocity){
    bool hasCollision=false;
    float tenthValueX,tenthValueZ;
    vec3f posHero=getPosition();
    posHero.y-=0.31;

    //Get the tenth of our position
    tenthValueX=posHero.x-(int)posHero.x;
    tenthValueZ=(int)posHero.z-posHero.z;

    //Check the collision in the center
    hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y-0.5,posHero.z),posHero);

    //Check the collision in the area
    if(tenthValueX>0.5 && !hasCollision){ //Case tenth in x >0.5
        if( tenthValueZ<0.5){ //case Tenth in x >0.5 and tenth in z <0.5
            hasCollision=rootMap->collision(vec3f(posHero.x+0.2,posHero.y-0.5,posHero.z),posHero);
            if(!hasCollision)
                hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y-0.5,posHero.z-0.2),posHero);
            if(!hasCollision)
                hasCollision=rootMap->collision(vec3f(posHero.x+0.2,posHero.y-0.5,posHero.z-0.2),posHero);
        }else{  //case Tenth in x >0.5 and tenth in z >= 0.5
            hasCollision=rootMap->collision(vec3f(posHero.x+0.2,posHero.y-0.5,posHero.z),posHero);
            if(!hasCollision)
                hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y-0.5,posHero.z+0.2),posHero);
            if(!hasCollision)
                hasCollision=rootMap->collision(vec3f(posHero.x+0.2,posHero.y-0.5,posHero.z+0.2),posHero);
        }
    }
    else if(tenthValueX<0.5 && !hasCollision){ //Case tenth in x <0.5
        if( tenthValueZ<0.5){ //case Tenth in x <0.5 and tenth in z <0.5
            hasCollision=rootMap->collision(vec3f(posHero.x-0.2,posHero.y-0.5,posHero.z),posHero);
            if(!hasCollision)
                hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y-0.5,posHero.z-0.2),posHero);
            if(!hasCollision)
                hasCollision=rootMap->collision(vec3f(posHero.x-0.2,posHero.y-0.5,posHero.z-0.2),posHero);
        }else{ //case Tenth in x <0.5 and tenth in z >= 0.5
            hasCollision=rootMap->collision(vec3f(posHero.x-0.2,posHero.y-0.5,posHero.z),posHero);
            if(!hasCollision)
                hasCollision=rootMap->collision(vec3f(posHero.x,posHero.y-0.5,posHero.z+0.2),posHero);
            if(!hasCollision)
            hasCollision=rootMap->collision(vec3f(posHero.x-0.2,posHero.y-0.5,posHero.z+0.2),posHero);
        }
    }

    float time=SDL_GetTicks();
    if(!hasCollision){ //if not collision
        LinearMovement transHero(0.0,velocity,0.0);
        moveHero->product(transHero.updateState(time-currentTime).getMatrix());
    }
}

//**********************************************************************//

vec3f Hero::getPosition(){
    vec4f position;
    position=moveHero->product(position);

    //cout<< "Position -> x:"<< position.x << " y: "<< position.y<< " z: "<< position.z << endl;
    return vec3f(position.x,position.y,position.z);
}
