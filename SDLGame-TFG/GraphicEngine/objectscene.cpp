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

#include "objectscene.h"

ObjectScene::ObjectScene()
{
    //ctor
}

//**********************************************************************//

ObjectScene::ObjectScene(Object3D * aObject){
    object=aObject;
}

//**********************************************************************//

ObjectScene::~ObjectScene()
{
    //dtor
}

//**********************************************************************//

void ObjectScene::visualization(Context & vis){
    matrix = vis.matrixStack.getMatrix();
    if(vis.visualization_mode==1)
        position=matrix.product(vec4f());
    vis.posObject.push_back(vec3f(position.x,position.y,position.z));

    object->visualization(vis);
}

//**********************************************************************//

void ObjectScene::updateState(float time){
    object->updateState(time);
}

//**********************************************************************//

vec3f ObjectScene::getPosition(){
    return vec3f(position.x,position.y,position.z);
}

//**********************************************************************//

void ObjectScene::setPosition(vec3f pos){
    position=vec4f(pos.x,pos.y,pos.z,1.0);
}
