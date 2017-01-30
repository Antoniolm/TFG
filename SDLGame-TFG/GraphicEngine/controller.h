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

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SDL.H>

class Controller
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Controller();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Controller();

        virtual void setButtonUp(bool value);
        virtual bool checkButtonUp();

        virtual void setButtonDown(bool value);
        virtual bool checkButtonDown();

        virtual void setButtonLeft(bool value);
        virtual bool checkButtonLeft();

        virtual void setButtonRight(bool value);
        virtual bool checkButtonRight();

        virtual void setButtonInteract(bool value);
        virtual bool checkButtonInteract();

        virtual void setButtonJump(bool value);
        virtual bool checkButtonJump();

        virtual void setButtonAttack(bool value);
        virtual bool checkButtonAttack();

        virtual void setButtonShield(bool value);
        virtual bool checkButtonShield();

        virtual void setButtonSwap(bool value);
        virtual bool checkButtonSwap();

        virtual void catchKeyBoardState(const Uint8* currentKeyStates);
    protected:

    private:
};

#endif // CONTROLLER_H
