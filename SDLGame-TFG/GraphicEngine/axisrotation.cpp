////////////////////////////////////////
//  Author: Antonio David L�pez Machado
////////////////////////////////////////

#include "axisrotation.h"

AxisRotation::AxisRotation()
{
    //ctor
}

//**********************************************************************//

AxisRotation::~AxisRotation()
{
    //dtor
}

//**********************************************************************//

Matrix4f AxisRotation::updateState(float time){
    return currentMatrix;
}
