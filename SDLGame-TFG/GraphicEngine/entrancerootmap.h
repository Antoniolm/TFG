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

#ifndef ENTRANCEROOTMAP_H
#define ENTRANCEROOTMAP_H

#include "object3d.h"
#include "matrix4f.h"

class Object3D;

class EntranceRootMap
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        EntranceRootMap();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters
        *   \param aObject -> Reference to our object
        */
        //////////////////////////////////////////////////////////////////////////
        EntranceRootMap(Object3D * aObject);

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters
        *   \param aObject -> Reference to our object
        *   \param pMatrix -> Reference to the transformation matrix of our object
        */
        //////////////////////////////////////////////////////////////////////////
        EntranceRootMap(Object3D * aObject,Matrix4f * pMatrix);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~EntranceRootMap();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    \return Return our transformation matrix4f
        */
        //////////////////////////////////////////////////////////////////////////
        Matrix4f * getMatrix();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    \return Return our object
        */
        //////////////////////////////////////////////////////////////////////////
        Object3D * getObject();

    protected:

    private:
        unsigned char type; // 0= object Dinamic , 1= Object static
        vec3f position;

        Matrix4f * matrix;
        Object3D * object;

};

#endif // ENTRANCEROOTMAP_H
