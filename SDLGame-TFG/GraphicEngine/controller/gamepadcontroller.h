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

#ifndef GAMEPADCONTROLLER_H
#define GAMEPADCONTROLLER_H

#include "controller.h"
#include <iostream>

using namespace std;

class GamepadController : public Controller
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        GamepadController();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~GamepadController();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will update the event/buttons of our gamepadcontroller
        *    @param event -> our current event
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void checkEvent(SDL_Event & event);


    protected:

    private:
        void setButton(bool value,Uint8 button);
        void updateJoystickMove(Sint16 x,Sint16 y);
        void addGamepad(int id);
        void removeGamepad();
        SDL_GameController * controller;
        SDL_Joystick *joy;
        int instanceID;
};

#endif // GAMEPADCONTROLLER_H
