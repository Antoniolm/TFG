// *********************************************************************
// **
// ** Copyright (C) 2016 Antonio David L�pez Machado
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

#ifndef GAME_H
#define GAME_H

#include "../GraphicEngine/window.h"
#include "../GraphicEngine/mesh.h"
#include "../GraphicEngine/context.h"
#include "../GraphicEngine/nodescenegraph.h"
#include "../GraphicEngine/sound.h"

class Game
{
    public:


        //////////////////////////////////////////////////////////////////////////
        /**
        *    Constructor
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        Game();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Destructor
        */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Game();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Method will contain the main loop of the videoGame
        *    In that loop will have the detection of keyboard events
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void loop();

    protected:

    private:
        Window *window;
};

#endif // GAME_H
