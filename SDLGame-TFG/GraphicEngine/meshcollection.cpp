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

#include "meshcollection.h"

MeshCollection* MeshCollection::instance = NULL;


MeshCollection::MeshCollection()
{
    Mesh * element=new Mesh("geometries/cube.obj");
    element->init();
    collection.push_back(element);

    element=new Mesh("geometries/fence.obj");
    element->init();
    collection.push_back(element);

    element=new Mesh("geometries/tree.obj");
    element->init();
    collection.push_back(element);

    element=new Mesh("geometries/grass.obj");
    element->init();
    collection.push_back(element);

    element=new Mesh("geometries/mushroomWhite.obj");
    element->init();
    collection.push_back(element);

    element=new Mesh("geometries/treeDie.obj");
    element->init();
    collection.push_back(element);

    element=new Mesh("geometries/sphereBackground.obj");
    element->init();
    collection.push_back(element);
}


//**********************************************************************//

MeshCollection::~MeshCollection()
{
    //dtor
}

//**********************************************************************//

Mesh * MeshCollection::getMesh(int i){
    return collection[i];
}
