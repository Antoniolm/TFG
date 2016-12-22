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
#include "../VideoGame/npclist.h"
#include "../VideoGame/enemylist.h"
#include <stdlib.h>     /* srand, rand */
RootMap::RootMap(){
}

//**********************************************************************//

RootMap::RootMap(const rapidjson::Document & document)
{
    cout<< "< Game is loading our current map >"<< endl;

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

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

    NodeSceneGraph * cubeNode=new NodeSceneGraph();

    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            transOneCube=new Matrix4f();
            transOneCube->translation(i+0.5f,0.5f,-j-0.5f);
            cubeNode=new NodeSceneGraph();
            cubeNode->add(transOneCube);
            cubeNode->add(scaleCube);
            if(j>0 && j<5)
                cubeNode->add(materialCollect->getMaterial(mCUBE_SAND));
            else
                cubeNode->add(materialCollect->getMaterial(mCUBE_GRASS));

            cubeNode->add(meshCollect->getMesh(CUBE));
            objs.push_back(new ObjectScene(cubeNode));
        }
    }
    for(int j=0;j<7;j++){
        transOneCube=new Matrix4f();
        transOneCube->translation(7.5f,-0.5f,-j-0.5f);
        cubeNode=new NodeSceneGraph();
        cubeNode->add(transOneCube);
        cubeNode->add(scaleCube);
        cubeNode->add(materialCollect->getMaterial(mCUBE_GRASS));
        cubeNode->add(meshCollect->getMesh(CUBE));
        objs.push_back(new ObjectScene(cubeNode));
    }

    for(int i=0;i<2;i++){
        for(int j=0;j<7;j++){
            transOneCube=new Matrix4f();
            transOneCube->translation(i+8.5f,-1.5f,-j-0.5f);
            cubeNode=new NodeSceneGraph();
            cubeNode->add(transOneCube);
            cubeNode->add(scaleCube);
            cubeNode->add(materialCollect->getMaterial(mCUBE_GRASS));
            cubeNode->add(meshCollect->getMesh(CUBE));
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
            cubeNode->add(materialCollect->getMaterial(mCUBE_GRASS));
            cubeNode->add(meshCollect->getMesh(CUBE));
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
            cubeNode->add(materialCollect->getMaterial(mCUBE_GRASS));
            cubeNode->add(meshCollect->getMesh(CUBE));
            objs.push_back(new ObjectScene(cubeNode,-10.0));
        }
    }

    transOneCube=new Matrix4f();
    transOneCube->translation(13.5f,-2.5f,-3.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleWater);
    cubeNode->add(materialCollect->getMaterial(mWATER));
    cubeNode->add(meshCollect->getMesh(CUBE));
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
            cubeNode->add(materialCollect->getMaterial(mWOOD));
            cubeNode->add(meshCollect->getMesh(FENCE));
            objs.push_back(new ObjectScene(cubeNode));
        }
    }

    ////////////////////////////////////////////
    // Background
    transOneCube=new Matrix4f();
    transOneCube->translation(0.0f,0.0f,0.0f);
    Matrix4f *scaleBack =new Matrix4f();
    scaleBack->scale(10.0,10.0,10.0);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleBack);
    cubeNode->add(materialCollect->getMaterial(mWATER));
    cubeNode->add(meshCollect->getMesh(BACKGROUND));
    background= new ObjectScene(cubeNode);

    transOneCube=new Matrix4f();
    transOneCube->translation(1.5f,2.0f,-6.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleTree);
    cubeNode->add(materialCollect->getMaterial(mGRASS));
    cubeNode->add(meshCollect->getMesh(TREE));
    objs.push_back(new ObjectScene(cubeNode));

    transOneCube=new Matrix4f();
    transOneCube->translation(4.5f,1.3f,-6.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleTreeDie);
    cubeNode->add(materialCollect->getMaterial(MUSH));
    cubeNode->add(meshCollect->getMesh(TREEDIE));
    objs.push_back(new ObjectScene(cubeNode));

    transOneCube=new Matrix4f();
    transOneCube->translation(2.1f,1.2f,-0.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(materialCollect->getMaterial(mGRASS));
    cubeNode->add(meshCollect->getMesh(GRASS));
    decorationObjs.push_back(new ObjectScene(cubeNode));

    transOneCube=new Matrix4f();
    transOneCube->translation(0.5f,1.0f,-0.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleCube);
    cubeNode->add(materialCollect->getMaterial(MUSH));
    cubeNode->add(meshCollect->getMesh(MUSHWHITE));
    decorationObjs.push_back(new ObjectScene(cubeNode));

    transOneCube=new Matrix4f();
    transOneCube->translation(6.0f,1.5f,-3.0f);
    scaleCube =new Matrix4f();
    scaleCube->scale(1.0,0.5,1.0);

    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleCube);
    cubeNode->add(materialCollect->getMaterial(mCUBE_SAND));
    cubeNode->add(meshCollect->getMesh(CUBE));
    objs.push_back(new ObjectScene(cubeNode));
    /////////////////////////////////////////
    // Add coins to our map
    /////////////////////////////////////////
    const rapidjson::Value & coinValue=document["coins"];
    for(int i=0;i<coinValue.Size();i++){
        coins.push_back(new Coin(vec3f(coinValue[i]["position"][0].GetFloat(),coinValue[i]["position"][1].GetFloat(),coinValue[i]["position"][2].GetFloat()),
                                 coinValue[i]["value"].GetInt()));
    }


    /////////////////////////////////////////
    // Add npcs of our map
    /////////////////////////////////////////
    const rapidjson::Value & npcsValue=document["npcs"];
    npcList=new NpcList(npcsValue);

    //Added to our indexMap for collision with our hero
    transOneCube=new Matrix4f();
    transOneCube->translation(3.5,2.0,-2.5f);
    scaleCube =new Matrix4f();
    scaleCube->scale(0.5,1,0.5);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleCube);
    cubeNode->add(materialCollect->getMaterial(mVOID));
    cubeNode->add(meshCollect->getMesh(CUBE));
    objs.push_back(new ObjectScene(cubeNode));

    //Added to our indexMap for collision with our hero
    transOneCube=new Matrix4f();
    transOneCube->translation(0.5,2.0,-3.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleCube);
    cubeNode->add(materialCollect->getMaterial(mVOID));
    cubeNode->add(meshCollect->getMesh(CUBE));
    objs.push_back(new ObjectScene(cubeNode));

    //Added to our indexMap for collision with our hero
    transOneCube=new Matrix4f();
    transOneCube->translation(10.5,0.0,-3.5f);
    cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleCube);
    cubeNode->add(materialCollect->getMaterial(mVOID));
    cubeNode->add(meshCollect->getMesh(CUBE));
    objs.push_back(new ObjectScene(cubeNode));

    /////////////////////////////////////////
    // Add enemy of our map
    const rapidjson::Value & enemies=document["enemies"];

    enemyList=new EnemyList(enemies);

    ////////////////////////////////////////
    //Create the indexMap;

    Context cv;
    cv.visualization_mode=1;
    for(unsigned i=0;i<objs.size();i++){
        objs[i]->visualization(cv);
    }

    for(unsigned i=0;i<decorationObjs.size();i++){
        decorationObjs[i]->visualization(cv);
    }

    vec3f pos;
    BoundingBox bounding;

    //Create our indexMap for our collision system
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
    delete backSound;
    delete npcList;
    delete enemyList;

    for(unsigned i=0;i<objs.size();i++)
        delete objs[i];

    for(unsigned i=0;i<decorationObjs.size();i++)
        delete decorationObjs[i];
}

