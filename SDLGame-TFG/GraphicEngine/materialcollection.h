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

using namespace std;

enum materialElement{
    mCUBE_GRASS, //0
    mCUBE_SAND,  //1
    mCUBE_BOX,   //2
    mWOOD,       //3
    MUSH,       //4
    mGRASS,      //5
    mWATER,      //6
    mVOID,       //7
    mCOIN        //8
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
    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        MaterialCollection();

        static MaterialCollection* instance;
        vector<Material *> collection;
};

#endif // MATERIALCOLLECTION_H
