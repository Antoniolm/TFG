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

#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "object3d.h"
#include "rootmap.h"
#include "context.h"
#include "mesh.h"
#include "nodescenegraph.h"
#include "texture.h"
#include "material.h"
#include "sound.h"
#include "menu.h"
#include "profile.h"
#include "mainmenu.h"
#include "meshcollection.h"
#include "materialcollection.h"
#include "soundcollection.h"

enum PauseMenuOption{
    pRESUME,
    pQUIT
};

class PauseMenu : public Menu
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        PauseMenu(vec3f initPos);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~PauseMenu();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void visualization(Context & cv);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void updateState(GameState & gameState);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will add a new texture and that texture has a functionality (MainMenuOption)
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void add(string fileName,PauseMenuOption aOption);
    protected:

    private:
        vec3f initialPosition;
        vector<PauseMenuOption> actionOption;
        Sound * openSound,* moveSound;
        int channelOpen,channelMove;
};

#endif // PAUSEMENU_H
