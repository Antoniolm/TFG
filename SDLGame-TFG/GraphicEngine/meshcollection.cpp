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

#include "meshcollection.h"

MeshCollection* MeshCollection::instance = NULL;


MeshCollection::MeshCollection()
{
    //Mesh 0
    Mesh * element=new Mesh("geometries/cube.obj");
    element->init();
    collection.push_back(element);

    //Mesh 1
    element=new Mesh("geometries/fence.obj");
    element->init();
    collection.push_back(element);

    //Mesh 2
    element=new Mesh("geometries/tree.obj");
    element->init();
    collection.push_back(element);

    //Mesh 3
    element=new Mesh("geometries/grass.obj");
    element->init();
    collection.push_back(element);

    //Mesh 4
    element=new Mesh("geometries/mushroomWhite.obj");
    element->init();
    collection.push_back(element);

    //Mesh 5
    element=new Mesh("geometries/treeDie.obj");
    element->init();
    collection.push_back(element);

    //Mesh 6
    element=new Mesh("geometries/sphereBackground.obj");
    element->init();
    collection.push_back(element);

    //Hero-Enemy mesh
    //Mesh 7
    element=new Mesh("geometries/knee.obj");
    element->init();
    collection.push_back(element);

    //Mesh 8
    element=new Mesh("geometries/armour2.obj");
    element->init();
    collection.push_back(element);

    //Mesh 9
    element=new Mesh("geometries/armourChest.obj");
    element->init();
    collection.push_back(element);

    //Mesh 10
    element=new Mesh("geometries/hand.obj");
    element->init();
    collection.push_back(element);

    //Mesh 11
    element=new Mesh("geometries/topArm.obj");
    element->init();
    collection.push_back(element);

    //Mesh 12
    element=new Mesh("geometries/chest.obj");
    element->init();
    collection.push_back(element);

    //Mesh 13
    element=new Mesh("geometries/foot.obj");
    element->init();
    collection.push_back(element);

    //Mesh 14
    element=new Mesh("geometries/hip.obj");
    element->init();
    collection.push_back(element);

    //Mesh 15
    element=new Mesh("geometries/head.obj");
    element->init();
    collection.push_back(element);

    //Mesh 16
    element=new Mesh("geometries/armour.obj");
    element->init();
    collection.push_back(element);

    //Text-menu mesh
    //Mesh 17
    element=new Mesh("geometries/text.obj");
    element->init();
    collection.push_back(element);

    //Coin mesh
    //Mesh 18
    element=new Mesh("geometries/coin.obj");
    element->init();
    collection.push_back(element);

    //Create our map
    enumMap.insert(pair<string,meshElement> ("CUBE",CUBE));
    enumMap.insert(pair<string,meshElement> ("FENCE",FENCE));
    enumMap.insert(pair<string,meshElement> ("TREE",TREE));
    enumMap.insert(pair<string,meshElement> ("GRASS",GRASS));
    enumMap.insert(pair<string,meshElement> ("MUSHWHITE",MUSHWHITE));
    enumMap.insert(pair<string,meshElement> ("TREEDIE",TREEDIE));
    enumMap.insert(pair<string,meshElement> ("BACKGROUND",BACKGROUND));
    enumMap.insert(pair<string,meshElement> ("KNEE",KNEE));
    enumMap.insert(pair<string,meshElement> ("ARMOUR2",ARMOUR2));
    enumMap.insert(pair<string,meshElement> ("ARMOURCHEST",ARMOURCHEST));
    enumMap.insert(pair<string,meshElement> ("HAND",HAND));
    enumMap.insert(pair<string,meshElement> ("TOPARM",TOPARM));
    enumMap.insert(pair<string,meshElement> ("CHEST",CHEST));
    enumMap.insert(pair<string,meshElement> ("FOOT",FOOT));
    enumMap.insert(pair<string,meshElement> ("HIP",HIP));
    enumMap.insert(pair<string,meshElement> ("HEAD",HEAD));
    enumMap.insert(pair<string,meshElement> ("ARMOUR",ARMOUR));
    enumMap.insert(pair<string,meshElement> ("TEXT",TEXT));
    enumMap.insert(pair<string,meshElement> ("COIN",COIN));
}

//**********************************************************************//

MeshCollection::~MeshCollection()
{
    if(instance!=NULL){
        vector<Mesh *>::iterator it;
        for(it=collection.begin();it!=collection.end();it++){
            delete (*it);
        }
        instance=NULL;
    }
}

//**********************************************************************//

Mesh * MeshCollection::getMesh(meshElement element){
    return collection[element];
}

//**********************************************************************//

Mesh * MeshCollection::getMesh(string element){
    return collection[(enumMap.find(element))->second];
}
