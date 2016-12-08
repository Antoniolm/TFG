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
#include "../VideoGame/npclist.h"

RootMap::RootMap()
{
    cout<< "< Game is loading our current map >"<< endl;

    Mesh * cubeObject=new Mesh("geometries/cube.obj");
    cubeObject->init();

    Mesh * fenceObject=new Mesh("geometries/fence.obj");
    fenceObject->init();

    Mesh * treeObject=new Mesh("geometries/tree.obj");
    treeObject->init();

    Mesh * grassObject=new Mesh("geometries/grass.obj");
    grassObject->init();

    Mesh * mushRoomObject=new Mesh("geometries/mushroomWhite.obj");
    mushRoomObject->init();

    Mesh * treeDieObject=new Mesh("geometries/treeDie.obj");
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
    //Material * materialBox=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/cubeBox.png");
    Material * materialFence=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/Wood.png");
    Material * materialMushroom=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/mushrooms.png");
    Material * materialTree=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/grass.png");
    Material * materialWater=new Material(vec3f(0.5f, 0.5f, 1.0f),vec3f(0.5f, 0.5f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/water.png");
    Material * materialVoid=new Material(vec3f(0.5f, 0.5f, 1.0f),vec3f(0.5f, 0.5f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/void.png");

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

            cubeNode->add(cubeObject);
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
        cubeNode->add(cubeObject);
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
            cubeNode->add(cubeObject);
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
            cubeNode->add(cubeObject);
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
            cubeNode->add(cubeObject);
            objs.push_back(new ObjectScene(cubeNode));
        }
    }

    transOneCube=new Matrix4f();
    transOneCube->translation(13.5f,-2.5f,-3.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleWater);
    cubeNode->add(materialWater);
    cubeNode->add(cubeObject);
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
            cubeNode->add(fenceObject);
            objs.push_back(new ObjectScene(cubeNode));
        }
    }

    transOneCube=new Matrix4f();
    transOneCube->translation(1.5f,2.0f,-6.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleTree);
    cubeNode->add(materialTree);
    cubeNode->add(treeObject);
    objs.push_back(new ObjectScene(cubeNode));

    transOneCube=new Matrix4f();
    transOneCube->translation(4.5f,1.3f,-6.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleTreeDie);
    cubeNode->add(materialMushroom);
    cubeNode->add(treeDieObject);
    objs.push_back(new ObjectScene(cubeNode));

    transOneCube=new Matrix4f();
    transOneCube->translation(2.1f,1.2f,-0.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(materialTree);
    cubeNode->add(grassObject);
    decorationObjs.push_back(new ObjectScene(cubeNode));

    transOneCube=new Matrix4f();
    transOneCube->translation(0.5f,1.0f,-0.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleCube);
    cubeNode->add(materialMushroom);
    cubeNode->add(mushRoomObject);
    decorationObjs.push_back(new ObjectScene(cubeNode));

    transOneCube=new Matrix4f();
    transOneCube->translation(6.0f,1.5f,-2.0f);
    scaleCube =new Matrix4f();
    scaleCube->scale(1.0,0.5,1.0);

    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleCube);
    cubeNode->add(materialSand);
    cubeNode->add(cubeObject);
    objs.push_back(new ObjectScene(cubeNode));

    /////////////////////////////////////////
    // Add npcs of our map
    npcList=new NpcList();

    Npc * npc1=new Npc(vec3f(3.5,2.0,-3.5f));
    npc1->addDialog("Esto es una prueba",NPC_DIALOG);
    npc1->addDialog("Segundo mensaje de prueba",HERO_DIALOG);
    npc1->addDialog("Tercer mensaje de prueba",HERO_DIALOG);
    npcList->add(npc1);

    transOneCube=new Matrix4f();
    transOneCube->translation(3.5,2.0,-3.5f);
    scaleCube =new Matrix4f();
    scaleCube->scale(0.5,1,0.5);

    //Added to our indexMap for collision with our hero
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleCube);
    cubeNode->add(materialVoid);
    cubeNode->add(cubeObject);
    objs.push_back(new ObjectScene(cubeNode));

    Npc * npc2=new Npc(vec3f(0.5,2.0,-3.5f));
    npc2->addDialog("Segundo Npc",HERO_DIALOG);
    npc2->addDialog("Segundo mensaje de Npc2",NPC_DIALOG);
    npcList->add(npc2);

    //Added to our indexMap for collision with our hero
    transOneCube=new Matrix4f();
    transOneCube->translation(0.5,2.0,-3.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleCube);
    cubeNode->add(materialVoid);
    cubeNode->add(cubeObject);
    objs.push_back(new ObjectScene(cubeNode));

    Npc * npc3=new Npc(vec3f(10.5,0.0,-3.5f));
    npc3->addDialog("Hola este es el rio",NPC_DIALOG);
    npc3->addDialog("Y esto es otra prueba",NPC_DIALOG);
    npcList->add(npc3);

    //Added to our indexMap for collision with our hero
    transOneCube=new Matrix4f();
    transOneCube->translation(10.5,0.0,-3.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleCube);
    cubeNode->add(materialVoid);
    cubeNode->add(cubeObject);
    objs.push_back(new ObjectScene(cubeNode));

    ////////////////////////////////////////
    //Create the indexMap;

    Context cv;
    cv.visualization_mode=1;
    for(unsigned i=0;i<objs.size();i++){
        objs[i]->visualization(cv);
    }

    vec3f pos;
    BoundingBox bounding;

    //Push all the positions
    for(unsigned i=0;i<objs.size();i++){
        pos=objs[i]->getPosition();
        bounding=objs[i]->getBoundingBox();
        bounding.minValue.z+=0.1;

        for(int x=bounding.minValue.x;x<bounding.maxValue.x;x++){
            for(int z=bounding.minValue.z;z<bounding.maxValue.z;z++){
                indexMap[(int)(pos.x+x)][(int)((pos.z+z)*(-1))].push_back(i);
            }
        }
    }

    /////////////////////////////////////////
    // Add sound of our map
    backSound=new Sound("sounds/background.wav",0,60);
    //backSound->play();

    currentTime=SDL_GetTicks();
}

//**********************************************************************//

RootMap::~RootMap()
{
    delete(backSound);
    delete hero;

    for(unsigned i=0;i<objs.size();i++)
        delete objs[i];

    for(unsigned i=0;i<decorationObjs.size();i++)
        delete decorationObjs[i];
}

//**********************************************************************//

void RootMap::setHero(Hero * theHero){
    hero=theHero;
    hero->setMap(this);
}

//**********************************************************************//

Hero * RootMap::getHero(){
    return hero;
}

//**********************************************************************//

void RootMap::visualization(Context & cv){
    //Draw object
    for(unsigned i=0;i<objs.size();i++){
        objs[i]->visualization(cv);
    }

    //Draw hero
    hero->visualization(cv);

    //Draw decoration object
    for(unsigned i=0;i<decorationObjs.size();i++){
        decorationObjs[i]->visualization(cv);
    }

    npcList->visualization(cv);
}

//**********************************************************************//

void RootMap::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap  ){
    //Update the hero
    hero->updateState(time,currentKeyStates,rootMap);

    //Update the Scene
    for(unsigned i=0;i<objs.size();i++)
        objs[i]->updateState(time,currentKeyStates,rootMap);

    npcList->updateState(time,currentKeyStates,rootMap);
    currentTime+=time-currentTime;
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
