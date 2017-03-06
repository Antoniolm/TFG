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
    collection.addElement(new Sound("sounds/coin.wav",1,30,-1,0));

    collection.addElement(new Sound("sounds/openSound.wav",1,40,-1,0));

    collection.addElement(new Sound("sounds/walking.wav",1,40,-1,-1));

    collection.addElement(new Sound("sounds/enemyHit.wav",1,50,-1,0));

    collection.addElement(new Sound("sounds/shoot.wav",1,50,-1,0));

    collection.addElement(new Sound("sounds/sword.wav",1,1,-1,0));

    collection.addElement(new Sound("sounds/arrowHit.wav",1,50,-1,0));

    //Create our map
    collection.addIndex("sCoin",sCoin);
    collection.addIndex("sOpen",sOpen);
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
