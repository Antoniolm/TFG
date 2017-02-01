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
#include "../VideoGame/coinlist.h"
#include "objectgroup.h"
#include <stdlib.h>     /* srand, rand */
RootMap::RootMap(){
}

//**********************************************************************//

RootMap::RootMap(const rapidjson::Document & document,Shader & shader)
{
    cout<< "< Game is loading our current map >"<< endl;

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    /////////////////////////////////////////
    // Create hero
    /////////////////////////////////////////
    hero=new Hero(vec3f(document["heroPosition"][0].GetFloat(),document["heroPosition"][1].GetFloat(),document["heroPosition"][2].GetFloat()));

    /////////////////////////////////////////
    // Add Light to our map
    /////////////////////////////////////////
    const rapidjson::Value & lightFeature=document["light"];
    glUniform1i(glGetUniformLocation(shader.getProgram(), "numActivateLight"), lightFeature.Size()-1);
    Light * light;
    for(unsigned currentLight=0;currentLight<lightFeature.Size();currentLight++){
        //Create our light
        light=new Light(lightFeature[currentLight]);
        //Activate our current Light
        light->activate(&shader,std::string(lightFeature[currentLight]["channel"].GetString()));

    }

    /////////////////////////////////////////
    // Add particleSystems to our map
    /////////////////////////////////////////
    const rapidjson::Value & particleFeature=document["particleSystem"];
    for(unsigned currentPSys=0;currentPSys<particleFeature.Size();currentPSys++){
        particleSystem.push_back(new ParticleSystem(particleFeature[currentPSys]));
    }

    /////////////////////////////////////////
    // Add projectileSystem to our map
    /////////////////////////////////////////
    const rapidjson::Value & projectileFeature=document["projectileSystem"];
    for(unsigned currentPSys=0;currentPSys<projectileFeature.Size();currentPSys++){
        projectileSystem.push_back(new ProjectileSystem(projectileFeature[currentPSys]));
    }

    /////////////////////////////////////////
    // Add voxelGroup to our map
    /////////////////////////////////////////
    const rapidjson::Value & voxelGroup=document["voxelGroup"];
    VoxelGroup * vGroup;

    for(unsigned currentGroup=0;currentGroup<voxelGroup.Size();currentGroup++){
        vGroup=new VoxelGroup(voxelGroup[currentGroup],objs);
    }

    /////////////////////////////////////////
    // Add decorationObject to our map
    /////////////////////////////////////////
    Matrix4f * transformation;
    const rapidjson::Value & decoObject=document["decorationObject"];
    vec3f posDecoration;
    for(unsigned currentDeco=0;currentDeco<decoObject.Size();currentDeco++){

        for(unsigned i=0;i<decoObject[currentDeco]["position"].Size();i+=3){
            posDecoration=vec3f(decoObject[currentDeco]["position"][i].GetFloat(),
                                decoObject[currentDeco]["position"][i+1].GetFloat(),
                                decoObject[currentDeco]["position"][i+2].GetFloat());

            if(decoObject[currentDeco]["collision"].GetBool()) //If collision
                objs.push_back(new DecorationObject(decoObject[currentDeco],posDecoration));

                decorationObjs.push_back(new DecorationObject(decoObject[currentDeco],posDecoration));

        }
    }

    ////////////////////////////////////////////
    // Background
    Matrix4f * transObj=new Matrix4f();
    transObj->translation(0.0f,0.0f,0.0f);

    Matrix4f *scaleBack =new Matrix4f();
    scaleBack->scale(10.0,10.0,10.0);

    NodeSceneGraph * objNode=new NodeSceneGraph();
    objNode->add(transObj);
    objNode->add(scaleBack);
    objNode->add(materialCollect->getMaterial(document["bkgdMaterial"].GetString()));
    objNode->add(meshCollect->getMesh(BACKGROUND));
    background= new ObjectScene(objNode);

    /////////////////////////////////////////
    // Add coins to our map
    /////////////////////////////////////////
    const rapidjson::Value & coinValue=document["coins"];
    coinList=new CoinList(coinValue);


    /////////////////////////////////////////
    // Add npcs of our map
    /////////////////////////////////////////
    const rapidjson::Value & npcsValue=document["npcs"];
    npcList=new NpcList(npcsValue);

    /////////////////////////////////////////
    // Add enemy of our map
    const rapidjson::Value & enemies=document["enemies"];

    enemyList=new EnemyList(enemies);

    ////////////////////////////////////////
    //Create the indexMap;

    Context cv;
    objectGround=new ObjectGroup(mCUBE_DUNG);
    objectWall=new ObjectGroup(mCUBE_WALL);
    for(unsigned i=0;i<objs.size();i++){
        objs[i]->obtainPosition(cv);
        if(objs[i]->getMaterialIndex()==mCUBE_DUNG)
            objectGround->addObject(objs[i]->getPosition(),CUBE);
        if(objs[i]->getMaterialIndex()==mCUBE_WALL)
            objectWall->addObject(objs[i]->getPosition(),CUBE);
    }
    objectGround->init();
    objectWall->init();


    for(unsigned i=0;i<decorationObjs.size();i++){
        decorationObjs[i]->obtainPosition(cv);
    }

    vec3f pos;
    BoundingBox bounding;

    //Create our indexMap for our collision system
    for(unsigned i=0;i<objs.size();i++){
        pos=objs[i]->getPosition();
        bounding=objs[i]->getBoundingBox();
        bounding.minValue.z+=0.1;
        bounding.minValue.x-=0.1;

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

    MaterialCollection * materialCollect= MaterialCollection::getInstance();
    delete materialCollect;

    SoundCollection * soundCollect= SoundCollection::getInstance();
    delete soundCollect;
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

EnemyList * RootMap::getEnemyList(){
    return enemyList;
}

//**********************************************************************//

void RootMap::visualization(Context & cv){
    vec3f position,posHero=hero->getPosition();
    //Draw background
    background->visualization(cv);

    //Draw object
    /*for(unsigned i=0;i<objs.size();i++){
        position=objs[i]->getPosition();
        if(position.x>posHero.x-10 && position.x<posHero.x+10)
            objs[i]->visualization(cv);
    }*/

    objectGround->visualization(cv);
    objectWall->visualization(cv);

    //Draw hero
    hero->visualization(cv);

    //Draw ncps
    npcList->visualization(cv);

    //Draw enemies
    enemyList->visualization(cv);

    //Draw coins
    coinList->visualization(cv);

    //Draw decoration object
    for(unsigned i=0;i<decorationObjs.size();i++){
        position=decorationObjs[i]->getPosition();
        if(position.x>posHero.x-10 && position.x<posHero.x+10)
            decorationObjs[i]->visualization(cv);
    }

    //Draw particles system
    for(unsigned i=0;i<particleSystem.size();i++){
        //position=vec3f(particleSystem[i]->getPosition());
        //if(position.x>posHero.x-8 && position.x<posHero.x+8)
            particleSystem[i]->visualization(cv);
    }

    //Draw projectile system
    for(unsigned i=0;i<projectileSystem.size();i++){
            projectileSystem[i]->visualization(cv);
    }
}

//**********************************************************************//

void RootMap::updateState(float time,Controller * controller,RootMap * rootMap){
    if(time-currentTime>200)
        currentTime=time-50;

    //Update the hero
    hero->updateState(time,controller,rootMap);

    //Update the Scene
    for(unsigned i=0;i<objs.size();i++)
        objs[i]->updateState(time,controller,rootMap);

    //Update the Scene
    coinList->updateState(time,controller,rootMap);

    //Update particles system
    for(unsigned i=0;i<particleSystem.size();i++){
        particleSystem[i]->updateState(time,controller,rootMap);
    }

    //Update projectile system
    for(unsigned i=0;i<projectileSystem.size();i++){
        projectileSystem[i]->updateState(time,controller,rootMap);
    }

    npcList->updateState(time,controller,rootMap);
    enemyList->updateState(time,controller,rootMap);
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
            if((indexObj.y >= (pos.y)+box.minValue.y && indexObj.y <= (pos.y)+box.maxValue.y)){
                hasCollision=true;
                result=objs[(*it)];
            }
        }
    }

    return result;
}
