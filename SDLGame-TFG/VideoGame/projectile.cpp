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

#include "projectile.h"

Projectile::Projectile(vec3f aPosition,vec3f aVelocity,avatarDirection aDir,MeshIndex msIndex,MaterialIndex maIndex)
{
    direction=aDir;
    velocity=aVelocity;
    acceleratedMove=new AcceleratedMovement();
    acceleratedMove->resetState();
    isLive=true;
    isMoving=false;
    isFalling=false;
    isJumping=false;
    isHitting=false;
    isImpacted=false;
    isShielded=false;
    life=100;

    position=vec4f(aPosition.x,aPosition.y,aPosition.z,1.0);
    MeshCollection * meshCollect =MeshCollection::getInstance();
    MaterialCollection *materialCollect=MaterialCollection::getInstance();

    moveAvatar= new Matrix4f();
    moveAvatar->translation(position.x,position.y,position.z);

    root=new NodeSceneGraph();
    root->add(moveAvatar);
    root->add(materialCollect->getMaterial(maIndex));
    root->add(meshCollect->getMesh(msIndex));

    currentTime=SDL_GetTicks();

}

//**********************************************************************//

Projectile::~Projectile()
{
    //dtor
}

//**********************************************************************//

void Projectile::visualization(Context & vis){
    if(isLive)
        root->visualization(vis);
}

//**********************************************************************//

void Projectile::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap ){
    //moveBody(velocity,direction);
    root->updateState(time,currentKeyStates,rootMap);
    currentTime+=(time-currentTime);
}
