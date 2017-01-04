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

RootMap::RootMap(const rapidjson::Document & document,Shader & shader)
{
    cout<< "< Game is loading our current map >"<< endl;

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    Matrix4f * scaleObj=new Matrix4f();
    scaleObj->scale(0.5,0.5,0.5);

    Matrix4f * transObj=new Matrix4f();
    transObj->translation(0.5,0.5,-0.5);

    /////////////////////////////////////////
    // Add Light to our map
    /////////////////////////////////////////
    const rapidjson::Value & lights=document["light"];
    glUniform1i(glGetUniformLocation(shader.getProgram(), "numActivateLight"), lights.Size()-1);
    Light * light;

    for(int currentLight=0;currentLight<lights.Size();currentLight++){
        //Create our light
        if(lights[currentLight]["type"].GetFloat()==0){
            light=new Light(vec3f(lights[currentLight]["position"][0].GetFloat(), lights[currentLight]["position"][1].GetFloat(), lights[currentLight]["position"][2].GetFloat()),
                          vec3f(lights[currentLight]["ambient"][0].GetFloat(), lights[currentLight]["ambient"][1].GetFloat(), lights[currentLight]["ambient"][2].GetFloat()),
                          vec3f(lights[currentLight]["diffuse"][0].GetFloat(), lights[currentLight]["diffuse"][1].GetFloat(), lights[currentLight]["diffuse"][2].GetFloat()),
                          vec3f(lights[currentLight]["specular"][0].GetFloat(), lights[currentLight]["specular"][1].GetFloat(), lights[currentLight]["specular"][2].GetFloat()));
        }
        else{
            light=new Light(vec3f(lights[currentLight]["position"][0].GetFloat(), lights[currentLight]["position"][1].GetFloat(), lights[currentLight]["position"][2].GetFloat()),
                          vec3f(lights[currentLight]["ambient"][0].GetFloat(), lights[currentLight]["ambient"][1].GetFloat(), lights[currentLight]["ambient"][2].GetFloat()),
                          vec3f(lights[currentLight]["diffuse"][0].GetFloat(), lights[currentLight]["diffuse"][1].GetFloat(), lights[currentLight]["diffuse"][2].GetFloat()),
                          vec3f(lights[currentLight]["specular"][0].GetFloat(), lights[currentLight]["specular"][1].GetFloat(), lights[currentLight]["specular"][2].GetFloat()),
                          lights[currentLight]["constant"].GetFloat(),lights[currentLight]["linear"].GetFloat(),lights[currentLight]["quadratic"].GetFloat());
        }
        //Activate our current Light
        light->activate(&shader,std::string(lights[currentLight]["channel"].GetString()));

    }

    /////////////////////////////////////////
    // Add particleSystems to our map
    /////////////////////////////////////////
    ParticleSystem * pSystem;
    const rapidjson::Value & particleSys=document["particleSystem"];
    for(int currentPSys=0;currentPSys<particleSys.Size();currentPSys++){
        pSystem=new ParticleSystem(particleSys[currentPSys]["number"].GetFloat(),
                                   vec3f(particleSys[currentPSys]["minPosition"][0].GetFloat(), particleSys[currentPSys]["minPosition"][1].GetFloat(), particleSys[currentPSys]["minPosition"][2].GetFloat()),
                                   vec3f(particleSys[currentPSys]["maxPosition"][0].GetFloat(), particleSys[currentPSys]["maxPosition"][1].GetFloat(), particleSys[currentPSys]["maxPosition"][2].GetFloat()),
                                   vec3f(particleSys[currentPSys]["velocity"][0].GetFloat(), particleSys[currentPSys]["velocity"][1].GetFloat(), particleSys[currentPSys]["velocity"][2].GetFloat()),
                                   particleSys[currentPSys]["minLife"].GetFloat(),particleSys[currentPSys]["maxLife"].GetFloat());
        particleSystem.push_back(pSystem);
    }

    /////////////////////////////////////////
    // Add voxelGroup to our map
    /////////////////////////////////////////
    NodeSceneGraph * objNode=new NodeSceneGraph();
    const rapidjson::Value & voxelGroup=document["voxelGroup"];
    int tamX,tamY,tamZ,initialX,initialZ;
    float initialY;

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
                    transObj=new Matrix4f();
                    transObj->translation(initialX+x+0.5f,initialY-y,initialZ-z-0.5f);
                    objNode=new NodeSceneGraph();
                    objNode->add(transObj);
                    objNode->add(scaleObj);
                    if(y==0)
                    objNode->add(materialCollect->getMaterial(voxelGroup[currentGroup]["materialTop"].GetString()));
                    else
                    objNode->add(materialCollect->getMaterial(voxelGroup[currentGroup]["materialMiddle"].GetString()));
                    objNode->add(meshCollect->getMesh(voxelGroup[currentGroup]["mesh"].GetString()));
                    objs.push_back(new ObjectScene(objNode,voxelGroup[currentGroup]["damage"].GetFloat()));
                }
            }
        }
    }

    /////////////////////////////////////////
    // Add decorationObject to our map
    /////////////////////////////////////////
    Matrix4f * transformation;
    const rapidjson::Value & decoObject=document["decorationObject"];
    for(int currentDeco=0;currentDeco<decoObject.Size();currentDeco++){

        objNode=new NodeSceneGraph();

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
            objNode->add(transformation);

        }

        objNode->add(materialCollect->getMaterial(decoObject[currentDeco]["material"].GetString()));
        objNode->add(meshCollect->getMesh(decoObject[currentDeco]["mesh"].GetString()));

        if(decoObject[currentDeco]["collision"].GetBool()) //If collision
            objs.push_back(new ObjectScene(objNode));
        else{ //If is a decoration obj
            decorationObjs.push_back(new ObjectScene(objNode));
        }
    }

    ////////////////////////////////////////////
    // Background
    transObj=new Matrix4f();
    transObj->translation(0.0f,0.0f,0.0f);
    Matrix4f *scaleBack =new Matrix4f();
    scaleBack->scale(10.0,10.0,10.0);
    objNode=new NodeSceneGraph();
    objNode->add(transObj);
    objNode->add(scaleBack);
    objNode->add(materialCollect->getMaterial(document["bkgdMaterial"].GetString()));
    objNode->add(meshCollect->getMesh(BACKGROUND));
    background= new ObjectScene(objNode);

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

    MeshCollection * meshCollect= MeshCollection::getInstance();
    delete meshCollect;

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
        position=vec3f(coins[i]->getPosition());
        if(position.x>posHero.x-8 && position.x<posHero.x+8)
            coins[i]->visualization(cv);
    }

    //Draw particles system
    for(unsigned i=0;i<particleSystem.size();i++){
        position=vec3f(particleSystem[i]->getPosition());
        if(position.x>posHero.x-8 && position.x<posHero.x+8)
            particleSystem[i]->visualization(cv);
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

    //Update particles system
    for(unsigned i=0;i<particleSystem.size();i++){
        particleSystem[i]->updateState(time,currentKeyStates,rootMap);
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
            //if((indexObj.y >= (pos.y)+box.minValue.y && indexObj.y <= (pos.y)+box.maxValue.y)){
            if((indexObj.y+0.5 > (pos.y)+box.minValue.y && indexObj.y+0.5 < (pos.y)+box.maxValue.y)||(indexObj.y-0.5 > (pos.y)+box.minValue.y && indexObj.y-0.5 < (pos.y)+box.maxValue.y)){
                hasCollision=true;
                result=objs[(*it)];
            }
        }
    }

    return result;
}
