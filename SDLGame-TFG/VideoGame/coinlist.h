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

#ifndef COINLIST_H
#define COINLIST_H

#include "../GraphicEngine/nodeSceneGraph.h"
#include "coin.h"
#include <vector>
#include "../lib/rapidjson/document.h"

using namespace rapidjson;

class coinList : public NodeSceneGraph
{
    public:
        /** Default constructor */
        coinList();
        /** Default destructor */
        virtual ~coinList();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will add a new enemy on the list
        *    \param enemy -> The new element that will added on our list
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void add(Coin * coin);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void visualization(Context & cv);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap);

    protected:

    private:
        vector<Coin *> coins;
};

#endif // COINLIST_H
