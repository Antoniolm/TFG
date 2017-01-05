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

#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <object3d.h>
#include <nodescenegraph.h>
#include <context.h>
#include "materialcollection.h"
#include <rootmap.h>
#include <list>
#include <particle.h>
#include <string>

class Particle;
class ParticleSystem : public NodeSceneGraph
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        ParticleSystem();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters*/
        //////////////////////////////////////////////////////////////////////////
        ParticleSystem(int numParticle,string aMaterial,vec3f aMinPos,vec3f aMaxPos,vec3f aVelocity,float aMinTime,float aMaxTime);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~ParticleSystem();

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
        void updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap);

    protected:

    private:
        list<Particle *> particles;
        int nParticles;         //total number of particles that our system has to have with life
        int currentParticles;   //number of live particles in our system
        vec3f maxPos,minPos,velocity;
        float minTime,maxTime;
        Material * material;
};

#endif // PARTICLESYSTEM_H
