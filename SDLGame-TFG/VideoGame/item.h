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

#ifndef ITEM_H
#define ITEM_H

#include "../GraphicEngine/object3d.h"
#include "../GraphicEngine/nodescenegraph.h"
#include "../GraphicEngine/material/material.h"
#include "../GraphicEngine/matrix/matrix4f.h"
#include "../GraphicEngine/matrix/matrix4fdynamic.h"
#include "../GraphicEngine/collection/meshcollection.h"
#include "../GraphicEngine/collection/soundcollection.h"
#include "../GraphicEngine/matrix/axisrotation.h"
#include "../GraphicEngine/sound/sound.h"

enum ItemIndex{
    iCOIN,
    iPOTION
};

class Item : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor
        *    @param aPosition -> The initial position of our item
        *    @param aValue -> the value of our item
        *    @param aType -> the type of item that our item will be
        */
        //////////////////////////////////////////////////////////////////////////
        Item(vec3f aPosition,int aValue,ItemIndex aType);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Item();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    @param vis -> the context of our visualization
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void visualization(Context & cv);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    @param gameState -> the current state of our game
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void updateState(GameState & gameState);


        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will set the value of our coin
        *    @param aValue -> the new contain of our value
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setValue(int aValue);

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
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isTake();

    protected:

    private:
        int value;                  // Value of the item
        NodeSceneGraph * root;      // Root of the object
        Matrix4f * animationMatrix; // Matrix 4x4 of the animation
        AxisRotation * rotation;    // Rotation movement
        Sound * soundTake;          // Sound of taken coin
        bool notTake;               // Flag to not taken coin
        ItemIndex type;             // Type of the item( potion or crystal )
};

#endif // ITEM_H
