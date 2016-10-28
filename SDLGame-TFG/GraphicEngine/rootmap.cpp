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
    string p("geometries/ant.ply");
    Mesh * aObject=new Mesh(p);
    aObject->LoadShader("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    aObject->init();
    Mesh * prueba=new Mesh(*aObject);
    string p2("geometries/cylinder.ply");
    Mesh * aObject2=new Mesh(p2);
    aObject2->LoadShader("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    aObject2->init();

    Matrix4f *matrixone =new Matrix4f();
    matrixone->scale(0.03,0.03,0.03);

    Matrix4f * matrixtwo=new Matrix4f();
    matrixtwo->translation(0.0,0,-2.1);

    Matrix4f * matrixthree=new Matrix4f();
    matrixthree->translation(-1.1,0,0);

    Matrix4f * matrixt=new Matrix4f();
    matrixt->rotation(90,0.0,1.0,0.0);

    LinearMovement * movet=new LinearMovement(0,0.5,0.0);
    AxisRotation * axisRot=new AxisRotation(40,0,0,1);
    OscillateRotation * osci=new OscillateRotation(true,90,30,50,30,vec3f(0,0,1));

    MatrixStatic *matrix=new MatrixStatic((*matrixone));
    MatrixStatic *matrix2=new MatrixStatic((*matrixtwo));
    MatrixStatic *matrix4=new MatrixStatic((*matrixt));
    MatrixStatic *matrix3=new MatrixStatic((*matrixthree));

    NodeSceneGraph * root2=new NodeSceneGraph();

    //root3->add(matrix);
    //root3->add(static_cast<Object3D*>(new Mesh(*aObject)));
    NodeSceneGraph * root=new NodeSceneGraph();
    root->add(matrix);
    root->add(static_cast<Object3D*>(new Mesh(*aObject)));
    //for(int i=0;i<4;i++){

        root2->add(matrix3);
        root2->add(static_cast<Object3D*>(root));
        root2->add(osci);
        root2->add(matrix3);
        root2->add(static_cast<Object3D*>(root));
    //}

    for(int i=0;i<4;i++){
        root3->add(matrix3);
        root3->add(static_cast<Object3D*>(root2));
    }
    objectDinamic.push_back(root3);

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

    object=cv.posObject;
    vec4f pos;

    cout<< "///////INIT///////"<<endl;
    for(it=object.begin();it!=object.end();it++){
        pos=(*it)->getPosition();

        cout<< pos.x<< " "<< pos.y<< " "<< pos.z<< endl;
    }
    cout<< "//////////////////"<<endl;

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
    //objectStatic.clear();
    //objectStatic=cv.posObject;
}

//**********************************************************************//

void RootMap::updateState(float time){

}
