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
    scaleMatrix->scale(0.3,0.5,1);

    Matrix4f *scaleSphere=new Matrix4f();
    scaleSphere->scale(0.28,0.28,0.28);

    Matrix4f *transMatrix=new Matrix4f();
    transMatrix->translation(0.0,0.0,0.5);

    Matrix4f *AnkFootransMatrix=new Matrix4f();
    AnkFootransMatrix->translation(0.0,-1.0,0.0);

    //Createa new Movement
    Matrix4f * moveAnkle=new Matrix4f();
    moveAnkle->identity();
    moveMatrix.push_back(moveAnkle);

    OscillateRotation * oscillate=new OscillateRotation(true,90,30,50,30,vec3f(1,0,0));
    animation.add(oscillate);



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
    ankle_foot->add(moveAnkle);
    ankle_foot->add(static_cast<Object3D*>(ankle));
    ankle_foot->add(static_cast<Object3D*>(foot));

    root->add(static_cast<Object3D*>(ankle_foot));
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
    cout<< "//////////////////////Prob//////////////////"<<endl;
    cout<< matrix[0]<< " "<< matrix[1]<< " "<< matrix[2]<< " "<< matrix[3]<< endl;
    cout<< matrix[4]<< " "<< matrix[5]<< " "<< matrix[6]<< " "<< matrix[7]<< endl;
    cout<< matrix[8]<< " "<< matrix[9]<< " "<< matrix[10]<< " "<< matrix[11]<< endl;
    cout<< matrix[12]<< " "<< matrix[13]<< " "<< matrix[14]<< " "<< matrix[15]<< endl;
    cout<< "////////////////////////////////////////////"<<endl;

    moveMatrix[0]->setMatrix(animation.readMatrix(0).getMatrix());
    root->visualization(cv);
}
