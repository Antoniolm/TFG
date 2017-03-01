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

#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "context.h"
#include "structdata.h"
#include "controller.h"
#include "keyboardcontroller.h"
#include "controllermanager.h"
#include "SDL.h"

class Context;
class RootMap;
class GameState;

struct BoundingBox{
    vec3f maxValue;
    vec3f minValue;

    bool operator<(BoundingBox aBounding){
        bool result=false;

        if(maxValue<aBounding.maxValue && minValue>aBounding.minValue)
            result=true;

        return result;
    }
};

class Object3D
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Object3D();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Object3D();

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
        *    The method will obtain the boundingBox of the object.
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual BoundingBox getBoundingBox();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will obtain the boundingBox of the object.
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void obtainPosition(Context & cv);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    \return vec4f with the mesh position
        */
        //////////////////////////////////////////////////////////////////////////
        vec4f getPosition();

    protected:
        float currentTime;
        vec4f position;
        BoundingBox boundingBox;

    private:


};

#endif // OBJECT3D_H
