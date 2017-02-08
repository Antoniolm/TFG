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
    mCUBE_GRASS, //0
    mCUBE_BOX,   //3
    mCUBE_DUNG,   //3
    mCUBE_DUNGB,
    mCUBE_WALL,
    mCUBE_TRAP,
    mWATER,      //7
    mDWATER,      //7
    mVOID,       //8
    mCRYSTAL,     //9
    mHERO,     //11
    mSWORD,       //12
    mSHIELD,       //12
    mENEMY,      //13
    mARCHENEMY,      //14
    mDIALOG,     //15
    mADIALOG,     //16
    mBUTLER,
    mFURNITURE,
    mFIREPLACE,
    mRUG,
    mFIRE,
    mWINDOW,
    mPILLAR,
    mBED,
    mTORCH,
    mCHANDELIER,
    mFLAG,
    mCOLUMN,
    mPOTION,
    mMATE,
    mCHAIR,
    mWOOD,
    mBOOKS

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
