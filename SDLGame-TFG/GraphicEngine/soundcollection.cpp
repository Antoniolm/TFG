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

#include "soundcollection.h"

SoundCollection* SoundCollection::instance = NULL;

//**********************************************************************//

SoundCollection::SoundCollection()
{
    Sound * sound=new Sound("sounds/coin.wav",1,30,4,0);
    collection.push_back(sound);

    sound=new Sound("sounds/walking.wav",1,40,8,-1);
    collection.push_back(sound);

    sound=new Sound("sounds/enemyHit.wav",1,50,7,0);
    collection.push_back(sound);

    //Create our map
    enumMap.insert(pair<string,soundElement> ("sCoin",sCoin));
    enumMap.insert(pair<string,soundElement> ("EMOVE",EMOVE));
    enumMap.insert(pair<string,soundElement> ("EHIT",EHIT));
}

//**********************************************************************//

SoundCollection::~SoundCollection()
{
    if(instance!=NULL){
        vector<Sound *>::iterator it;
        for(it=collection.begin();it!=collection.end();it++){
            delete (*it);
        }
        instance=NULL;
    }
}

//**********************************************************************//

Sound* SoundCollection::getSound(soundElement element){
    return collection[element];
}

//**********************************************************************//

Sound* SoundCollection::getSound(string element){
    return collection[(enumMap.find(element))->second];
}
