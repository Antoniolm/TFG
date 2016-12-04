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


#ifndef NODESCENEGRAPH_H
#define NODESCENEGRAPH_H

#include "object3d.h"
#include "context.h"
#include "matrix4fdynamic.h"
#include "matrix4f.h"
#include "material.h"
#include <vector>
#include <SDL.h>

using namespace std;

/////////////////////////////////////////////////////////////////////////
/**
*    Struct --> Our NodeSceneGraph will contain one or more object of this type
*    That struct can contain a matrix4fDinamic or an Object3D
*/
//////////////////////////////////////////////////////////////////////////
struct EntryNGE
{
	unsigned type;   //0=subscene, 1=Transformation, 2=Material

	union
	{
        Object3D * obj;   //ptr. to Object3D
        Matrix4f * matrix;   //ptr. to matrix4f
        Material * material; //ptr. to Material
	};

	EntryNGE(Object3D * aObject){
        obj=aObject;
        type=0;
	}
	EntryNGE(Matrix4f * pMatrix){
        matrix=pMatrix;
        type=1;
	}
    EntryNGE(Material * aMaterial){
        material=aMaterial;
        type=2;
	}
};

//**********************************************************************//

class NodeSceneGraph : public Object3D
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        /////////////////////////////////////////////////////////////////////////
        NodeSceneGraph();

        //////////////////////////////////////////////////////////////////////////
        /** Copy constructor */
        /////////////////////////////////////////////////////////////////////////
        NodeSceneGraph(const NodeSceneGraph & aNode);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        /////////////////////////////////////////////////////////////////////////
        virtual ~NodeSceneGraph();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        /////////////////////////////////////////////////////////////////////////
        void visualization(Context & cv);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateState(float time);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will obtain the boundingBox of the object.
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        BoundingBox getBoundingBox();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will add a new element in our NodeSceneGraph
        *    \return void
        */
        /////////////////////////////////////////////////////////////////////////
        void add(EntryNGE * anEntry);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will add a new element in our NodeSceneGraph
        *    \return void
        */
        /////////////////////////////////////////////////////////////////////////
        void add(Object3D * anObject);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will add a new element in our NodeSceneGraph
        *    \return void
        */
        /////////////////////////////////////////////////////////////////////////
        void add(Matrix4f * aMatrix);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will add a new element in our NodeSceneGraph
        *    \return void
        */
        /////////////////////////////////////////////////////////////////////////
        void add(Material * aMaterial);

    protected:

    private:
        vector<EntryNGE> entrance;
};

#endif // NODESCENEGRAPH_H
