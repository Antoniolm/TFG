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

#ifndef ACCELERATEDMOVEMENT_H
#define ACCELERATEDMOVEMENT_H

#include "matrix4fdynamic.h"
#include "structdata.h"
#include <SDL.h>

class AcceleratedMovement : public Matrix4fDynamic
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        AcceleratedMovement();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters*/
        //////////////////////////////////////////////////////////////////////////
        AcceleratedMovement(float x,float y,float z,float aAccel,bool incre);

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters*/
        //////////////////////////////////////////////////////////////////////////
        AcceleratedMovement(const vec3f & aVelocity,float aAccel,bool incre);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~AcceleratedMovement();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Set the value of some parameters in the object
        *   \param x -> axis X
        *   \param y -> axis Y
        *   \param z -> axis Z
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setParameters(float x,float y,float z,float aAccel,bool incre);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Set the value of some parameters in the object
        *   \param x -> axis X
        *   \param y -> axis Y
        *   \param z -> axis Z
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setParameters(const vec3f & aVelocity,float aAccel,bool incre);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the Matrix4xf. That change need the
        *    current time in our application
        *    \return the new state of the matrix4f
        */
        //////////////////////////////////////////////////////////////////////////
        virtual Matrix4f & updateState(float time);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will reset to the initial state
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void resetState();

    protected:

    private:
        vec3f velocity;
        float currentTime,acceleration;
        bool increment;
};

#endif // ACCELERATEDMOVEMENT_H
