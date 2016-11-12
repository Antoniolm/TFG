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

#ifndef OSCILLATEROTATION_H
#define OSCILLATEROTATION_H

#include "matrix4fdynamic.h"
#include <SDL.h>

class OscillateRotation : public Matrix4fDynamic
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        OscillateRotation();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters
        *   \param incre -> Initial increment or decrement grade
        *   \param maxG -> max Grade in our movement
        *   \param minG -> min Grade in our movement
        *   \param initG -> Initial Grade in our movement
        *   \param velocity -> Grade per second
        *   \param dir -> axis of movement
        *   \param loop -> number of loop that the move do( -1 = infinity loop)
        */
        //////////////////////////////////////////////////////////////////////////
        OscillateRotation(bool incre,float maxG,float minG,float initG,float velocity,vec3f dir,int aLoop);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~OscillateRotation();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Set the value of some parameters in the object
        *   \param incre -> Initial increment or decrement grade
        *   \param maxG -> max Grade in our movement
        *   \param minG -> min Grade in our movement
        *   \param initG -> Initial Grade in our movement
        *   \param velocity -> Grade per second
        *   \param dir -> axis of movement
        *   \param loop -> number of loop that the move do( -1 = infinity loop)
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setParameters(bool incre,float maxG,float minG,float initG,float velocity,vec3f dir,int aLoop);

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
        vec3f direction;
        float maxGrade;
        float minGrade;
        float initialGrade;
        float currentGrade;
        float angularVelocity;
        float currentTime;
        bool increment;
        int loop;
        int currentLoop;

};

#endif // OSCILLATEROTATION_H
