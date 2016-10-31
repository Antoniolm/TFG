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

#include "entrancerootmap.h"

EntranceRootMap::EntranceRootMap()
{
    //ctor
}

//**********************************************************************//

EntranceRootMap::EntranceRootMap(Object3D * aObject){
        object=aObject;
        type=0;
}

//**********************************************************************//

EntranceRootMap::EntranceRootMap(Object3D * aObject,Matrix4f * pMatrix){
	    object=aObject;
        matrix=new Matrix4f((*pMatrix));
        type=1;
}

//**********************************************************************//

EntranceRootMap::~EntranceRootMap()
{
    //dtor
}

//**********************************************************************//

Matrix4f * EntranceRootMap::getMatrix(){
    return matrix;
}

//**********************************************************************//

Object3D * EntranceRootMap::getObject(){
    return object;
}


