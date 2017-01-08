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

#include "material.h"
#include <vector>
#include <map>
#include <string>

using namespace std;

enum materialElement{
    mCUBE_GRASS, //0
    mCUBE_SAND,  //1
    mCUBE_LAND,  //2
    mCUBE_BOX,   //3
    mCUBE_DUNG,   //3
    mCUBE_WALL,
    mWOOD,       //4
    MUSH,        //5
    mGRASS,      //6
    mWATER,      //7
    mVOID,       //8
    mCOIN10,     //9
    mCOIN50,     //10
    mARMOUR,     //11
    mSWORD,       //12
    mSHIELD,       //12
    mENEMY,      //13
    mDHAND,      //14
    mDIALOG,     //15
    mADIALOG     //16
};


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

        Material * getMaterial(materialElement element);
        Material * getMaterial(string element);
    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        MaterialCollection();

        static MaterialCollection* instance;
        vector<Material *> collection;
        map<string,materialElement> enumMap;
};

#endif // MATERIALCOLLECTION_H
