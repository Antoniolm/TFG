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

#include "rootmap.h"

RootMap::RootMap()
{
    string file("geometries/cube.obj");
    Mesh * aObject=new Mesh(file);
    aObject->init();

    Matrix4f *scaleCube =new Matrix4f();
    scaleCube->scale(0.5,0.5,0.5);

    Matrix4f * matrix2=new Matrix4f();
    matrix2->translation(-5.0,1,0.0);

    Matrix4f * transOneCube=new Matrix4f();
    transOneCube->translation(0.5,0.5,-0.5);

    Matrix4f * transObsCube=new Matrix4f();
    transObsCube->translation(2.0,1.0,-2.0);

    Matrix4f * transGravityCube=new Matrix4f();
    transGravityCube->translation(1,1.0,-1.0);

    Matrix4f * transCube=new Matrix4f();
    transCube->translation(1.0,0.0,0.0);

    Matrix4f * transRow=new Matrix4f();
    transRow->translation(0.0,0.0,-1.0);

    Matrix4f * matrixt=new Matrix4f();
    matrixt->rotation(90,0.0,1.0,0.0);

    //Materials
    Material * materialGrass=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/cubeGrass.png");
    Material * materialSand=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/cubeSand.png");

    NodeSceneGraph * cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleCube);
    cubeNode->add(static_cast<Object3D*>(new ObjectScene(aObject)));

    NodeSceneGraph * obsNode=new NodeSceneGraph();
    obsNode->add(materialSand);
    obsNode->add(transObsCube);
    obsNode->add(static_cast<Object3D*>(cubeNode));
    obsNode->add(transObsCube);
    obsNode->add(static_cast<Object3D*>(cubeNode));
    obsNode->add(transObsCube);
    obsNode->add(static_cast<Object3D*>(cubeNode));

    NodeSceneGraph * rowCube=new NodeSceneGraph();
    rowCube->add(materialGrass);
    rowCube->add(static_cast<Object3D*>(cubeNode));
    for(int i=0;i<7;i++){
        rowCube->add(transCube);
        rowCube->add(static_cast<Object3D*>(cubeNode));
    }

    NodeSceneGraph * ColumCube=new NodeSceneGraph();
    ColumCube->add(static_cast<Object3D*>(rowCube));
    for(int i=0;i<7;i++){
        ColumCube->add(transRow);
        ColumCube->add(static_cast<Object3D*>(rowCube));
    }


    NodeSceneGraph * gravityNode=new NodeSceneGraph();
    gravityNode->add(transGravityCube);
    gravityNode->add(static_cast<Object3D*>(cubeNode));

    objectStatic.push_back(ColumCube);
    objectStatic.push_back(obsNode);
    objectStatic.push_back(gravityNode);
    //objectDinamic.push_back(root);
}

//**********************************************************************//

RootMap::~RootMap()
{
    //dtor
}

//**********************************************************************//

void RootMap::setHero(Hero * theHero){
    hero=theHero;
    hero->setMap(this);
}

//**********************************************************************//

void RootMap::visualization(Context & cv){

    list<Object3D *>::iterator it;

    //Draw the static object
    for(it=objectStatic.begin();it!=objectStatic.end();it++){
        (*it)->visualization(cv);
    }

    //Make the colission map
    if(object.size()==0){
        //Initialization
        list<float> aux;
        vector<list<float> > auxVec;
        for(int j=0;j<11;j++){
                auxVec.push_back(aux);
        }

        for(int i=0;i<11;i++){
            object.push_back(auxVec);
        }

        vec3f pos;
        //Push all the positions
        for(int i=0;i<cv.posObject.size();i++){
            pos=cv.posObject[i];
            object[pos.x][(pos.z*(-1))].push_back(pos.y);
            cout<< "Position -> x: "<< pos.x<< " y: "<< pos.y<< " z: "<< pos.z<< endl;
        }

    }

    //Draw hero
    hero->visualization(cv);

    vec3f positionHero=hero->getPosition();
}

//**********************************************************************//

void RootMap::updateState(float time){

}

//**********************************************************************//

bool RootMap::collision(const vec3f & indexObj, const vec3f & dynamicObj){
    bool result=false;
    int tam=object[(int)indexObj.x][(int)indexObj.z*-1].size();

    list<float>::iterator it=object[(int)indexObj.x][(int)indexObj.z*-1].begin();
    list<float>::iterator endIt=object[(int)indexObj.x][(int)indexObj.z*-1].end();

    if(tam!=0 && ((dynamicObj.x+0.5 >= indexObj.x-0.5 && dynamicObj.x+0.5 <= indexObj.x+0.5 )||(dynamicObj.x-0.5 >= indexObj.x-0.5 && dynamicObj.x-0.5 <= indexObj.x+0.5))
       &&((-dynamicObj.z+0.5 >= -indexObj.z-0.5 && -dynamicObj.z+0.5 <= -indexObj.z+0.5 )||(-dynamicObj.z-0.5 >= -indexObj.z-0.5 && -dynamicObj.z-0.5 <= -indexObj.z+0.5))){
        for(;it!=endIt && !result;it++){
            if((dynamicObj.y+0.5 > (*it)-0.5 && dynamicObj.y+0.5 < (*it)+0.5 )||(dynamicObj.y-0.5 > (*it)-0.5 && dynamicObj.y-0.5 < (*it)+0.5))
                result=true;
        }
    }

    return result;
}

