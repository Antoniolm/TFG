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

#ifndef COIN_H
#define COIN_H

#include "../GraphicEngine/object3d.h"
#include "../GraphicEngine/nodescenegraph.h"
#include "../GraphicEngine/material.h"
#include "../GraphicEngine/matrix4f.h"
#include "../GraphicEngine/matrix4fdynamic.h"
#include "../GraphicEngine/meshcollection.h"
#include "../GraphicEngine/soundcollection.h"
#include "../GraphicEngine/axisrotation.h"
#include "../GraphicEngine/sound.h"

class Coin : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Coin(vec3f aPosition,int aValue);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Coin();

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
        virtual void updateState(float time,Controller * controller,RootMap * rootMap);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will return the value of our coin
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int getValue();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will return if the hero took that coin or not
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        bool isTake();

    protected:

    private:
        int value;
        NodeSceneGraph * root;
        Matrix4f * animationMatrix;
        AxisRotation * rotation;
        Sound * soundTake;
        bool notTake;
};

#endif // COIN_H
