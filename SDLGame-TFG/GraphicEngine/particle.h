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

#ifndef PARTICLE_H
#define PARTICLE_H

#include "object3d.h"
#include <context.h>
#include <rootmap.h>
#include <meshcollection.h>
#include <materialcollection.h>
#include <stdlib.h>


class Particle : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Particle();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters */
        //////////////////////////////////////////////////////////////////////////
        Particle(Material * material,vec3f aScale,vec3f minPos,vec3f maxPos,vec3f aVelocity,float minTime,float maxTime);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Particle();

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
        void updateState(float time,Controller * controller,RootMap * rootMap);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the remaining time of our particle
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getRemainingTime();
    protected:

    private:
        vec3f position,velocity;
        NodeSceneGraph *root;
        Matrix4f * transMatrix;
        float remainingTime;
};

#endif // PARTICLE_H
