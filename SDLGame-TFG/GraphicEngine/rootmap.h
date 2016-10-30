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

#ifndef ROOTMAP_H
#define ROOTMAP_H

#include "object3d.h"
#include "nodescenegraph.h"
#include <list>
#include <vector>
#include "matrix4f.h"
#include "matrix4fdinamic.h"
#include "linearmovement.h"
#include "axisrotation.h"
#include "matrixstatic.h"
#include "oscillaterotation.h"
#include "mesh.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////
/**
*    Struct --> This object contain the information for an objectStatic
*    On this way, We only need to create the transformation matrix one time
*/
//////////////////////////////////////////////////////////////////////////
struct ObjectStatic{
    Object3D * object;
    Matrix4f * matrix;
};

/////////////////////////////////////////////////////////////////////////
/**
*    Struct --> Our RootMap will contain one or more object of this type
*    That struct can contain an objectStatic or an objectDinamic
*/
//////////////////////////////////////////////////////////////////////////
struct EntranceMap{
    unsigned char type; // 0= object Dinamic , 1= Object static
    vec3f position;

    union{
        ObjectStatic objectStatic;
        Object3D * objectDinamic;
    };
};

class RootMap : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Default constructor */
        //////////////////////////////////////////////////////////////////////////
        RootMap();

        //////////////////////////////////////////////////////////////////////////
        /** Default destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~RootMap();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        /////////////////////////////////////////////////////////////////////////
        virtual void visualization(Context & vis);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void updateState(float time);

        void initStatic();
    protected:

    private:
        list<Object3D *> object;
        list<Object3D *> objectStatic;
        list<Object3D *> objectDinamic;
};

#endif // ROOTMAP_H
