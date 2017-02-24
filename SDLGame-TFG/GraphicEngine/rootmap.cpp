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
#include "../VideoGame/itemlist.h"
#include "objectgroup.h"
#include <stdlib.h>     /* srand, rand */

bool RootMap::loading=false;

RootMap::RootMap(){
}

//**********************************************************************//

RootMap::RootMap(string fileMap,bool flagThread){
    RootMap::loading=true;
    hero=0;
    if(flagThread){
        loader=new LoaderThread(this,fileMap);
        loader->run();
    }
    else initialize(fileMap);
}

//**********************************************************************//

RootMap::~RootMap()
{
    delete loader;
    delete backSound;
    delete npcList;
    delete enemyList;
    delete itemList;
    delete hero;
    delete mate;
    delete title;
    delete endMapRegion;
    delete movie;

    for(unsigned i=0;i<objs.size();i++)
        delete objs[i];

    for(unsigned i=0;i<decorationObjs.size();i++)
        delete decorationObjs[i];

    for(unsigned i=0;i<objectGroup.size();i++)
        delete objectGroup[i];

    for(unsigned i=0;i<particleSystem.size();i++)
        delete particleSystem[i];

    for(unsigned i=0;i<projectileSystem.size();i++)
        delete projectileSystem[i];

   for(unsigned i=0;i<regions.size();i++)
        delete regions[i];

    for(unsigned i=0;i<spikes.size();i++)
        delete spikes[i];

    for(unsigned i=0;i<lights.size();i++)
        delete lights[i];

}

//**********************************************************************//

