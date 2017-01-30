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
#include "../GraphicEngine/Camera.h"
#include "../GraphicEngine/structdata.h"
#include "../GraphicEngine/text.h"
#include "../GraphicEngine/menu.h"
#include "../GraphicEngine/pausemenu.h"
#include "../GraphicEngine/mainmenu.h"
#include "../GraphicEngine/deadmenu.h"
#include "../GraphicEngine/controller.h"
#include "../GraphicEngine/keyboardcontroller.h"
#include "../GraphicEngine/gamepadcontroller.h"
#include "projectile.h"
#include "../lib/rapidjson/document.h"
#include "../lib/rapidjson/stringbuffer.h"
#include "../lib/rapidjson/filereadstream.h"
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

        void updateLife(int &lastLife);
        void updateCoin(int & currentCoin);
        static Game* instance;
        Window * window;
        RootMap * rootMap;
        Hero * hero;
        PauseMenu * pauseMenu;
        MainMenu * mainMenu;
        DeadMenu * deadMenu;
        Text * lifeText,* coinText;
        Controller * controller;
        Context context;
};

#endif // GAME_H
