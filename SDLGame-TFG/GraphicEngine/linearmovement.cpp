////////////////////////////////////////
//  Author: Antonio David L�pez Machado
////////////////////////////////////////

#include "linearmovement.h"

LinearMovement::LinearMovement()
{
    //ctor
}

//**********************************************************************//

LinearMovement::~LinearMovement()
{
    //dtor
}

//**********************************************************************//

Matrix4f LinearMovement::updateState(float time){
    return currentMatrix;
}
