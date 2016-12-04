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
    cout<< "< Game is loading our current map >"<< endl;

    string file("geometries/cube.obj");
    Mesh * cubeObject=new Mesh(file);
    cubeObject->init();

    file="geometries/fence.obj";
    Mesh * fenceObject=new Mesh(file);
    fenceObject->init();

    file="geometries/tree.obj";
    Mesh * treeObject=new Mesh(file);
    treeObject->init();

    file="geometries/grass.obj";
    Mesh * grassObject=new Mesh(file);
    grassObject->init();

    file="geometries/mushroomWhite.obj";
    Mesh * mushRoomObject=new Mesh(file);
    mushRoomObject->init();

    file="geometries/treeDie.obj";
    Mesh * treeDieObject=new Mesh(file);
    treeDieObject->init();

    Matrix4f *scaleTreeDie =new Matrix4f();
    scaleTreeDie->scale(0.6,0.5,0.5);

    Matrix4f *scaleCube =new Matrix4f();
    scaleCube->scale(0.5,0.5,0.5);

    Matrix4f *scaleTree =new Matrix4f();
    scaleTree->scale(0.3,0.5,0.3);

    Matrix4f *scaleWater =new Matrix4f();
    scaleWater->scale(3.5,0.5,3.5);

    Matrix4f *scaleGrass =new Matrix4f();
    scaleGrass->scale(0.7,0.7,0.7);

    Matrix4f * transOneCube=new Matrix4f();
    transOneCube->translation(0.5,0.5,-0.5);

    Matrix4f * scaleRock=new Matrix4f();
    scaleRock->scale(0.02,0.02,0.02);

    Matrix4f * transRock=new Matrix4f();
    transRock->translation(4.5,1.5,-1.5);

    Matrix4f * transCube=new Matrix4f();
    transCube->translation(1.0,0.0,0.0);

    //Materials
    Material * materialGrass=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/cubeGrass.png");
    Material * materialSand=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/cubeSand.png");
    Material * materialBox=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/cubeBox.png");
    Material * materialRock=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/rock.png");
    Material * materialFence=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/Wood.png");
    Material * materialMushroom=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/mushrooms.png");
    Material * materialTree=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/grass.png");
    Material * materialWater=new Material(vec3f(0.5f, 0.5f, 1.0f),vec3f(0.5f, 0.5f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/water.png");

    NodeSceneGraph * cubeNode=new NodeSceneGraph();

    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            transOneCube=new Matrix4f();
            transOneCube->translation(i+0.5f,0.5f,-j-0.5f);
            cubeNode=new NodeSceneGraph();
            cubeNode->add(transOneCube);
            cubeNode->add(scaleCube);
            if(j>0 && j<5)
                cubeNode->add(materialSand);
            else
                cubeNode->add(materialGrass);

            cubeNode->add(static_cast<Object3D*>(cubeObject));
            objs.push_back(new ObjectScene(cubeNode));
        }
    }
    for(int j=0;j<7;j++){
        transOneCube=new Matrix4f();
        transOneCube->translation(7.5f,-0.5f,-j-0.5f);
        cubeNode=new NodeSceneGraph();
        cubeNode->add(transOneCube);
        cubeNode->add(scaleCube);
        cubeNode->add(materialGrass);
        cubeNode->add(static_cast<Object3D*>(cubeObject));
        objs.push_back(new ObjectScene(cubeNode));
    }

    for(int i=0;i<2;i++){
        for(int j=0;j<7;j++){
            transOneCube=new Matrix4f();
            transOneCube->translation(i+8.5f,-1.5f,-j-0.5f);
            cubeNode=new NodeSceneGraph();
            cubeNode->add(transOneCube);
            cubeNode->add(scaleCube);
            cubeNode->add(materialGrass);
            cubeNode->add(static_cast<Object3D*>(cubeObject));
            objs.push_back(new ObjectScene(cubeNode));
        }
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<2;j++){
            transOneCube=new Matrix4f();
            transOneCube->translation(i+10.5f,-1.5f,-j-2.5f);
            cubeNode=new NodeSceneGraph();
            cubeNode->add(transOneCube);
            cubeNode->add(scaleCube);
            cubeNode->add(materialGrass);
            cubeNode->add(static_cast<Object3D*>(cubeObject));
            objs.push_back(new ObjectScene(cubeNode));
        }
    }


    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            transOneCube=new Matrix4f();
            transOneCube->translation(i+10.5f,-3.5f,-j-0.5f);
            cubeNode=new NodeSceneGraph();
            cubeNode->add(transOneCube);
            cubeNode->add(scaleCube);
            cubeNode->add(materialGrass);
            cubeNode->add(static_cast<Object3D*>(cubeObject));
            objs.push_back(new ObjectScene(cubeNode));
        }
    }

    transOneCube=new Matrix4f();
    transOneCube->translation(13.5f,-2.5f,-3.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleWater);
    cubeNode->add(materialWater);
    cubeNode->add(static_cast<Object3D*>(cubeObject));
    decorationObjs.push_back(new ObjectScene(cubeNode));


    float scale=-1.5;
    for(int i=0;i<2;i++){
        if(i==1) scale=-5.5;
        for(int j=0;j<7;j++){
            transOneCube=new Matrix4f();
            transOneCube->translation(j+0.5f,1.5f,scale);
            cubeNode=new NodeSceneGraph();
            cubeNode->add(transOneCube);
            cubeNode->add(scaleCube);
            cubeNode->add(materialFence);
            cubeNode->add(static_cast<Object3D*>(fenceObject));
            objs.push_back(new ObjectScene(cubeNode));
        }
    }

    transOneCube=new Matrix4f();
    transOneCube->translation(1.5f,2.0f,-6.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleTree);
    cubeNode->add(materialTree);
    cubeNode->add(static_cast<Object3D*>(treeObject));
    objs.push_back(new ObjectScene(cubeNode));

    transOneCube=new Matrix4f();
    transOneCube->translation(4.5f,1.3f,-6.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleTreeDie);
    cubeNode->add(materialMushroom);
    cubeNode->add(static_cast<Object3D*>(treeDieObject));
    objs.push_back(new ObjectScene(cubeNode));

    transOneCube=new Matrix4f();
    transOneCube->translation(2.1f,1.2f,-0.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(materialTree);
    cubeNode->add(static_cast<Object3D*>(grassObject));
    decorationObjs.push_back(new ObjectScene(cubeNode));

    transOneCube=new Matrix4f();
    transOneCube->translation(0.5f,1.0f,-0.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleCube);
    cubeNode->add(materialMushroom);
    cubeNode->add(static_cast<Object3D*>(mushRoomObject));
    decorationObjs.push_back(new ObjectScene(cubeNode));

    transOneCube=new Matrix4f();
    transOneCube->translation(3.5f,3.5f,-5.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleCube);
    cubeNode->add(materialSand);
    cubeNode->add(static_cast<Object3D*>(cubeObject));
    objs.push_back(new ObjectScene(cubeNode));

    //visualization;
    Context cv;
    cv.visualization_mode=1;
    for(int i=0;i<objs.size();i++){
        objs[i]->visualization(cv);
    }

    vec3f pos;
    BoundingBox bounding;

    //Push all the positions
    for(int i=0;i<objs.size();i++){
        pos=objs[i]->getPosition();
        bounding=objs[i]->getBoundingBox();

        for(int x=bounding.minValue.x;x<bounding.maxValue.x;x++){
            for(int z=bounding.minValue.z;z<bounding.maxValue.z;z++){
                indexMap[(int)(pos.x+x)][(int)((pos.z+z)*(-1))].push_back(i);
            }
        }
    }


    /////////////////////////////////////////
    // Add sound of our map
    backSound=new Sound("sounds/background.wav",0,60);
    backSound->play();
}

