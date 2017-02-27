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

#include "npclist.h"

NpcList::NpcList(){
    currentTime=SDL_GetTicks();
    dialogTime=currentTime;
}

//**********************************************************************//

NpcList::NpcList(const Value & npcsFeatures){
    for(unsigned i=0;i<npcsFeatures.Size();i++){
        npcs.push_back(new Npc(npcsFeatures[i]));
    }
    currentTime=SDL_GetTicks();
    dialogTime=currentTime;
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

void NpcList::updateState(GameState & gameState){

    //Check if the hero is speaking with a avatar
    for(unsigned i=0;i<npcs.size();i++){ //Check if hero is talking now
        npcs[i]->updateState(gameState);
    }
}
