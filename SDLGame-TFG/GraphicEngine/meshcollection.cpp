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
    collection.addElement(element);

    element=new Mesh("geometries/sphere.obj");
    element->init();
    collection.addElement(element);

    //Mesh 6
    element=new Mesh("geometries/sphereBackground.obj");
    element->init();
    collection.addElement(element);

    //Hero-Enemy mesh
    //Mesh 7
    element=new Mesh("geometries/knightFoot.obj");
    element->init();
    collection.addElement(element);

    //Mesh 8
    element=new Mesh("geometries/knightFootInv.obj");
    element->init();
    collection.addElement(element);

    //Mesh 9
    element=new Mesh("geometries/sword.obj");
    element->init();
    collection.addElement(element);

    //Mesh 10
    element=new Mesh("geometries/shield.obj");
    element->init();
    collection.addElement(element);

    //Mesh 11
    element=new Mesh("geometries/KnightHand.obj");
    element->init();
    collection.addElement(element);

    element=new Mesh("geometries/KnightHandShield.obj");
    element->init();
    collection.addElement(element);

    //Mesh 12
    element=new Mesh("geometries/KnightArm.obj");
    element->init();
    collection.addElement(element);

    //Mesh 13
    element=new Mesh("geometries/KnightBody.obj");
    element->init();
    collection.addElement(element);

    //Mesh 16
    element=new Mesh("geometries/KnightHead.obj");
    element->init();
    collection.addElement(element);

    //Text-menu mesh
    //Mesh 18
    element=new Mesh("geometries/text.obj");
    element->init();
    collection.addElement(element);

    //Coin mesh
    //Mesh 19
    element=new Mesh("geometries/crystal.obj");
    element->init();
    collection.addElement(element);

    //Enemy mesh
    //Mesh 19
    element=new Mesh("geometries/enemyHead.obj");
    element->init();
    collection.addElement(element);

    //Mesh 19
    element=new Mesh("geometries/enemyBody.obj");
    element->init();
    collection.addElement(element);

    //Mesh 19
    element=new Mesh("geometries/enemyHand.obj");
    element->init();
    collection.addElement(element);

    //Mesh 19
    element=new Mesh("geometries/enemyFoot.obj");
    element->init();
    collection.addElement(element);

    //NPC mesh
    //Mesh 19
    element=new Mesh("geometries/ghostButler.obj");
    element->init();
    collection.addElement(element);

    //scene mesh
    //Mesh 19
    element=new Mesh("geometries/bed.obj");
    element->init();
    collection.addElement(element);

    element=new Mesh("geometries/cupBoard.obj");
    element->init();
    collection.addElement(element);

    element=new Mesh("geometries/bedsideTable.obj");
    element->init();
    collection.addElement(element);

    element=new Mesh("geometries/arrow.obj");
    element->init();
    collection.addElement(element);

    //Create our map
    collection.addIndex("CUBE",CUBE);
    collection.addIndex("SPHERE",SPHERE);
    collection.addIndex("BACKGROUND",BACKGROUND);
    collection.addIndex("KNEE",KNEE);
    collection.addIndex("KNEE2",KNEE2);
    collection.addIndex("SWORD",SWORD);
    collection.addIndex("SHIELD",SHIELD);
    collection.addIndex("HAND",HAND);
    collection.addIndex("HANDS",HANDS);
    collection.addIndex("TOPARM",TOPARM);
    collection.addIndex("CHEST",CHEST);
    collection.addIndex("HEAD",HEAD);
    collection.addIndex("TEXT",TEXT);
    collection.addIndex("COIN",COIN);
    collection.addIndex("EHEAD",EHEAD);
    collection.addIndex("ECHEST",ECHEST);
    collection.addIndex("EHAND",EHAND);
    collection.addIndex("EFOOT",EFOOT);
    collection.addIndex("BUTLER",BUTLER);
    collection.addIndex("BED",BED);
    collection.addIndex("CUPBOARD",CUPBOARD);
    collection.addIndex("BEDSIDETABLE",BEDSIDETABLE);
    collection.addIndex("ARROW",ARROW);
}

//**********************************************************************//

MeshCollection::~MeshCollection()
{
    if(instance!=NULL){

        instance=NULL;
    }
}

//**********************************************************************//

Mesh * MeshCollection::getMesh(MeshIndex element){
    return collection.getElement(element);
}

//**********************************************************************//

Mesh * MeshCollection::getMesh(string element){
    return collection.getElement(element);
}
