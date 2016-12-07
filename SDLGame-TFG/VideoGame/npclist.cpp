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

NpcList::NpcList()
{
}

//**********************************************************************//

NpcList::~NpcList()
{
    //dtor
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
    bool isActivate=false;vec3f distance,posHero;unsigned currentNpc;

    Hero * hero=rootMap->getHero();
    posHero=hero->getPosition();
    for(unsigned i=0;i<npcs.size() && !isActivate;i++){ //Check if hero is talking now
        isActivate=npcs[i]->getActivate();
        currentNpc=i;
    }
    if(isActivate){ //If hero is talking and he is a good distance
        distance=(npcs[currentNpc]->getPosition())-(posHero);
        if((distance.x<-2 || distance.x>2)||(distance.y<-1 || distance.y>1)||(distance.z<-2 || distance.z>2)){
            npcs[currentNpc]->activateNpc(false);
            hero->activateDialog(false);
        }
    }

    //User push the button -> A
    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_a)] && dialogTime<(time-400.0)){
        if(isActivate){ //If hero is talking -> nextDialog
                npcs[currentNpc]->nextDialog();
                //Check the speaker
                if(npcs[currentNpc]->getSpeaker()==NPC_DIALOG){ //speaker -> Npc
                    npcs[currentNpc]->currentDialog();
                    hero->activateDialog(false);
                }
                else { //speaker -> Hero
                    if(!npcs[currentNpc]->isInitialState()){
                        hero->activateDialog(true);
                        hero->setDialog(npcs[currentNpc]->getMessage());
                    }
                    else{
                        hero->activateDialog(false);
                    }
                }
        }
        else { //Else Check if hero will start a new conversation.
            for(unsigned j=0;j<npcs.size();j++){
                distance=(npcs[j]->getPosition())-(posHero);
                if((distance.x>-1 && distance.x<1)&&(distance.y>-1 && distance.y<1)&&(distance.z>-1 && distance.z<1)){
                    npcs[j]->activateNpc(true);
                    //Check the speaker
                    if(npcs[j]->getSpeaker()==NPC_DIALOG){ //speaker -> Npc
                        npcs[j]->currentDialog();
                        hero->activateDialog(false);
                    }
                    else {//speaker -> Hero
                        hero->activateDialog(true);
                        hero->setDialog(npcs[j]->getMessage());
                    }
                }
            }
        }
        dialogTime=currentTime;
    }
    currentTime+=time-currentTime;
}
