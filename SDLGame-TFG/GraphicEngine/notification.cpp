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

#include "notification.h"

Notification::Notification(vec3f aPosition,vec3f aScale,float aVisibleTime,MaterialIndex material)
{
    position=vec4f(aPosition.x,aPosition.y,aPosition.z,1.0);
    activatedNoti=true;
    visibleTime=aVisibleTime;

    MeshCollection * meshCollect =MeshCollection::getInstance();
    MaterialCollection * materialCollect =MaterialCollection::getInstance();

    transNoti=new Matrix4f();
    transNoti->identity();

    Matrix4f * scaleMenu=new Matrix4f();
    scaleMenu->scale(aScale.x,aScale.y,aScale.z);

    Matrix4f * rotationMenu=new Matrix4f();
    rotationMenu->rotation(20,1.0,0.0,0.0);

    root=new NodeSceneGraph(false,true);
    root->add(transNoti);
    root->add(rotationMenu);
    root->add(scaleMenu);
    root->add(materialCollect->getMaterial(material));
    root->add(meshCollect->getMesh(TEXT));

    currentTime=SDL_GetTicks();
    initialTime=currentTime;
}

//**********************************************************************//

Notification::Notification(const Value & notificationFeatures)
{
    position=vec4f(notificationFeatures["position"][0].GetFloat(),notificationFeatures["position"][1].GetFloat(),notificationFeatures["position"][2].GetFloat(),1.0);
    activatedNoti=true;
    visibleTime=notificationFeatures["visibleTime"].GetFloat();

    MeshCollection * meshCollect =MeshCollection::getInstance();
    Material * material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,notificationFeatures["texture"].GetString(),mTRUNK);

    transNoti=new Matrix4f();
    transNoti->identity();

    Matrix4f * scaleMenu=new Matrix4f();
    scaleMenu->scale(notificationFeatures["scale"][0].GetFloat(),notificationFeatures["scale"][1].GetFloat(),notificationFeatures["scale"][2].GetFloat());

    Matrix4f * rotationMenu=new Matrix4f();
    rotationMenu->rotation(20,1.0,0.0,0.0);

    root=new NodeSceneGraph(false,true);
    root->add(transNoti);
    root->add(rotationMenu);
    root->add(scaleMenu);
    root->add(material);
    root->add(meshCollect->getMesh(TEXT));

    currentTime=SDL_GetTicks();
    initialTime=currentTime;
}

//**********************************************************************//

Notification::~Notification()
{
    delete root;
}

//**********************************************************************//

void Notification::visualization(Context & cv){
    if(activatedNoti){
        root->visualization(cv);
    }
}

//**********************************************************************//

void Notification::updateState(float time,ControllerManager * controller,RootMap * rootMap){
    vec3f posHero=rootMap->getHero()->getPosition();

    if(time-currentTime>200){ //If we have a delay in our time
        initialTime+=time-currentTime;
        currentTime=time-50;
    }

    transNoti->translation(position.x+posHero.x,position.y+posHero.y,position.z+posHero.z);

    if(currentTime-initialTime>visibleTime) //if the time of our notification is finished
        activatedNoti=false;


    currentTime+=time-currentTime;


}