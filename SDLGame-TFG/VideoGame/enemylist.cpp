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
    for(vector<Enemy *>::iterator it = enemies.begin() ; it != enemies.end(); ++it){
        delete (*it);
    }
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
    //Check if the hero is speaking with a avatar
    vec3f distance,radio,posHero;unsigned currentNpc;

    Hero * hero=rootMap->getHero();
    posHero=hero->getPosition();
    for(unsigned i=0;i<enemies.size();i++){ //Check if hero is talking now
        distance=(enemies[i]->getPosition())-(posHero);
        radio=(enemies[i]->getRadioActivity());
        if((distance.x>-radio.x && distance.x<radio.x)&&(distance.y>-radio.y && distance.y<radio.y)&&(distance.z>-radio.z && distance.z<radio.z)){
            enemies[i]->activatedEnemy(true);
        }
        enemies[i]->updateState(time,currentKeyStates,rootMap);
    }

}
