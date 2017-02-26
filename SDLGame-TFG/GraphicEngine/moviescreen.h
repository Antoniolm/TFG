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

#ifndef MOVIESCREEN_H
#define MOVIESCREEN_H

#include "object3d.h"
#include "rootmap.h"
#include "context.h"
#include "mesh.h"
#include "nodescenegraph.h"
#include "texture.h"
#include "material.h"
#include "profile.h"
#include "sound.h"
#include "gamestate.h"
#include "meshcollection.h"
#include "materialcollection.h"
#include "../lib/rapidjson/document.h"

using namespace rapidjson;

class MovieScreen : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        MovieScreen(vec3f pos,const Value & movieFeatures);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~MovieScreen();

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
        void updateState(GameState & gameState);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set if the movie is activated or not
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setActivate(bool value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return if the movie is activated or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isActivated();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will activate all the texture of our movie (require when our rootMap
        *    is created in a thread)
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activateAllTexture();

    protected:

    private:
        NodeSceneGraph * root;
        Matrix4f * positionMenu;
        bool activateMenu;
        vector<Texture *> options;
        int currentOption;
        Material * currentMaterial;
        float menuDelay;
        vector<string> textures;
};

#endif // MOVIESCREEN_H