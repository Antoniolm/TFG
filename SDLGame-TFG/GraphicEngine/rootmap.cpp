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

#include "rootmap.h"

RootMap::RootMap()
{
    NodeSceneGraph * root=new NodeSceneGraph();
    NodeSceneGraph * root3=new NodeSceneGraph();
    string p("geometries/cube.ply");
    Mesh * aObject=new Mesh(p);
    aObject->LoadShader("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    aObject->init();

    string p2("geometries/cylinder.ply");
    Mesh * aObject2=new Mesh(p2);
    aObject2->LoadShader("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    aObject2->init();

    Matrix4f *matrixone =new Matrix4f();
    matrixone->scale(0.5,0.5,0.5);

    Matrix4f * matrixtwo=new Matrix4f();
    matrixtwo->translation(0,0,-1);

    Matrix4f * matrixthree=new Matrix4f();
    matrixthree->translation(-1,0,0);

    LinearMovement * movet=new LinearMovement(0,0.5,0.0);
    AxisRotation * axisRot=new AxisRotation(20,0,0,1);
    OscillateRotation * osci=new OscillateRotation(true,90,30,50,30,vec3f(0,0,1));
    MatrixStatic *matrix=new MatrixStatic((*matrixone));
    MatrixStatic *matrix2=new MatrixStatic((*matrixtwo));
    MatrixStatic *matrix4=new MatrixStatic((*matrixtwo));
    MatrixStatic *matrix3=new MatrixStatic((*matrixthree));

    NodeSceneGraph * root2=new NodeSceneGraph();
    root2->add(matrix);

    for(int i=0;i<4;i++){
        root2->add(matrix2);
        root2->add(static_cast<Object3D*>(aObject));
    }

    for(int i=0;i<10;i++){
        root->add(matrix3);
        root->add(static_cast<Object3D*>(root2));
    }
    objectDinamic.push_back(root);

}

//**********************************************************************//

RootMap::~RootMap()
{
    //dtor
}

//**********************************************************************//

void RootMap::visualization(Context & cv){
    list<Object3D *>::iterator it;

    cv.visualization_static=false;
    for(it=objectDinamic.begin();it!=objectDinamic.end();it++)
        (*it)->visualization(cv);

    cv.visualization_static=true;
    for(it=objectStatic.begin();it!=objectStatic.end();it++)
        (*it)->visualization(cv);
}

//**********************************************************************//

void RootMap::initStatic(){
    list<Object3D *>::iterator it;
    Context cv;

    cv.visualization_static=false;
    for(it=objectStatic.begin();it!=objectStatic.end();it++)
        (*it)->visualization(cv);

}

//**********************************************************************//

void RootMap::updateState(float time){

}
