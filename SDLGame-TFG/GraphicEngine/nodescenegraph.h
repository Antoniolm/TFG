////////////////////////////////////////
//  Author: Antonio David López Machado
////////////////////////////////////////


#ifndef NODESCENEGRAPH_H
#define NODESCENEGRAPH_H

#include "object3d.h"
#include "context.h"
#include "matrix4fdinamic.h"
#include "matrix4f.h"
#include <vector>

using namespace std;

/////////////////////////////////////////////////////////////////////////
/**
*    Struct --> Our NodeSceneGraph will contain one or more object of this type
*    That struct can contain a matrix4fDinamic or an Object3D
*/
//////////////////////////////////////////////////////////////////////////
struct EntranceNGE
{
	unsigned char type;   //0=subscene, 1=Transformation

	union
	{
        Object3D * obj;   //ptr. to Object3D
        Matrix4f * matrix;   //ptr. to matrix4fDinamico
	};

	EntranceNGE(Object3D * aObject){
        obj=aObject;
        type=0;
	}
	EntranceNGE(Matrix4f * pMatrix){
        matrix=pMatrix;
        type=1;
	}
};

//**********************************************************************//

class NodeSceneGraph : public Object3D
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Constructor
        */
        /////////////////////////////////////////////////////////////////////////
        NodeSceneGraph();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Destructor
        */
        /////////////////////////////////////////////////////////////////////////
        virtual ~NodeSceneGraph();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        /////////////////////////////////////////////////////////////////////////
        virtual void visualization(Context & cv);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void updateState(float time);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will add a new element in our NodeSceneGraph
        *    \return void
        */
        /////////////////////////////////////////////////////////////////////////
        void add(EntranceNGE * anEntrance);

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

    protected:

    private:
        vector<EntranceNGE> entrance;
};

#endif // NODESCENEGRAPH_H
