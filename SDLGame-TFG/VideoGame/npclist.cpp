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

#include "npclist.h"

NpcList::NpcList(){
}

//**********************************************************************//

NpcList::NpcList(const Value & npcsFeatures,vector<ObjectScene *> & objs){
    speakerMessage speaker;
    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();


    for(unsigned i=0;i<npcsFeatures.Size();i++){
        Npc * currentNpc=new Npc(vec3f(npcsFeatures[i]["position"][0].GetFloat(),npcsFeatures[i]["position"][1].GetFloat(),npcsFeatures[i]["position"][2].GetFloat()));
        const Value & dialogs=npcsFeatures[i]["dialog"];

        for(unsigned j=0;j<dialogs.Size();j++){
            if(dialogs[j]["speaker"].GetInt()==0) speaker=NPC_DIALOG;
            else speaker=HERO_DIALOG;
            currentNpc->addDialog(std::string(dialogs[j]["string"].GetString()),speaker);
        }
        npcs.push_back(currentNpc);


        //Added his void cube for collision
        Matrix4f * transMatrix=new Matrix4f();
        transMatrix->translation(npcsFeatures[i]["position"][0].GetFloat(),npcsFeatures[i]["position"][1].GetFloat(),npcsFeatures[i]["position"][2].GetFloat());
        Matrix4f * scaleMatrix =new Matrix4f();
        scaleMatrix->scale(0.5,1,0.5);
        NodeSceneGraph * collisionNode=new NodeSceneGraph();
        collisionNode->add(transMatrix);
        collisionNode->add(scaleMatrix);
        collisionNode->add(materialCollect->getMaterial(mVOID));
        collisionNode->add(meshCollect->getMesh(CUBE));
        objs.push_back(new ObjectScene(collisionNode));
    }
}

//**********************************************************************//

NpcList::~NpcList(){
    for(vector<Npc *>::iterator it = npcs.begin() ; it != npcs.end(); ++it){
        delete (*it);
    }
}

//**********************************************************************//

void NpcList::add(Npc * npc){
    npcs.push_back(npc);
}

//**********************************************************************//

void NpcList::visualization(Context & cv){
    for(unsigned i=0;i<npcs.size();i++)
        npcs[i]->visualization(cv);
}

//**********************************************************************//

void NpcList::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap  ){

    //Check if the hero is speaking with a avatar
    bool isActivate=false,isNearNpc=false;vec3f distance,posHero;unsigned currentNpc;

    Hero * hero=rootMap->getHero();
    posHero=hero->getPosition();
    for(unsigned i=0;i<npcs.size() && !isActivate;i++){ //Check if hero is talking now
        npcs[i]->updateState(time,currentKeyStates,rootMap);
        isActivate=npcs[i]->getActivate();
        currentNpc=i;

        //Check if the hero is near to a npc
        distance=(npcs[i]->getPosition())-(posHero);
        if((distance.x>-1 && distance.x<1)&&(distance.y>-2 && distance.y<2)&&(distance.z>-1 && distance.z<1) && !isActivate){
            hero->activateDialog(true,1);
            hero->setDialog("A",1);
            isNearNpc=true;
        }
    }

    if(isActivate){ //If hero is talking and he is a good distance
        distance=(npcs[currentNpc]->getPosition())-(posHero);
        if((distance.x<-2 || distance.x>2)||(distance.y<-2 || distance.y>2)||(distance.z<-2 || distance.z>2)){
            npcs[currentNpc]->activateNpc(false);
            hero->activateDialog(false,0);
        }
    }
    else{
        if(!isNearNpc) //If the hero is not near to a npc them the hero doesn't show the dialog "Pulsa A"
            hero->activateDialog(false,1);
    }

    //User push the button -> A
    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_a)] && dialogTime<(time-400.0)){
        if(isActivate){ //If hero is talking -> nextDialog
                npcs[currentNpc]->nextDialog();
                //Check the speaker
                if(npcs[currentNpc]->getSpeaker()==NPC_DIALOG){ //speaker -> Npc
                    npcs[currentNpc]->currentDialog();
                    hero->activateDialog(false,0);
                }
                else { //speaker -> Hero
                    if(!npcs[currentNpc]->isInitialState()){
                        hero->activateDialog(true,0);
                        hero->setDialog(npcs[currentNpc]->getMessage(),0);
                    }
                    else{
                        hero->activateDialog(false,0);
                    }
                }
        }
        else { //Else Check if hero will start a new conversation.
            for(unsigned j=0;j<npcs.size();j++){
                distance=(npcs[j]->getPosition())-(posHero);
                if((distance.x>-1 && distance.x<1)&&(distance.y>-2 && distance.y<2)&&(distance.z>-1 && distance.z<1)){
                    npcs[j]->activateNpc(true);
                    hero->activateDialog(false,1);
                    //Check the speaker
                    if(npcs[j]->getSpeaker()==NPC_DIALOG){ //speaker -> Npc
                        npcs[j]->currentDialog();
                        hero->activateDialog(false,0);
                    }
                    else {//speaker -> Hero
                        hero->activateDialog(true,0);
                        hero->setDialog(npcs[j]->getMessage(),0);
                    }
                }
            }
        }
        dialogTime=currentTime;
    }
    currentTime+=time-currentTime;
}
