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

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "controllermanager.h"
#include "menu.h"
#include "pausemenu.h"
#include "mainmenu.h"
#include "deadmenu.h"
#include "optionmenu.h"
#include "controlmenu.h"
#include "loadingscreen.h"
#include "moviescreen.h"
#include "rootmap.h"
#include "camera.h"

class DeadMenu;
class LoadingScreen;
class MainMenu;
class PauseMenu;
class OptionMenu;
class ControlMenu;
class MovieScreen;
class Camera;
class GameState
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        GameState();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~GameState();

        float time;
        ControllerManager * controller;
        RootMap * rootMap;
        PauseMenu * pauseMenu;
        MainMenu * mainMenu;
        DeadMenu * deadMenu;
        OptionMenu * optionMenu;
        ControlMenu * controlMenu;
        LoadingScreen * loadScreen;
        MovieScreen * movie;
        Camera * camera;

    protected:

    private:
};

#endif // GAMESTATE_H
