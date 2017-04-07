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

#ifndef SOUL_H
#define SOUL_H

#include "../GraphicEngine/object3d.h"
#include "../GraphicEngine/nodescenegraph.h"
#include "../GraphicEngine/matrix4f.h"
#include "../GraphicEngine/matrix4fdynamic.h"
#include "../GraphicEngine/meshcollection.h"
#include "../GraphicEngine/materialcollection.h"
#include "../GraphicEngine/axisrotation.h"
#include "../lib/rapidjson/document.h"

using namespace rapidjson;

class Soul : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Soul(const Value & soulFeatures);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Soul();

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
        *    It will set the position of our soul
        *    @param value -> the new value of our position
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setPosition(vec3f value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set if the soul is in the hand of our hero or not
        *    @param  value -> the new value of our boolean
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setInCarrier(bool value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return if the soul is in the hand of our hero
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool getInCarrier();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return if the soul is activated or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool getActivate();

    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will calculate the position of our soul when is taken for a hero
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void calculatePosition(vec3f posHero,avatarDirection direction);

        NodeSceneGraph * root;
        Matrix4f * transMatrix,* animationMatrix;
        AxisRotation * rotation;
        bool activated;
        bool inCarrier;
};

#endif // SOUL_H
