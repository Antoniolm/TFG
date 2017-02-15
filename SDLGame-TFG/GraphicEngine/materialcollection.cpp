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

#include "materialcollection.h"
#include "material.h"

MaterialCollection* MaterialCollection::instance = NULL;

MaterialCollection::MaterialCollection()
{
    Material * material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 1.0f, 1.0f),vec3f(0.0f, 0.0f, 0.0f),16.0f,"./textures/cubeGrass.png",mCUBE_GRASS);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/cubeBox.png",mCUBE_BOX);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/cubeDungeon.png",mCUBE_DUNG);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/cubeDungeonB.png",mCUBE_DUNGB);
    collection.addElement(material);

    material=new Material(vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/cubeWall.png",mCUBE_WALL);
    collection.addElement(material);

    material=new Material(vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/cubeTrap.png",mCUBE_TRAP);
    collection.addElement(material);

    material=new Material(vec3f(0.5f, 0.5f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/water.png",mWATER);
    collection.addElement(material);

    material=new Material(vec3f(0.5f, 1.0f, 0.5f),vec3f(0.5f, 1.0f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/water.png",mDWATER);
    collection.addElement(material);

    material=new Material(vec3f(0.5f, 0.5f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/void.png",mVOID);
    collection.addElement(material);

    material=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/TEX_crystal.png",mCRYSTAL);
    collection.addElement(material);

    //Hero material
    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 1.0f, 1.0f),16.0f,"./textures/heroTexture.jpg",mHERO);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/swordTexture.png",mSWORD);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/shieldTexture.png",mSHIELD);
    collection.addElement(material);

    //Enemy material
    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/enemyTexture.png",mENEMY);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"./textures/archerTexture.png",mARCHENEMY);
    collection.addElement(material);

    //Text Material
    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/dialog.png",mDIALOG);
    collection.addElement(material);

    material=new Material(vec3f(0.6f, 0.6f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/dialog.png",mBDIALOG);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/actionDialog.png",mADIALOG);
    collection.addElement(material);

    //NPC
    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/butlerTexture.png",mBUTLER);
    collection.addElement(material);

    //Scene Material
    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/furnitureText.png",mFURNITURE);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/fpTexture.png",mFIREPLACE);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/rugTexture.png",mRUG);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/fireTexture.png",mFIRE);
    collection.addElement(material);

    material=new Material(vec3f(0.8f, 0.8f, 0.8f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.0f, 0.0f, 0.0f),16.0f,"textures/windowTex.png",mWINDOW);
    collection.addElement(material);

    material=new Material(vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.0f, 0.0f, 0.0f),16.0f,"textures/pillar.png",mPILLAR);
    collection.addElement(material);

    material=new Material(vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.0f, 0.0f, 0.0f),16.0f,"textures/bedTexture.png",mBED);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/torch.png",mTORCH);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/chandelier.png",mCHANDELIER);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/flag.png",mFLAG);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/column.png",mCOLUMN);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/potionTexture.png",mPOTION);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/mateTexture.png",mMATE);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/chairTexture.png",mCHAIR);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/tableTexture.png",mWOOD);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/bookTexture.png",mBOOKS);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/trunkTexture.png",mTRUNK);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/spikeTexture.png",mSPIKE);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/gamepadV.png",mGMPADV);
    collection.addElement(material);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),16.0f,"textures/gamepadX.png",mGMPADX);
    collection.addElement(material);

    //Create our map
    collection.addIndex("mCUBE_GRASS",mCUBE_GRASS);
    collection.addIndex("mCUBE_BOX",mCUBE_BOX);
    collection.addIndex("mCUBE_DUNG",mCUBE_DUNG);
    collection.addIndex("mCUBE_DUNGB",mCUBE_DUNGB);
    collection.addIndex("mCUBE_WALL",mCUBE_WALL);
    collection.addIndex("mCUBE_TRAP",mCUBE_TRAP);
    collection.addIndex("mWATER",mWATER);
    collection.addIndex("mDWATER",mDWATER);
    collection.addIndex("mVOID",mVOID);
    collection.addIndex("mCRYSTAL",mCRYSTAL);
    collection.addIndex("mHERO",mHERO);
    collection.addIndex("mSWORD",mSWORD);
    collection.addIndex("mSHIELD",mSHIELD);
    collection.addIndex("mENEMY",mENEMY);
    collection.addIndex("mARCHENEMY",mARCHENEMY);
    collection.addIndex("mDIALOG",mDIALOG);
    collection.addIndex("mBDIALOG",mBDIALOG);
    collection.addIndex("mADIALOG",mADIALOG);
    collection.addIndex("mBUTLER",mBUTLER);
    collection.addIndex("mFURNITURE",mFURNITURE);
    collection.addIndex("mFIREPLACE",mFIREPLACE);
    collection.addIndex("mRUG",mRUG);
    collection.addIndex("mFIRE",mFIRE);
    collection.addIndex("mWINDOW",mWINDOW);
    collection.addIndex("mPILLAR",mPILLAR);
    collection.addIndex("mBED",mBED);
    collection.addIndex("mTORCH",mTORCH);
    collection.addIndex("mCHANDELIER",mCHANDELIER);
    collection.addIndex("mFLAG",mFLAG);
    collection.addIndex("mCOLUMN",mCOLUMN);
    collection.addIndex("mPOTION",mPOTION);
    collection.addIndex("mMATE",mMATE);
    collection.addIndex("mCHAIR",mCHAIR);
    collection.addIndex("mWOOD",mWOOD);
    collection.addIndex("mBOOKS",mBOOKS);
    collection.addIndex("mTRUNK",mTRUNK);
    collection.addIndex("mSPIKE",mSPIKE);
    collection.addIndex("mGMPADV",mGMPADV);
    collection.addIndex("mGMPADX",mGMPADX);

}

//**********************************************************************//

MaterialCollection::~MaterialCollection()
{
}

//**********************************************************************//

Material* MaterialCollection::getMaterial(MaterialIndex element){
    return collection.getElement(element);
}

//**********************************************************************//

Material* MaterialCollection::getMaterial(string element){
    return collection.getElement(element);
}
