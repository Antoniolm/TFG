#ifndef STRUCTDATA2_H
#define STRUCTDATA2_H
#include "object3d.h"

class Object3D;

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
        Matrix4f * matrix;
        Object3D * object;
    };
    EntranceMap(){}
    EntranceMap(Object3D * aObject){
        object=aObject;
        type=0;
	}
	EntranceMap(Object3D * aObject,Matrix4f * pMatrix){
        object=aObject;
        cout<< "Wat happen herere"<< endl;
        matrix=new Matrix4f((*pMatrix));
        type=1;
	}

};

#endif
