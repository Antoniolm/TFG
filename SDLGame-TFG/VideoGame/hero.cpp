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
    //Create each primitive
    string file("geometries/cube.ply");
    Mesh * cube=new Mesh(file);
    cube->LoadShader("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    cube->init();

    file=string("geometries/sphere.ply");
    Mesh * sphere=new Mesh(file);
    sphere->LoadShader("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    sphere->init();

    file=string("geometries/cylinder.ply");
    Mesh * cylinder=new Mesh(file);
    cylinder->LoadShader("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    cylinder->init();

    Matrix4f *scaleMatrix=new Matrix4f();
    scaleMatrix->scale(0.3,0.3,0.6);

    Matrix4f *scaleSphere=new Matrix4f();
    scaleSphere->scale(0.15,0.15,0.15);

    Matrix4f *scaleCylinder=new Matrix4f();
    scaleCylinder->scale(0.1,0.1,0.7);

    Matrix4f *scaleCylinder2=new Matrix4f();
    scaleCylinder2->scale(0.1,0.1,0.6);

    Matrix4f *transCylinder=new Matrix4f();
    transCylinder->translation(0.0,-0.7,0.0);

    Matrix4f *transLeg=new Matrix4f();
    transLeg->translation(0.0,-0.6,0.0);

    Matrix4f *rotateCylinder=new Matrix4f();
    rotateCylinder->rotation(90,1.0,0.0,0.0);

    Matrix4f *transMatrix=new Matrix4f();
    transMatrix->translation(0.0,0.0,0.5);

    Matrix4f *AnkFootransMatrix=new Matrix4f();
    AnkFootransMatrix->translation(0.0,-0.8,0.0);

    //Create a new Movement
    Matrix4f * moveKnee=new Matrix4f();
    moveKnee->identity();
    moveMatrix.push_back(moveKnee);

    Matrix4f * moveLeg=new Matrix4f();
    moveLeg->identity();
    moveMatrix.push_back(moveLeg);

    OscillateRotation * oscillateKnee=new OscillateRotation(false,0,-40,0,50,vec3f(1,0,0));
    OscillateRotation * oscillateLeg=new OscillateRotation(true,40,0,0,50,vec3f(1,0,0));
    animation.add(oscillateKnee);
    animation.add(oscillateLeg);

    //Ankle + foot
    NodeSceneGraph * ankle=new NodeSceneGraph();
    NodeSceneGraph * foot=new NodeSceneGraph();
    NodeSceneGraph * ankle_foot=new NodeSceneGraph();
    ankle->add(scaleSphere);
    ankle->add(static_cast<Object3D*>(sphere));
    foot->add(transMatrix);
    foot->add(scaleMatrix);
    foot->add(static_cast<Object3D*>(cube));
    ankle_foot->add(AnkFootransMatrix);
    //ankle_foot->add(moveAnkle);
    ankle_foot->add(static_cast<Object3D*>(ankle));
    ankle_foot->add(static_cast<Object3D*>(foot));

    //knee + ankle
    NodeSceneGraph * knee_ankle=new NodeSceneGraph();

    knee_ankle->add(transCylinder);
    knee_ankle->add(moveKnee);
    knee_ankle->add(static_cast<Object3D*>(ankle));
    knee_ankle->add(transCylinder);
    knee_ankle->add(static_cast<Object3D*>(ankle_foot));
    knee_ankle->add(rotateCylinder);
    knee_ankle->add(scaleCylinder);
    knee_ankle->add(static_cast<Object3D*>(cylinder));

    //Leg
    NodeSceneGraph * leg=new NodeSceneGraph();
    leg->add(moveLeg);
    leg->add(static_cast<Object3D*>(ankle));
    leg->add(transLeg);
    leg->add(static_cast<Object3D*>(knee_ankle));
    leg->add(rotateCylinder);
    leg->add(scaleCylinder2);
    leg->add(static_cast<Object3D*>(cylinder));


    Matrix4f *mat=new Matrix4f();
    mat->translation(-0.8,0.0,0.0);
    root->add(static_cast<Object3D*>(leg));
    root->add(mat);
    root->add(static_cast<Object3D*>(leg));
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
    animation.updateState(time);
    GLfloat * matrix=animation.readMatrix(0).getMatrix();

    for(int i=0;i<2;i++)
    moveMatrix[i]->setMatrix(animation.readMatrix(i).getMatrix());

    root->visualization(cv);
}
