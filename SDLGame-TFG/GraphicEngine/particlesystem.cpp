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

#include "particlesystem.h"

ParticleSystem::ParticleSystem()
{
    //ctor
}

//**********************************************************************//

ParticleSystem::ParticleSystem(int numParticle)
{
    nParticles=numParticle;
    currentParticles=0;
}

//**********************************************************************//

ParticleSystem::~ParticleSystem()
{
    //dtor
}

//**********************************************************************//

void ParticleSystem::visualization(Context & cv){
    list<Particle *>::iterator it;
    for(it=particles.begin();it!=particles.end();it++){
        (*it)->visualization(cv);
    }
}

//**********************************************************************//

void ParticleSystem::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap){
    if(time-currentTime>200)
        currentTime=time-50;

    list<Particle *>::iterator it=particles.begin();
    while(it!=particles.end()){
        (*it)->updateState(time,currentKeyStates,rootMap);
        if((*it)->getRemainingTime()<=0.0){
            particles.erase(it);
            currentParticles--;
        }
        else
            it++;
    }

    //Create new particles if some of them is dead
    int diff=nParticles-currentParticles;
    for(int i=0;i<diff;i++)
        particles.push_back(new Particle());

    currentTime+=(time-currentTime);
}
