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


#include "enemylist.h"

EnemyList::EnemyList()
{
}

//**********************************************************************//

EnemyList::~EnemyList()
{
    //dtor
}

//**********************************************************************//

void EnemyList::add(Enemy * enemy){
    enemies.push_back(enemy);
}

//**********************************************************************//

void EnemyList::visualization(Context & cv){
    for(unsigned i=0;i<enemies.size();i++)
        enemies[i]->visualization(cv);
}

//**********************************************************************//

void EnemyList::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap  ){
    for(unsigned i=0;i<enemies.size();i++)
        enemies[i]->updateState(time,currentKeyStates,rootMap);
}
