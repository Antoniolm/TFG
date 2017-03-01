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

#ifndef GAME_H
#define GAME_H

#include "../GraphicEngine/window.h"
#include "../GraphicEngine/context.h"
#include "../GraphicEngine/nodescenegraph.h"
#include "../GraphicEngine/sound.h"
#include "../GraphicEngine/matrixstatic.h"
#include "../GraphicEngine/linearmovement.h"
#include "../GraphicEngine/axisrotation.h"
#include "../GraphicEngine/rootmap.h"
#include "../GraphicEngine/camera.h"
#include "../GraphicEngine/structdata.h"
#include "../GraphicEngine/text.h"
#include "../GraphicEngine/controllermanager.h"
#include "../GraphicEngine/profile.h"
#include "../GraphicEngine/notification.h"
#include "../GraphicEngine/gamestate.h"
#include "../GraphicEngine/savedmanager.h"
#include "projectile.h"
#include "hero.h"
#include <SDL_gamecontroller.h>
#include <sstream>

class Game
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
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

        static Game * getInstance(){
            if(instance == NULL)
                instance = new Game();

            return instance;
        }


    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor  */
        //////////////////////////////////////////////////////////////////////////
        Game();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It  will update the life of our user interface
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateLife(int &lastLife);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It  will update the crystals of our user interface
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateCoin(int & currentCoin);

        static Game* instance;
        Window * window;
        GameState gameState;
        Hero * hero;
        Text * lifeText,* coinText;
        Notification * notiGamePad;
        Context context;
};

#endif // GAME_H
