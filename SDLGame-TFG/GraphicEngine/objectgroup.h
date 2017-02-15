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


#ifndef OBJECTGROUP_H
#define OBJECTGROUP_H

#include "materialcollection.h"
#include "nodescenegraph.h"
#include "meshcollection.h"

class ObjectGroup : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        ObjectGroup(MaterialIndex materialIndex);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~ObjectGroup();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will add another object to our group of object
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void addObject(vec3f position,MeshIndex meshIndex);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will init our group of object( init his mesh)
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void init();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        /////////////////////////////////////////////////////////////////////////
        void visualization(Context & vis);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateState(GameState & gameState);
    protected:

    private:
        vector<vec3f> vertex;
        vector<GLushort> triangles;
        vector<vec3f> normals;
        vector<vec2f> textureCord;
        NodeSceneGraph * root;
};

#endif // OBJECTGROUP_H
