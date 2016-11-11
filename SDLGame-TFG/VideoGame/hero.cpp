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
    //Create each object
    string file=string("geometries/sphere.obj");
    MeshMaterial * sphereObject=new MeshMaterial(file);
    sphereObject->LoadShader("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    sphereObject->init();

    file=string("geometries/pill.obj");
    MeshMaterial * pillObject=new MeshMaterial(file);
    pillObject->LoadShader("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    pillObject->init();

    /*file=string("geometries/hand.obj");
    MeshMaterial * handObject=new MeshMaterial(file);
    handObject->LoadShader("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    handObject->init();*/

    file=string("geometries/foot.obj");
    MeshMaterial * footObject=new MeshMaterial(file);
    footObject->LoadShader("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    footObject->init();

    file=string("geometries/hip.obj");
    MeshMaterial * hipObject=new MeshMaterial(file);
    hipObject->LoadShader("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    hipObject->init();

    Matrix4f *scaleFoot=new Matrix4f();
    scaleFoot->scale(0.2,0.2,0.2);

    Matrix4f *rotateFoot=new Matrix4f();
    rotateFoot->rotation(-90,0.0,1.0,0.0);

    Matrix4f *scaleSphere=new Matrix4f();
    scaleSphere->scale(0.15,0.15,0.15);

    Matrix4f *scalePillKnee=new Matrix4f();
    scalePillKnee->scale(0.3,0.6,0.3);

    Matrix4f *scalePill=new Matrix4f();
    scalePill->scale(0.3,0.5,0.3);

    Matrix4f *scaleHip=new Matrix4f();
    scaleHip->scale(0.4,0.4,0.3);

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

    OscillateRotation * oscillateKnee=new OscillateRotation(false,0,-40,0,100,vec3f(1,0,0));
    OscillateRotation * oscillateLeg=new OscillateRotation(true,40,0,0,100,vec3f(1,0,0));
    MatrixStatic * notMove=new MatrixStatic();

    //Movement to the first leg
    MatrixScript * KneeScriptLeft=new MatrixScript();
    MatrixScript * LegScriptLeft=new MatrixScript();
    KneeScriptLeft->add(0.6,oscillateKnee);
    KneeScriptLeft->add(0.6,notMove);
    LegScriptLeft->add(0.6,oscillateLeg);
    LegScriptLeft->add(0.6,notMove);


    //Movement to the second leg
    MatrixScript * KneeScriptRight=new MatrixScript();
    MatrixScript * LegScriptRight=new MatrixScript();
    KneeScriptRight->add(0.6,notMove);
    KneeScriptRight->add(0.6,oscillateKnee);
    LegScriptRight->add(0.6,notMove);
    LegScriptRight->add(0.6,oscillateLeg);

    //Add the script to our animation
    animation.add(KneeScriptRight);
    animation.add(KneeScriptLeft);
    animation.add(LegScriptRight);
    animation.add(LegScriptLeft);

    //Movement for our hero
    moveHero=new Matrix4f();
    moveHero->identity();
    moveHero->translation(0.5,0.1,-1);

    //Ankle + foot
    NodeSceneGraph * ankle=new NodeSceneGraph();
    NodeSceneGraph * ankle_foot=new NodeSceneGraph();
    ankle->add(scaleSphere);
    ankle->add(static_cast<Object3D*>(sphereObject));
    ankle_foot->add(AnkFootransMatrix);
    ankle_foot->add(rotateFoot);
    ankle_foot->add(scaleFoot);
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

    //Leg Left
    NodeSceneGraph * legLeft=new NodeSceneGraph();
    legLeft->add(moveLegLeft);
    legLeft->add(static_cast<Object3D*>(ankle));
    legLeft->add(transLeg);
    legLeft->add(static_cast<Object3D*>(knee_ankleLeft));
    legLeft->add(scalePill);
    legLeft->add(static_cast<Object3D*>(pillObject));

    //Leg Right
    NodeSceneGraph * legRight=new NodeSceneGraph();
    legRight->add(moveLegRight);
    legRight->add(static_cast<Object3D*>(ankle));
    legRight->add(transLeg);
    legRight->add(static_cast<Object3D*>(knee_ankleRight));
    legRight->add(scalePill);
    legRight->add(static_cast<Object3D*>(pillObject));

    //////////////////////////////////////////////////////
    /////                  Arms                      /////
    //////////////////////////////////////////////////////


    //Create a new Movement
    /*Matrix4f * moveKneeRight=new Matrix4f();
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

    OscillateRotation * oscillateKnee=new OscillateRotation(false,0,-40,0,50,vec3f(1,0,0));
    OscillateRotation * oscillateLeg=new OscillateRotation(true,40,0,0,50,vec3f(1,0,0));
    MatrixStatic * notMove=new MatrixStatic();

    //Movement to the first leg
    MatrixScript * KneeScriptLeft=new MatrixScript();
    MatrixScript * LegScriptLeft=new MatrixScript();
    KneeScriptLeft->add(1.55,oscillateKnee);
    KneeScriptLeft->add(1.55,notMove);
    LegScriptLeft->add(1.55,oscillateLeg);
    LegScriptLeft->add(1.55,notMove);


    //Movement to the second leg
    MatrixScript * KneeScriptRight=new MatrixScript();
    MatrixScript * LegScriptRight=new MatrixScript();
    KneeScriptRight->add(1.55,notMove);
    KneeScriptRight->add(1.55,oscillateKnee);
    LegScriptRight->add(1.55,notMove);
    LegScriptRight->add(1.55,oscillateLeg);

    //Add the script to our animation
    animation.add(KneeScriptRight);
    animation.add(KneeScriptLeft);
    animation.add(LegScriptRight);
    animation.add(LegScriptLeft);
*/

    Matrix4f * scaleHand=new Matrix4f();
    scaleHand->scale(0.2,0.2,0.2);

    Matrix4f * transHand=new Matrix4f();
    transHand->translation(0.0,-0.6,-0.2);

    Matrix4f * wristHandTransMatrix=new Matrix4f();
    wristHandTransMatrix->translation(0.0,-0.6,0.0);

    Matrix4f * rotateHand=new Matrix4f();
    rotateHand->rotation(180,1,0,0);

    //wrist + hand
    NodeSceneGraph * wrist=new NodeSceneGraph();
    NodeSceneGraph * hand=new NodeSceneGraph();
    NodeSceneGraph * wrist_hand=new NodeSceneGraph();
    wrist->add(scaleSphere);
    wrist->add(static_cast<Object3D*>(sphereObject));
    hand->add(transHand);
    hand->add(rotateHand);
    hand->add(scaleHand);
    //hand->add(static_cast<Object3D*>(handObject));
    wrist_hand->add(wristHandTransMatrix);
    wrist_hand->add(static_cast<Object3D*>(wrist));
    wrist_hand->add(static_cast<Object3D*>(hand));

    //elbow + wrist
    NodeSceneGraph * elbow_wrist=new NodeSceneGraph();

    Matrix4f * scaleElbowCylin=new Matrix4f();
    scaleElbowCylin->scale(0.1,0.1,0.5);

    elbow_wrist->add(static_cast<Object3D*>(wrist));
    elbow_wrist->add(transCylinder);
    elbow_wrist->add(static_cast<Object3D*>(wrist_hand));
    elbow_wrist->add(rotateCylinder);
    elbow_wrist->add(scaleElbowCylin);
    elbow_wrist->add(static_cast<Object3D*>(pillObject));

    //Leg
    /*NodeSceneGraph * elbow_wristRight=new NodeSceneGraph();
    elbow_wristRight->add(transCylinder);
    elbow_wristRight->add(moveKneeRight);
    elbow_wristRight->add(static_cast<Object3D*>(elbow_wrist));

    NodeSceneGraph * knee_ankleLeft=new NodeSceneGraph();
    knee_ankleLeft->add(transCylinder);
    knee_ankleLeft->add(moveKneeLeft);
    knee_ankleLeft->add(static_cast<Object3D*>(knee_ankle));

    //Leg Left
    NodeSceneGraph * legLeft=new NodeSceneGraph();
    legLeft->add(moveLegLeft);
    legLeft->add(static_cast<Object3D*>(ankle));
    legLeft->add(transLeg);
    legLeft->add(static_cast<Object3D*>(knee_ankleLeft));
    legLeft->add(rotateCylinder);
    legLeft->add(scaleCylinder2);
    legLeft->add(static_cast<Object3D*>(cylinder));

    //Leg Right
    NodeSceneGraph * legRight=new NodeSceneGraph();
    legRight->add(moveLegRight);
    legRight->add(static_cast<Object3D*>(ankle));
    legRight->add(transLeg);
    legRight->add(static_cast<Object3D*>(knee_ankleRight));
    legRight->add(rotateCylinder);
    legRight->add(scaleCylinder2);
    legRight->add(static_cast<Object3D*>(cylinder));*/


    Matrix4f *mat=new Matrix4f();
    mat->translation(-0.8,0.0,0.0);
    root->add(moveHero);

    Matrix4f *mat2=new Matrix4f();
    mat2->translation(0.4,0.0,0.0);

    NodeSceneGraph * hipNode=new NodeSceneGraph();
    hipNode->add(scaleHip);
    hipNode->add(static_cast<Object3D*>(hipObject));

    root->add((static_cast<Object3D*>(hipNode)));
    root->add(mat2);
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

    animation.updateState(time-currentTime);
    GLfloat * matrix;

    for(int i=0;i<4;i++)
        moveMatrix[i]->setMatrix(animation.readMatrix(i).getMatrix());

    root->visualization(cv);

    currentTime+=(time-currentTime);
}

//**********************************************************************//

void Hero::moveBody(Matrix4f * moveMatrix){
    moveHero->product(moveMatrix->getMatrix());
}
