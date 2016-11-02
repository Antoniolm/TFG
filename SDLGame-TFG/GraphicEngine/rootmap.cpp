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
    NodeSceneGraph * root3=new NodeSceneGraph();
    string file("geometries/ant.ply");
    Mesh * aObject=new Mesh(file);
    aObject->LoadShader("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    aObject->init();

    file=string("geometries/cylinder.ply");
    Mesh * aObject2=new Mesh(file);
    aObject2->LoadShader("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    aObject2->init();

    Matrix4f *matrix =new Matrix4f();
    matrix->scale(0.1,0.1,0.1);

    Matrix4f * matrix2=new Matrix4f();
    matrix2->translation(-5.0,1,0.0);

    Matrix4f * matrix3=new Matrix4f();
    matrix3->translation(1.1,1.1,0);

    Matrix4f * matrixt=new Matrix4f();
    matrixt->rotation(90,0.0,1.0,0.0);

    //LinearMovement * movet=new LinearMovement(0,0.5,0.0);
    //AxisRotation * axisRot=new AxisRotation(40,0,0,1);
    //OscillateRotation * osci=new OscillateRotation(true,90,30,50,30,vec3f(0,0,1));

    NodeSceneGraph * root2=new NodeSceneGraph();
    NodeSceneGraph * root4=new NodeSceneGraph();

    NodeSceneGraph * root=new NodeSceneGraph();
    root->add(matrix);
    root->add(static_cast<Object3D*>(aObject));

        root2->add(matrix3);
        root2->add(static_cast<Object3D*>(root));
        //root2->add(osci);
        root2->add(matrix3);
        root2->add(static_cast<Object3D*>(root));

        //root4->add(osci);
        root4->add(matrix2);
        root4->add(static_cast<Object3D*>(root));

    for(int i=0;i<3;i++){
        root3->add(matrix3);
        root3->add(matrix3);
        root3->add(static_cast<Object3D*>(root2));
    }
    objectStatic.push_back(root3);
    objectDinamic.push_back(root4);

    //Create the hero
    hero=new Hero();

}

//**********************************************************************//

RootMap::~RootMap()
{
    //dtor
}

//**********************************************************************//

void RootMap::visualization(Context & cv){

    list<Object3D *>::iterator it;

    //Draw the dynamic object
    for(it=objectDinamic.begin();it!=objectDinamic.end();it++)
        (*it)->visualization(cv);

    //Draw the static object
    for(it=objectStatic.begin();it!=objectStatic.end();it++){
        (*it)->visualization(cv);
    }

    //Draw hero
    hero->visualization(cv);
}

//**********************************************************************//

void RootMap::updateState(float time){

}
