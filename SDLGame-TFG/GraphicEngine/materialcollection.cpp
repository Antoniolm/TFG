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

#include "materialcollection.h"

MaterialCollection* MaterialCollection::instance = NULL;

MaterialCollection::MaterialCollection()
{
    Material * material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 1.0f, 1.0f),vec3f(0.0f, 0.0f, 0.0f),32.0f,"./textures/cubeGrass.png");
    collection.push_back(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/cubeSand.png");
    collection.push_back(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 1.0f, 1.0f),vec3f(0.0f, 0.0f, 0.0f),32.0f,"./textures/cubeLand.png");
    collection.push_back(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/cubeBox.png");
    collection.push_back(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/cubeDungeon.png");
    collection.push_back(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/cubeWall.png");
    collection.push_back(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/Wood.png");
    collection.push_back(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/mushrooms.png");
    collection.push_back(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/grass.png");
    collection.push_back(material);

    material=new Material(vec3f(0.5f, 0.5f, 1.0f),vec3f(0.5f, 0.5f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/water.png");
    collection.push_back(material);

    material=new Material(vec3f(0.5f, 0.5f, 1.0f),vec3f(0.5f, 0.5f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/void.png");
    collection.push_back(material);

    material=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(0.5f, 0.5f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/TEX_crystal.png");
    collection.push_back(material);

    material=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(0.5f, 0.5f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/textureCoin50.png");
    collection.push_back(material);

    //Hero material
    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 1.0f, 1.0f),32.0f,"./textures/heroTexture.jpg");
    collection.push_back(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/swordTexture.png");
    collection.push_back(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/shieldTexture.png");
    collection.push_back(material);

    //Enemy material
    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.3f, 0.3f, 0.3f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/enemyTexture.png");
    collection.push_back(material);

    material=new Material(vec3f(0.3f, 0.3f, 0.3f),vec3f(0.3f, 0.3f, 0.3f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/textureLeg.png");
    collection.push_back(material);

    //Text Material
    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"textures/dialog.png");
    collection.push_back(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"textures/actionDialog.png");
    collection.push_back(material);

    //NPC
    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"textures/butlerTexture.png");
    collection.push_back(material);

    //Scene Material
    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"textures/furniture.png");
    collection.push_back(material);


    //Create our map
    enumMap.insert(pair<string,MaterialIndex> ("mCUBE_GRASS",mCUBE_GRASS));
    enumMap.insert(pair<string,MaterialIndex> ("mCUBE_SAND",mCUBE_SAND));
    enumMap.insert(pair<string,MaterialIndex> ("mCUBE_LAND",mCUBE_LAND));
    enumMap.insert(pair<string,MaterialIndex> ("mCUBE_BOX",mCUBE_BOX));
    enumMap.insert(pair<string,MaterialIndex> ("mCUBE_DUNG",mCUBE_DUNG));
    enumMap.insert(pair<string,MaterialIndex> ("mCUBE_WALL",mCUBE_WALL));
    enumMap.insert(pair<string,MaterialIndex> ("mWOOD",mWOOD));
    enumMap.insert(pair<string,MaterialIndex> ("MUSH",MUSH));
    enumMap.insert(pair<string,MaterialIndex> ("mGRASS",mGRASS));
    enumMap.insert(pair<string,MaterialIndex> ("mWATER",mWATER));
    enumMap.insert(pair<string,MaterialIndex> ("mVOID",mVOID));
    enumMap.insert(pair<string,MaterialIndex> ("mCOIN10",mCOIN10));
    enumMap.insert(pair<string,MaterialIndex> ("mCOIN50",mCOIN50));
    enumMap.insert(pair<string,MaterialIndex> ("mARMOUR",mARMOUR));
    enumMap.insert(pair<string,MaterialIndex> ("mSWORD",mSWORD));
    enumMap.insert(pair<string,MaterialIndex> ("mSHIELD",mSHIELD));
    enumMap.insert(pair<string,MaterialIndex> ("mENEMY",mENEMY));
    enumMap.insert(pair<string,MaterialIndex> ("mDHAND",mDHAND));
    enumMap.insert(pair<string,MaterialIndex> ("mDIALOG",mDIALOG));
    enumMap.insert(pair<string,MaterialIndex> ("mADIALOG",mADIALOG));
    enumMap.insert(pair<string,MaterialIndex> ("mBUTLER",mBUTLER));
    enumMap.insert(pair<string,MaterialIndex> ("mFURNITURE",mFURNITURE));

}

//**********************************************************************//

MaterialCollection::~MaterialCollection()
{
    if(instance!=NULL){
        vector<Material *>::iterator it;
        for(it=collection.begin();it!=collection.end();it++){
            delete (*it);
        }
        instance=NULL;
    }
}

//**********************************************************************//

Material* MaterialCollection::getMaterial(MaterialIndex element){
    return collection[element];
}

//**********************************************************************//

Material* MaterialCollection::getMaterial(string element){
    return collection[(enumMap.find(element))->second];
}
