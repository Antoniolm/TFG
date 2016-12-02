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
    object->visualization(vis);

    matrix=Matrix4f(vis.currentTransf);
    position=matrix.product(vec4f());
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

BoundingBox ObjectScene::getBoundingBox(){
    return object->getBoundingBox();
}
