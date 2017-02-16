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

#ifndef MATERIALCOLLECTION_H
#define MATERIALCOLLECTION_H

#include <vector>
#include <map>
#include "collection.h"
#include "collection.cpp"
#include <string>

using namespace std;

enum MaterialIndex{
    mCUBE_GRASS,    //0
    mCUBE_BOX,      //1
    mCUBE_DUNG,     //2
    mCUBE_DUNGB,    //3
    mCUBE_WALL,     //4
    mCUBE_TRAP,     //5
    mWATER,         //6
    mDWATER,        //7
    mVOID,          //8
    mCRYSTAL,       //9
    mHERO,          //10
    mSWORD,         //11
    mSHIELD,        //12
    mENEMY,         //13
    mARCHENEMY,     //14
    mDIALOG,        //15
    mBDIALOG,       //16
    mADIALOG,       //17
    mBUTLER,        //18
    mFURNITURE,     //19
    mFIREPLACE,     //20
    mRUG,           //21
    mFIRE,          //22
    mWINDOW,        //23
    mPILLAR,        //24
    mBED,           //25
    mTORCH,         //26
    mCHANDELIER,    //27
    mFLAG,          //28
    mCOLUMN,        //29
    mPOTION,        //30
    mMATE,          //31
    mCHAIR,         //32
    mWOOD,          //33
    mBOOKS,         //34
    mTRUNK,         //35
    mSPIKE,         //36
    mGMPADV,
    mGMPADX,
    mTITLE1
};

class Material;
class MaterialCollection
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~MaterialCollection();

        static MaterialCollection * getInstance(){
            if(instance == NULL)
                instance = new MaterialCollection();

            return instance;
        }

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return a material -> parameters MaterialIndex
        *    \return Material *
        */
        //////////////////////////////////////////////////////////////////////////
        Material * getMaterial(MaterialIndex element);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return a material -> parameters string
        *    \return Material *
        */
        //////////////////////////////////////////////////////////////////////////
        Material * getMaterial(string element);

    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        MaterialCollection();

        static MaterialCollection* instance;
        Collection<Material,MaterialIndex> collection;
};

#endif // MATERIALCOLLECTION_H
