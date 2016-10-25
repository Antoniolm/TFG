// *********************************************************************
// **
// ** Copyright (C) 2016 Antonio David López Machado
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
    matrixone->scale(0.1,0.1,0.1);

    Matrix4f * matrixtwo=new Matrix4f();
    matrixtwo->translation(0,-0.1,0);

    Matrix4f * matrixthree=new Matrix4f();
    matrixthree->translation(-0.5,0,0);

    LinearMovement * movet=new LinearMovement(0,0.5,0.0);
    AxisRotation * axisRot=new AxisRotation(20,0,0,1);

    MatrixStatic *matrix=new MatrixStatic((*matrixone));
    MatrixStatic *matrix2=new MatrixStatic((*matrixtwo));
    MatrixStatic *matrix4=new MatrixStatic((*matrixtwo));
    MatrixStatic *matrix3=new MatrixStatic((*matrixthree));

    NodeSceneGraph * root2=new NodeSceneGraph();
    root2->add(matrix2); //tr y -0.1
    root2->add(static_cast<Object3D*>(aObject));
    root2->add(matrix4); //tr y -0.1
    root2->add(static_cast<Object3D*>(aObject));
    root->add(matrix3);
    root->add(static_cast<Object3D*>(root2));
    root->add(matrix3); //tr x -0.5
    //root->add(static_cast<Object3D*>(aObject));
    root->add(static_cast<Object3D*>(root2));
    objectList.push_back(root);
}

//**********************************************************************//

RootMap::~RootMap()
{
    //dtor
}

//**********************************************************************//

void RootMap::visualization(Context & cv){
    vector<Object3D *>::iterator it;

    for(int i=0;i<objectList.size();i++)
        (objectList[i])->visualization(cv);
}

//**********************************************************************//

void RootMap::updateState(float time){

}
