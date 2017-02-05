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
    collection.addElement(sound);

    sound=new Sound("sounds/walking.wav",1,40,8,-1);
    collection.addElement(sound);

    sound=new Sound("sounds/enemyHit.wav",1,50,7,0);
    collection.addElement(sound);

    sound=new Sound("sounds/shoot.wav",1,50,9,0);
    collection.addElement(sound);

    sound=new Sound("sounds/sword.wav",1,1,10,0);
    collection.addElement(sound);

    sound=new Sound("sounds/arrowHit.wav",1,50,11,0);
    collection.addElement(sound);

    //Create our map
    collection.addIndex("sCoin",sCoin);
    collection.addIndex("EMOVE",EMOVE);
    collection.addIndex("EHIT",EHIT);
    collection.addIndex("SHOOT",SHOOT);
    collection.addIndex("sSWORD",sSWORD);
    collection.addIndex("sARROW",sARROW);
}

//**********************************************************************//

SoundCollection::~SoundCollection()
{
}

//**********************************************************************//

Sound* SoundCollection::getSound(SoundIndex element){
    return collection.getElement(element);
}

//**********************************************************************//

Sound* SoundCollection::getSound(string element){
    return collection.getElement(element);
}