//**********************************************************************//

RootMap::~RootMap()
{
    delete(backSound);
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
    hero->visualization(cv);

    //Draw decoration object
    for(int i=0;i<decorationObjs.size();i++){
        decorationObjs[i]->visualization(cv);
    }
}

//**********************************************************************//

void RootMap::updateState(float time){

    //Update the hero
    hero->updateState(time);

    //Update the Scene
    for(int i=0;i<objs.size();i++)
        objs[i]->updateState(time);
}

//**********************************************************************//

ObjectScene * RootMap::collision(const vec3f & indexObj){
    bool hasCollision=false;
    ObjectScene * result=0;
    vec3f pos;
    BoundingBox box;
    int tam=indexMap[(int)indexObj.x][(int)indexObj.z*-1].size();

    vector<int>::iterator it=indexMap[(int)indexObj.x][(int)indexObj.z*-1].begin();
    vector<int>::iterator endIt=indexMap[(int)indexObj.x][(int)indexObj.z*-1].end();

    if(tam!=0 ){
        for(;it!=endIt && !hasCollision;it++){
            pos=objs[(*it)]->getPosition();
            box=objs[(*it)]->getBoundingBox();
            if((indexObj.y+0.5 > (pos.y)+box.minValue.y && indexObj.y+0.5 < (pos.y)+box.maxValue.y)||(indexObj.y-0.5 > (pos.y)+box.minValue.y && indexObj.y-0.5 < (pos.y)+box.maxValue.y)){
                hasCollision=true;
                result=objs[(*it)];
            }
        }
    }

    return result;
}

