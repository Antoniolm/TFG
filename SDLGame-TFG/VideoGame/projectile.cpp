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

Projectile::Projectile(vec3f aPosition,vec3f aVelocity,avatarDirection aDir,float aDamage,Mesh * mesh,Material * material)
{
    direction=aDir;
    velocity=aVelocity;
    damage=aDamage;
    live=true;


    position=vec4f(aPosition.x,aPosition.y,aPosition.z,1.0);

    moveAvatar= new Matrix4f();
    moveAvatar->translation(position.x,position.y,position.z);
    //Update direction
    changeDirection(direction);

    animationMatrix=new Matrix4f();
    animationMatrix->identity();


    Matrix4f * transMatrix=new Matrix4f();
    transMatrix->translation(0.0,0.11,0.0);

    rotation=new AxisRotation(200,0.0,0.0,1.0);

    root=new NodeSceneGraph();
    root->add(moveAvatar);
    root->add(animationMatrix);
    root->add(transMatrix);
    root->add(material);
    root->add(mesh);

    calculateHead();

    currentTime=SDL_GetTicks();

}

//**********************************************************************//

Projectile::~Projectile()
{
    //dtor
}

//**********************************************************************//

void Projectile::visualization(Context & vis){
    if(live)
        root->visualization(vis);
}

//**********************************************************************//

void Projectile::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap ){
    if(time-currentTime>200)
        currentTime=time-50;

    currentMap=rootMap;

    //Checking the hero
    vec3f posHero=rootMap->getHero()->getPosition();
    vec3f posHead=vec3f(vec3f(position)+projectileHead);
    float distance=sqrt(pow(posHead.x-posHero.x,2.0)+pow(posHead.z-posHero.z,2.0));

    if(distance<=0.3 && live && (position.y>posHero.y-1 && position.y<posHero.y+1)){
        rootMap->getHero()->takeDamage(position,direction,damage);
        live=false;
    }


    //Checking the enemies
    vector<Enemy *> enemies=rootMap->getEnemyList()->getEnemies();
    vec3f posEnemy;
    for(unsigned i=0;i<enemies.size() && live;i++){
        posEnemy=enemies[i]->getPosition(); //Calculate the distance
        distance=sqrt(pow(posHead.x-posEnemy.x,2.0)+pow(posHead.z-posEnemy.z,2.0));

        if(distance<=0.3 && (position.y>posEnemy.y-1 && position.y<posEnemy.y+1)){//If is near
            enemies[i]->takeDamage(position,direction,damage);
            live=false;
        }
    }

    if(live) //if not collision with something
        live=moveBody(velocity,direction);

    root->updateState(time,currentKeyStates,rootMap);
    position=moveAvatar->product(vec4f());
    if(position.z>0.0 || position.x<0.0)
        live=false;

    //Animation
    animationMatrix->setMatrix(rotation->updateState(time-currentTime).getMatrix());
    currentTime+=(time-currentTime);
}
//**********************************************************************//

bool Projectile::isLive(){
    return live;
}

//**********************************************************************//

void Projectile::calculateHead(){
    switch(direction){
            case FORWARD:
                projectileHead=vec3f(0.0,0.0,0.5);
            break;
            case BACKWARD:
                projectileHead=vec3f(0.0,0.0,-0.5);
            break;
            case LEFTWARD:
                projectileHead=vec3f(-0.5,0.0,0.0);
            break;
            case RIGHTWARD:
                projectileHead=vec3f(0.5,0.0,0.0);
            break;
            case FOR_LEFTWARD:
                projectileHead=vec3f(-0.4,0.0,0.4);
            break;
            case FOR_RIGHTWARD:
                projectileHead=vec3f(0.4,0.0,0.4);
            break;
            case BACK_LEFTWARD:
                projectileHead=vec3f(-0.4,0.0,-0.4);
            break;
            case BACK_RIGHTWARD:
                projectileHead=vec3f(0.4,0.0,-0.4);
            break;
        }

}
