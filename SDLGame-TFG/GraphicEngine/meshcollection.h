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

#ifndef MESHCOLLECTION_H
#define MESHCOLLECTION_H

#include "mesh.h"
#include "collection.h"
#include "collection.cpp"
class Mesh;

using namespace std;

enum MeshIndex{
    CUBE,       //0
    SPHERE,
    BACKGROUND, //6
    KNEE,       //7
    KNEE2,      //7
    SWORD,      //8
    SHIELD,     //9
    HAND,       //10
    HANDS,
    TOPARM,     //11
    CHEST,      //12
    HEAD,       //15
    TEXT,       //17
    COIN,        //18
    EHEAD,
    ECHEST,
    EHAND,
    EFOOT,
    BUTLER,
    BED,
    CUPBOARD,
    BEDSIDETABLE,
    ARROW
};

class MeshCollection
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~MeshCollection();

        static MeshCollection * getInstance(){
            if(instance == NULL)
                instance = new MeshCollection();

            return instance;
        }

        Mesh * getMesh(MeshIndex element);
        Mesh * getMesh(string element);

    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor  */
        //////////////////////////////////////////////////////////////////////////
        MeshCollection();

        static MeshCollection* instance;
        Collection<Mesh,MeshIndex> collection;
};

#endif // MESHCOLLECTION_H
