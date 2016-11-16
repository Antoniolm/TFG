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

#ifndef HERO_H
#define HERO_H

#include "avatar.h"
#include "../GraphicEngine/mesh.h"
#include "../GraphicEngine/meshmaterial.h"
#include "../GraphicEngine/scriptlmd.h"
#include "../GraphicEngine/context.h"
#include "../GraphicEngine/matrixscript.h"
#include "../GraphicEngine/rootmap.h"
#include <vector>

using namespace std;
class RootMap;
class Hero: public Avatar
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Hero();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Hero();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void visualization(Context & cv);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will set our map
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setMap(RootMap * aMap);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will move our hero
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        bool moveBody(vec3f aMove,avatarDirection aDir);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will reset animations because the hero isn't in movement
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void noMove();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will create the gravity for our hero
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void gravity(float velocity);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the position of our hero
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getPosition();

    protected:

    private:
        vector<Matrix4f *> moveMatrix;
        float currentTime;
        ScriptLMD animation;
        Matrix4f * moveHero;
        avatarDirection direction;
        bool isMoving;
        RootMap * rootMap;
};

#endif // HERO_H