void RootMap::initialize(string fileMap){
    cout<< "< Game is loading our current map >"<< endl;

    //Open file
    FILE * fp = fopen(fileMap.c_str(), "rb"); // non-Windows use "r"
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document document;
    document.ParseStream(is);
    fclose(fp);

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    //Take the file of our next map
    nextMapFile=document["nextMap"].GetString();

    /////////////////////////////////////////
    // Create hero and mate
    /////////////////////////////////////////
    vec3f positionHero=vec3f(document["heroPosition"][0].GetFloat(),document["heroPosition"][1].GetFloat(),document["heroPosition"][2].GetFloat());
    hero=new Hero(positionHero);

    mate=new Mate(positionHero);

    /////////////////////////////////////////
    // Add Light to our map
    /////////////////////////////////////////
    const rapidjson::Value & lightFeature=document["light"];
    for(unsigned currentLight=0;currentLight<lightFeature.Size();currentLight++){
        //Create our light
        lights.push_back(new Light(lightFeature[currentLight]));
    }

    /////////////////////////////////////////
    // Add movie to our map
    /////////////////////////////////////////
    const rapidjson::Value & movieFeature=document["movie"];
    movie=new MovieScreen(positionHero,movieFeature);

    /////////////////////////////////////////
    // Add title to our map
    /////////////////////////////////////////
    const rapidjson::Value & titleFeature=document["title"];
    title=new Notification(titleFeature);

    /////////////////////////////////////////
    // Add endMap region to our map
    /////////////////////////////////////////
    const rapidjson::Value & endRegionFeature=document["endMapRegion"];
    endMapRegion=new EndMapRegion(endRegionFeature);

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
    // Add events to our map
    /////////////////////////////////////////
    const rapidjson::Value & regionFeature=document["events"];
    for(unsigned currentRegion=0;currentRegion<regionFeature.Size();currentRegion++){
        regions.push_back(new TextRegion(regionFeature[currentRegion]));
    }

    /////////////////////////////////////////
    // Add spikes to our map
    /////////////////////////////////////////
    const rapidjson::Value & spikeFeature=document["spikes"];
    for(unsigned currentSpike=0;currentSpike<spikeFeature.Size();currentSpike++){
        spikes.push_back(new SpikeTrap(spikeFeature[currentSpike]));
    }

    /////////////////////////////////////////
    // Add voxelGroup to our map
    /////////////////////////////////////////
    const rapidjson::Value & voxelGroup=document["voxelGroup"];

    for(unsigned currentGroup=0;currentGroup<voxelGroup.Size();currentGroup++){
        new VoxelGroup(voxelGroup[currentGroup],objs);
    }

    /////////////////////////////////////////
    // Add decorationObject to our map
    /////////////////////////////////////////
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
    scaleBack->scale(10.0,5.0,10.0);

    NodeSceneGraph * objNode=new NodeSceneGraph();
    objNode->add(transObj);
    objNode->add(scaleBack);
    objNode->add(materialCollect->getMaterial(document["bkgdMaterial"].GetString()));
    objNode->add(meshCollect->getMesh(BACKGROUND));
    background= new ObjectScene(objNode);

    /////////////////////////////////////////
    // Add coins to our map
    /////////////////////////////////////////
    const rapidjson::Value & coinValue=document["items"];
    itemList=new ItemList(coinValue);


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
    objectGroup.push_back(new ObjectGroup(mCUBE_DUNG));
    objectGroup.push_back(new ObjectGroup(mCUBE_WALL));
    objectGroup.push_back(new ObjectGroup(mCUBE_DUNGB));
    objectGroup.push_back(new ObjectGroup(mCUBE_TRAP));
    objectGroup.push_back(new ObjectGroup(mVOID));

    for(unsigned i=0;i<objs.size();i++){
        objs[i]->obtainPosition(cv);
        switch(objs[i]->getMaterialIndex()){
            case mCUBE_DUNG:
                objectGroup[0]->addObject(objs[i]->getPosition(),CUBE);
            break;
            case mCUBE_WALL:
                objectGroup[1]->addObject(objs[i]->getPosition(),CUBE);
            break;
            case mCUBE_DUNGB:
                objectGroup[2]->addObject(objs[i]->getPosition(),CUBE);
            break;
            case mCUBE_TRAP:
                objectGroup[3]->addObject(objs[i]->getPosition(),CUBE);
            break;
            case mVOID:
                objectGroup[4]->addObject(objs[i]->getPosition(),CUBE);
            break;
            default:
            break;
        }
    }

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

    SDL_Delay(2000);

    currentTime=SDL_GetTicks();

    RootMap::loading=false;
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

Mate * RootMap::getMate(){
    return mate;
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

    //Draw object groups
    for(unsigned i=0;i<objectGroup.size()-1;i++)
        objectGroup[i]->visualization(cv);

    //Draw hero
    hero->visualization(cv);

    //Draw ncps
    npcList->visualization(cv);

    //Draw enemies
    enemyList->visualization(cv);

    //Draw items
    itemList->visualization(cv);

    //Draw decoration object
    for(unsigned i=0;i<decorationObjs.size();i++){
        position=decorationObjs[i]->getPosition();
        if(position.x>posHero.x-11 && position.x<posHero.x+11)
            decorationObjs[i]->visualization(cv);
    }

    //Draw particles system
    for(unsigned i=0;i<particleSystem.size();i++){
        position=vec3f(particleSystem[i]->getPosition());
        if(position.x>posHero.x-8 && position.x<posHero.x+8)
            particleSystem[i]->visualization(cv);
    }

    //Draw projectile system
    for(unsigned i=0;i<projectileSystem.size();i++){
        projectileSystem[i]->visualization(cv);
    }

    //Draw spiketrap
    for(unsigned i=0;i<spikes.size();i++){
        spikes[i]->visualization(cv);
    }

    //Draw mate
    mate->visualization(cv);

    //Draw title
    title->visualization(cv);

    /////////////////////////////////////////////////////
    //Visualization here that component because is a visible wall
    objectGroup[objectGroup.size()-1]->visualization(cv);
}

//**********************************************************************//

void RootMap::updateState(GameState & gameState){
    float time=gameState.time;

    if(time-currentTime>200)
        currentTime=time-50;

    //Update the hero
    hero->updateState(gameState);

    //Update the mate
    mate->updateState(gameState);

    //Update the Scene
    for(unsigned i=0;i<objectGroup.size();i++)
        objectGroup[i]->updateState(gameState);

    //Update the Scene
    itemList->updateState(gameState);

    //Update particles system
    for(unsigned i=0;i<particleSystem.size();i++){
        particleSystem[i]->updateState(gameState);
    }

    //Update projectile system
    for(unsigned i=0;i<projectileSystem.size();i++){
        projectileSystem[i]->updateState(gameState);
    }

    //Update textregions
    for(unsigned i=0;i<regions.size();i++){
        regions[i]->updateState(gameState);
    }

    //Update spikeTraps
    for(unsigned i=0;i<spikes.size();i++){
        spikes[i]->updateState(gameState);
    }

    //Update title
    title->updateState(gameState);

    //Update npcs
    npcList->updateState(gameState);

    //Update enemies
    enemyList->updateState(gameState);

    //Update endMapRegion
    endMapRegion->updateState(gameState);

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
        for(;it!=endIt && !hasCollision;it++){ //if There are object in that position (x,z)
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

//**********************************************************************//

pair<ObjectScene *,float> RootMap::detectNearObject(const vec3f & posObj){
    ObjectScene * result=0;
    vec3f pos;
    BoundingBox box;
    float distance,minDistance=20.0;
    int tam=indexMap[(int)posObj.x][(int)posObj.z*-1].size();

    vector<int>::iterator it=indexMap[(int)posObj.x][(int)posObj.z*-1].begin();
    vector<int>::iterator endIt=indexMap[(int)posObj.x][(int)posObj.z*-1].end();

    if(tam!=0 ){
        for(;it!=endIt;it++){ //if There are object in that position (x,z)
            pos=objs[(*it)]->getPosition();
            box=objs[(*it)]->getBoundingBox();
            distance=posObj.y-((pos.y)+box.maxValue.y);
            if(distance>=0.0 && minDistance>distance){
                minDistance=distance;
                result=objs[(*it)];
            }
        }
    }

    return pair<ObjectScene *,float> (result,minDistance);
}

//**********************************************************************//

bool RootMap::isLoading(){
    return RootMap::loading;
}

//**********************************************************************//

bool RootMap::isFinished(){
    bool result=endMapRegion->isActivated();
    if(result){
        RootMap::loading=true;
        enableSound(false);
    }

    return result;
}

//**********************************************************************//

string RootMap::getNextMap(){
    return nextMapFile;
}

//**********************************************************************//

MovieScreen * RootMap::getMovie(){
    return movie;
}

//**********************************************************************//

void RootMap::activatedLight(GLuint shaderID){
    glUniform1i(glGetUniformLocation(shaderID, "numActivateLight"), lights.size()-1);
    for(unsigned i=0;i<lights.size();i++)
        lights[i]->activate(shaderID);
}

//**********************************************************************//

void RootMap::activatedObjectGroup(){
    for(unsigned i=0;i<objectGroup.size();i++)
        objectGroup[i]->init();
}
