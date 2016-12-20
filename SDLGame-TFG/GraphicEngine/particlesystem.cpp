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

#include "particlesystem.h"

ParticleSystem::ParticleSystem()
{
    //ctor
}

//**********************************************************************//

ParticleSystem::~ParticleSystem()
{
    //dtor
}

//**********************************************************************//

void ParticleSystem::visualization(Context & cv){
    for(int i=0;i<particles.size();i++)
        particles[i]->visualization(cv);
}

//**********************************************************************//

void ParticleSystem::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap){
    if(time-currentTime>200)
        currentTime=time-50;

    for(int i=0;i<particles.size();i++){
        particles[i]->updateState(time,currentKeyStates,rootMap);
    }

    currentTime+=(time-currentTime);
}