//**********************************************************************//

void RootMap::setHero(Hero * theHero){
    hero=theHero;
}

//**********************************************************************//

Hero * RootMap::getHero(){
    return hero;
}

//**********************************************************************//

void RootMap::visualization(Context & cv){
    vec3f position,posHero=hero->getPosition();
    //Draw background
    background->visualization(cv);

    //Draw object
    for(unsigned i=0;i<objs.size();i++){
        position=objs[i]->getPosition();
        if(position.x>posHero.x-8 && position.x<posHero.x+8)
            objs[i]->visualization(cv);
    }

    //Draw hero
    hero->visualization(cv);

    //Draw ncps
    npcList->visualization(cv);

    //Draw enemies
    enemyList->visualization(cv);

    //Draw decoration object
    for(unsigned i=0;i<decorationObjs.size();i++){
        position=decorationObjs[i]->getPosition();
        if(position.x>posHero.x-8 && position.x<posHero.x+8)
        decorationObjs[i]->visualization(cv);
    }

    //Draw coins
    for(unsigned i=0;i<coins.size();i++){
        coins[i]->visualization(cv);
    }
}

//**********************************************************************//

void RootMap::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap){
    if(time-currentTime>200)
        currentTime=time-50;

    //Update the hero
    hero->updateState(time,currentKeyStates,rootMap);

    //Update the Scene
    for(unsigned i=0;i<objs.size();i++)
        objs[i]->updateState(time,currentKeyStates,rootMap);

    //Update the Scene
    vector<Coin*>::iterator it=coins.begin();
    while(it!=coins.end()){
        (*it)->updateState(time,currentKeyStates,rootMap);
        if((*it)->isTake())
            coins.erase(it);
        else
            it++;

    }

    npcList->updateState(time,currentKeyStates,rootMap);
    enemyList->updateState(time,currentKeyStates,rootMap);
    currentTime+=time-currentTime;
}

//**********************************************************************//

void RootMap::enableSound(bool value){
    if(value)
        backSound->resume();
    else{
        backSound->pause();
    }
    hero->enableSound(value);
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
