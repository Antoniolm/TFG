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

#include "projectilesystem.h"

ProjectileSystem::ProjectileSystem(vec3f aRadio,vec3f aPos,vec3f aVeloc,int aDir,float aDelay,string aMesh,string aMaterial)
{
    radioActivity=aRadio;
    position=aPos;
    velocity=aVeloc;

    MaterialCollection * materialCollect=MaterialCollection::getInstance();
    MeshCollection * meshCollect=MeshCollection::getInstance();

    direction=(avatarDirection)aDir;
    timeBWprojectile=aDelay;//time between one projectile and another
    mesh=meshCollect->getMesh(aMesh);
    material=materialCollect->getMaterial(aMaterial);
    currentTime=SDL_GetTicks();
    projectileDelay=currentTime;
}

//**********************************************************************//

ProjectileSystem::~ProjectileSystem()
{
    //dtor
}

//**********************************************************************//

void ProjectileSystem::visualization(Context & cv){
    list<Projectile *>::iterator it;
    for(it=projectiles.begin();it!=projectiles.end();it++){
        (*it)->visualization(cv);
    }
}

//**********************************************************************//

void ProjectileSystem::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap){
    if(time-currentTime>200)
        currentTime=time-50;

    list<Projectile *>::iterator it=projectiles.begin();
    while(it!=projectiles.end()){
        (*it)->updateState(time,currentKeyStates,rootMap);
        /*if((*it)->isLive()){
            delete (*it);
            it=projectiles.erase(it);
        }
        else*/
            it++;
    }

    if(projectileDelay<(time-timeBWprojectile)){
        projectiles.push_back(new Projectile(position,velocity,direction,mesh,material));
        projectileDelay=time;
    }


    currentTime+=(time-currentTime);
}
