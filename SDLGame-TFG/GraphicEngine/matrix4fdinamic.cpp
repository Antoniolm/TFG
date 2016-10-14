////////////////////////////////////////
//  Author: Antonio David López Machado
////////////////////////////////////////

#include "matrix4fdinamic.h"

Matrix4fDinamic::Matrix4fDinamic()
{
    //ctor
}

//**********************************************************************//

Matrix4fDinamic::~Matrix4fDinamic()
{
    //dtor
}

//**********************************************************************//

Matrix4f Matrix4fDinamic::updateState(float time){
    return currentMatrix;
}
