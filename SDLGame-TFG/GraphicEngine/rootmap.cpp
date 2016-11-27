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

RootMap::RootMap(Hero * aHero)
{
    cout<< "< Game is loading our current map >"<< endl;
    setHero(aHero);

    string file("geometries/cube.obj");
    Mesh * cubeObject=new Mesh(file);
    cubeObject->init();

    file="geometries/Cliff_low.obj";
    Mesh * rockObject=new Mesh(file);
    rockObject->init();

    file="geometries/fence.obj";
    Mesh * fenceObject=new Mesh(file);
    fenceObject->init();

    Matrix4f *scaleFence =new Matrix4f();
    scaleFence->scale(0.5,0.5,0.5);

    Matrix4f *scaleCube =new Matrix4f();
    scaleCube->scale(0.5,0.5,0.5);

    Matrix4f * transOneCube=new Matrix4f();
    transOneCube->translation(0.5,0.5,-0.5);

    Matrix4f * scaleRock=new Matrix4f();
    scaleRock->scale(0.02,0.02,0.02);

    Matrix4f * transRock=new Matrix4f();
    transRock->translation(4.5,1.5,-1.5);

    Matrix4f * transCube=new Matrix4f();
    transCube->translation(1.0,0.0,0.0);

    //Materials
    Material * materialGrass=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/cubeGrass.png");
    Material * materialSand=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/cubeSand.png");
    Material * materialBox=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/cubeBox.png");
    Material * materialRock=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/rock.png");
    Material * materialFence=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/Wood.png");

    NodeSceneGraph * cubeNode=new NodeSceneGraph();

    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            transOneCube=new Matrix4f();
            transOneCube->translation(i+0.5f,0.5f,-j-0.5f);
            cubeNode=new NodeSceneGraph();
            cubeNode->add(transOneCube);
            cubeNode->add(scaleCube);
            cubeNode->add(materialGrass);
            cubeNode->add(static_cast<Object3D*>(new ObjectScene(cubeObject)));
            objs.push_back(new ObjectScene(cubeNode));
        }
    }
    for(int i=0;i<7;i++){
        transOneCube=new Matrix4f();
        transOneCube->translation(i+0.5f,1.5f,-4.5f);
        cubeNode=new NodeSceneGraph();
        cubeNode->add(transOneCube);
        cubeNode->add(scaleFence);
        cubeNode->add(materialFence);
        cubeNode->add(static_cast<Object3D*>(new ObjectScene(fenceObject)));
        objs.push_back(new ObjectScene(cubeNode));
    }

    transOneCube=new Matrix4f();
    transOneCube->translation(2.5f,1.5f,-0.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleCube);
    cubeNode->add(materialBox);
    cubeNode->add(static_cast<Object3D*>(new ObjectScene(cubeObject)));
    objs.push_back(new ObjectScene(cubeNode));

    transOneCube=new Matrix4f();
    transOneCube->translation(3.5f,3.5f,-5.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleCube);
    cubeNode->add(materialSand);
    cubeNode->add(static_cast<Object3D*>(new ObjectScene(cubeObject)));
    objs.push_back(new ObjectScene(cubeNode));

    transOneCube=new Matrix4f();
    transOneCube->translation(1.5f,1.5f,-1.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleCube);
    cubeNode->add(materialBox);
    cubeNode->add(static_cast<Object3D*>(new ObjectScene(cubeObject)));
    objs.push_back(new ObjectScene(cubeNode));

    NodeSceneGraph * rockNode=new NodeSceneGraph();
    rockNode->add(transRock);
    rockNode->add(scaleRock);
    rockNode->add(materialRock);
    rockNode->add(static_cast<Object3D*>(new ObjectScene(rockObject)));
    objs.push_back(new ObjectScene(rockNode));

    //visualization;
    Context cv;
    cv.visualization_mode=1;
    visualization(cv);

    vec3f pos;

    //Push all the positions
    int cont=0;
    for(int i=1;i<cv.posObject.size();i+=2){
        pos=cv.posObject[i];
        objs[cont]->setPosition(pos);
        indexMap[(int)pos.x][(int)(pos.z*(-1))].push_back(cont);
        cont++;
    }
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

    //Draw object
    for(int i=0;i<objs.size();i++){
        objs[i]->visualization(cv);
    }

    //Draw hero
    hero->updateState(SDL_GetTicks());
    hero->visualization(cv);
}

//**********************************************************************//

void RootMap::updateState(float time){
    for(int i=0;i<objs.size();i++)
        objs[i]->updateState(time);
    hero->updateState(time);
}

//**********************************************************************//

ObjectScene * RootMap::collision(const vec3f & indexObj){
    bool hasCollision=false;
    ObjectScene * result=0;
    int tam=indexMap[(int)indexObj.x][(int)indexObj.z*-1].size();

    vector<int>::iterator it=indexMap[(int)indexObj.x][(int)indexObj.z*-1].begin();
    vector<int>::iterator endIt=indexMap[(int)indexObj.x][(int)indexObj.z*-1].end();

    if(tam!=0 ){
        for(;it!=endIt && !hasCollision;it++){
            vec3f pos=objs[(*it)]->getPosition();
            if((indexObj.y+0.5 > (pos.y)-0.5 && indexObj.y+0.5 < (pos.y)+0.5 )||(indexObj.y-0.5 > (pos.y)-0.5 && indexObj.y-0.5 < (pos.y)+0.5)){
                hasCollision=true;
                result=objs[(*it)];
            }
        }
    }

    return result;
}

