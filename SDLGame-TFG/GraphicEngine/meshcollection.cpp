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
    //Mesh 0
    Mesh * element=new Mesh("geometries/cube.obj",true);
    collection.addElement(element);

    element=new Mesh("geometries/sphere.obj");
    collection.addElement(element);

    //Mesh 6
    element=new Mesh("geometries/sphereBackground.obj");
    collection.addElement(element);

    //Hero-Enemy mesh
    //Mesh 7
    element=new Mesh("geometries/knightFoot.obj");
    collection.addElement(element);

    //Mesh 8
    element=new Mesh("geometries/knightFootInv.obj");
    collection.addElement(element);

    //Mesh 9
    element=new Mesh("geometries/sword.obj");
    collection.addElement(element);

    //Mesh 10
    element=new Mesh("geometries/shield.obj");
    collection.addElement(element);

    //Mesh 11
    element=new Mesh("geometries/knightHand.obj");
    collection.addElement(element);

    element=new Mesh("geometries/knightHandShield.obj");
    collection.addElement(element);

    //Mesh 12
    element=new Mesh("geometries/knightArm.obj");
    collection.addElement(element);

    //Mesh 13
    element=new Mesh("geometries/knightBody.obj");
    collection.addElement(element);

    //Mesh 16
    element=new Mesh("geometries/knightHead.obj");
    collection.addElement(element);

    //Text-menu mesh
    //Mesh 18
    element=new Mesh("geometries/text.obj");
    collection.addElement(element);

    //Coin mesh
    //Mesh 19
    element=new Mesh("geometries/crystal.obj");
    collection.addElement(element);

    //Enemy Melee mesh
    //Mesh 19
    element=new Mesh("geometries/enemyHead.obj");
    collection.addElement(element);

    //Mesh 19
    element=new Mesh("geometries/enemyBody.obj");
    collection.addElement(element);

    //Mesh 19
    element=new Mesh("geometries/enemyHand.obj");
    collection.addElement(element);

    //Mesh 19
    element=new Mesh("geometries/enemyFoot.obj");
    collection.addElement(element);

    //Enemy Ranged mesh
    //Mesh 19
    element=new Mesh("geometries/rangedHead.obj");
    collection.addElement(element);

    //Mesh 19
    element=new Mesh("geometries/rangedBody.obj");
    collection.addElement(element);

    //Mesh 19
    element=new Mesh("geometries/rangedHand.obj");
    collection.addElement(element);

    //Mesh 19
    element=new Mesh("geometries/rangedFoot.obj");
    collection.addElement(element);


    //NPC mesh
    //Mesh 19
    element=new Mesh("geometries/ghostButler.obj");
    collection.addElement(element);

    //scene mesh
    //Mesh 19
    element=new Mesh("geometries/bed.obj");
    collection.addElement(element);

    element=new Mesh("geometries/cupBoard.obj");
    collection.addElement(element);

    element=new Mesh("geometries/bedsideTable.obj");
    collection.addElement(element);

    element=new Mesh("geometries/arrow.obj");
    collection.addElement(element);

    element=new Mesh("geometries/bookShelf.obj");
    collection.addElement(element);

    element=new Mesh("geometries/firePlace.obj");
    collection.addElement(element);

    element=new Mesh("geometries/smallTable.obj");
    collection.addElement(element);

    element=new Mesh("geometries/chair.obj");
    collection.addElement(element);

    element=new Mesh("geometries/rug.obj");
    collection.addElement(element);

    element=new Mesh("geometries/window.obj");
    collection.addElement(element);

    element=new Mesh("geometries/pillar.obj");
    collection.addElement(element);

    element=new Mesh("geometries/crossbow.obj");
    collection.addElement(element);

    element=new Mesh("geometries/club.obj");
    collection.addElement(element);

    element=new Mesh("geometries/torch.obj");
    collection.addElement(element);

    element=new Mesh("geometries/chandelier.obj");
    collection.addElement(element);

    element=new Mesh("geometries/barrel.obj");
    collection.addElement(element);

    element=new Mesh("geometries/candleHolder.obj");
    collection.addElement(element);

    element=new Mesh("geometries/flag.obj");
    collection.addElement(element);

    element=new Mesh("geometries/bench.obj");
    collection.addElement(element);

    element=new Mesh("geometries/column.obj");
    collection.addElement(element);

    element=new Mesh("geometries/potion.obj");
    collection.addElement(element);

    element=new Mesh("geometries/mateHead.obj");
    collection.addElement(element);

    element=new Mesh("geometries/mateHand.obj");
    collection.addElement(element);

    element=new Mesh("geometries/books.obj");
    collection.addElement(element);

    element=new Mesh("geometries/trunk.obj");
    collection.addElement(element);

    element=new Mesh("geometries/ladder.obj");
    collection.addElement(element);

    element=new Mesh("geometries/spikes.obj");
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
    collection.addIndex("RHEAD",RHEAD);
    collection.addIndex("RCHEST",RCHEST);
    collection.addIndex("RHAND",RHAND);
    collection.addIndex("RFOOT",RFOOT);
    collection.addIndex("BUTLER",BUTLER);
    collection.addIndex("BED",BED);
    collection.addIndex("CUPBOARD",CUPBOARD);
    collection.addIndex("BEDSIDETABLE",BEDSIDETABLE);
    collection.addIndex("ARROW",ARROW);
    collection.addIndex("BKSHELF",BKSHELF);
    collection.addIndex("FIREPLACE",FIREPLACE);
    collection.addIndex("SMALLTABLE",SMALLTABLE);
    collection.addIndex("CHAIR",CHAIR);
    collection.addIndex("RUG",RUG);
    collection.addIndex("WINDOW",WINDOW);
    collection.addIndex("PILLAR",PILLAR);
    collection.addIndex("CBOW",CBOW);
    collection.addIndex("CLUB",CLUB);
    collection.addIndex("TORCH",TORCH);
    collection.addIndex("CHANDELIER",CHANDELIER);
    collection.addIndex("BARREL",BARREL);
    collection.addIndex("CHOLDER",CHOLDER);
    collection.addIndex("FLAG",FLAG);
    collection.addIndex("BENCH",BENCH);
    collection.addIndex("COLUMN",COLUMN);
    collection.addIndex("POTION",POTION);
    collection.addIndex("MATEHEAD",MATEHEAD);
    collection.addIndex("MATEHAND",MATEHAND);
    collection.addIndex("BOOKS",BOOKS);
    collection.addIndex("TRUNK",TRUNK);
    collection.addIndex("LADDER",LADDER);
    collection.addIndex("SPIKE",SPIKE);
}

//**********************************************************************//

MeshCollection::~MeshCollection()
{
   /*if(instance!=NULL){
        instance=NULL;
    }*/
}

//**********************************************************************//

Mesh * MeshCollection::getMesh(MeshIndex element){
    return collection.getElement(element);
}

//**********************************************************************//

Mesh * MeshCollection::getMesh(string element){
    return collection.getElement(element);
}
