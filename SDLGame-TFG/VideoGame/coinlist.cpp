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

#include "coinlist.h"

CoinList::CoinList()
{
    //ctor
}

//**********************************************************************//

CoinList::CoinList(const Value & coinFeatures){
    for(unsigned i=0;i<coinFeatures.Size();i++){
        coins.push_back(new Coin(vec3f(coinFeatures[i]["position"][0].GetFloat(),coinFeatures[i]["position"][1].GetFloat(),coinFeatures[i]["position"][2].GetFloat()),
                                 coinFeatures[i]["value"].GetInt()));
    }
}

//**********************************************************************//

CoinList::~CoinList()
{
    //dtor
}

//**********************************************************************//

void CoinList::add(Coin * coin){
    coins.push_back(coin);
}

//**********************************************************************//

void CoinList::visualization(Context & cv){
    for(unsigned i=0;i<coins.size();i++)
        coins[i]->visualization(cv);
}

//**********************************************************************//

void CoinList::updateState(float time,ControllerManager * controller,RootMap * rootMap  ){
    vector<Coin*>::iterator it=coins.begin();
    while(it!=coins.end()){
        (*it)->updateState(time,controller,rootMap);
        if((*it)->isTake()){
            delete (*it);
            coins.erase(it);
        }
        else
            it++;
    }
}
