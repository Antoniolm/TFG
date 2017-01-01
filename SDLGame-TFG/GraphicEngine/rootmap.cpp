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

    Matrix4f *scaleCube =new Matrix4f();
    scaleCube->scale(0.5,0.5,0.5);

    Matrix4f * transOneCube=new Matrix4f();
    transOneCube->translation(0.5,0.5,-0.5);

    NodeSceneGraph * cubeNode=new NodeSceneGraph();
    const rapidjson::Value & voxelGroup=document["voxelGroup"];
    int tamX,tamY,tamZ,initialX,initialZ;
    float initialY;

    //Bucle -> voxelGroup
    for(int currentGroup=0;currentGroup<voxelGroup.Size();currentGroup++){
        //For each group
        tamX=voxelGroup[currentGroup]["XNumber"].GetInt();
        tamY=voxelGroup[currentGroup]["YNumber"].GetInt();
        tamZ=voxelGroup[currentGroup]["ZNumber"].GetInt();
        initialX=voxelGroup[currentGroup]["position"][0].GetFloat();
        initialY=voxelGroup[currentGroup]["position"][1].GetFloat();
        initialZ=-voxelGroup[currentGroup]["position"][2].GetFloat();

        for(int x=0;x<tamX;x++){
            for(int z=0;z<tamZ;z++){
                for(int y=0;y<tamY;y++){
                    transOneCube=new Matrix4f();
                    transOneCube->translation(initialX+x+0.5f,initialY-y,initialZ-z-0.5f);
                    cubeNode=new NodeSceneGraph();
                    cubeNode->add(transOneCube);
                    cubeNode->add(scaleCube);
                    if(y==0)
                    cubeNode->add(materialCollect->getMaterial(voxelGroup[currentGroup]["materialTop"].GetString()));
                    else
                    cubeNode->add(materialCollect->getMaterial(voxelGroup[currentGroup]["materialMiddle"].GetString()));
                    cubeNode->add(meshCollect->getMesh(voxelGroup[currentGroup]["mesh"].GetString()));
                    objs.push_back(new ObjectScene(cubeNode,voxelGroup[currentGroup]["damage"].GetFloat()));
                }
            }
        }
    }

    Matrix4f * transformation;
    const rapidjson::Value & decoObject=document["decorationObject"];
    for(int currentDeco=0;currentDeco<decoObject.Size();currentDeco++){

        cubeNode=new NodeSceneGraph();

        for(int currentTrans=0;currentTrans<decoObject[currentDeco]["transforms"].Size();currentTrans++){
            transformation=new Matrix4f();
            if(decoObject[currentDeco]["transforms"][currentTrans]["translation"].GetBool()){ //If is a translation

                transformation->translation(decoObject[currentDeco]["transforms"][currentTrans]["values"][0].GetFloat(),
                                            decoObject[currentDeco]["transforms"][currentTrans]["values"][1].GetFloat(),
                                            decoObject[currentDeco]["transforms"][currentTrans]["values"][2].GetFloat());

            }
            else if(decoObject[currentDeco]["transforms"][currentTrans]["scale"].GetBool()){ //If is a scale

                transformation->scale(decoObject[currentDeco]["transforms"][currentTrans]["values"][0].GetFloat(),
                                      decoObject[currentDeco]["transforms"][currentTrans]["values"][1].GetFloat(),
                                      decoObject[currentDeco]["transforms"][currentTrans]["values"][2].GetFloat());

            }
            else if(decoObject[currentDeco]["transforms"][currentTrans]["rotation"].GetBool()){ //If is a rotation

                transformation->rotation(decoObject[currentDeco]["transforms"][currentTrans]["values"][0].GetFloat(),
                                         decoObject[currentDeco]["transforms"][currentTrans]["values"][1].GetFloat(),
                                         decoObject[currentDeco]["transforms"][currentTrans]["values"][2].GetFloat(),
                                         decoObject[currentDeco]["transforms"][currentTrans]["values"][3].GetFloat());

            }
            cubeNode->add(transformation);

        }

        cubeNode->add(materialCollect->getMaterial(decoObject[currentDeco]["material"].GetString()));
        cubeNode->add(meshCollect->getMesh(decoObject[currentDeco]["mesh"].GetString()));

        if(decoObject[currentDeco]["collision"].GetBool()) //If collision
            objs.push_back(new ObjectScene(cubeNode));
        else{ //If is a decoration obj
            decorationObjs.push_back(new ObjectScene(cubeNode));
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
    cubeNode->add(materialCollect->getMaterial(document["bkgdMaterial"].GetString()));
    cubeNode->add(meshCollect->getMesh(BACKGROUND));
    background= new ObjectScene(cubeNode);

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
    npcList=new NpcList(npcsValue,objs);

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
    backSound=new Sound(document["sound"].GetString(),0,document["volSound"].GetFloat());
    backSound->play();

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
