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

#ifndef NPC_H
#define NPC_H

#include "../GraphicEngine/ianpc.h"
#include "avatar.h"
#include "../GraphicEngine/mesh.h"
#include "../GraphicEngine/text.h"
#include <SDL_TTF.h>

class Npc : public Avatar
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Npc();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Npc();

        void addDialog(const string state);
        void currentDialog();
        void nextDialog();
        void visualization(Context & cv);
        void updateState(float time);
        void activateNpc(bool value);
        bool getActivate();


    protected:

    private:
        IANpc stateMachine;
        Text *currentText;
        bool npcActivate;
};

#endif // NPC_H
