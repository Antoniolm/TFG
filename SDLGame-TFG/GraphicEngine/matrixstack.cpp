// *********************************************************************
// **
// ** Copyright (C) 2016 Antonio David López Machado
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

#include "matrixstack.h"

MatrixStack::MatrixStack()
{
    //ctor
}

//**********************************************************************//

MatrixStack::~MatrixStack()
{
    //dtor
}

//**********************************************************************//

void MatrixStack::push(){
    currentMatrix=new Matrix4f();
    currentMatrix->identity();
    mainStack.push_back((*currentMatrix));
}

//**********************************************************************//

void MatrixStack::pop(){
    mainStack.pop_back();
    currentMatrix=&mainStack[mainStack.size()-1];

}

//**********************************************************************//

void MatrixStack::asignIdentity(){
    currentMatrix->identity();
}

//**********************************************************************//

void MatrixStack::cMatrix( Matrix4f & mat ){
    currentMatrix->product(mat.getMatrix());
}

//**********************************************************************//

void MatrixStack::cTraslation( const float dx, const float dy, const float dz ){
    Matrix4f auxMatrix;
    auxMatrix.translation(dx,dy,dz);
    currentMatrix->product(auxMatrix.getMatrix());
}

//**********************************************************************//

void MatrixStack::cScale ( const float sx, const float sy, const float sz ){
    Matrix4f auxMatrix;
    auxMatrix.scale(sx,sy,sz);
    currentMatrix->product(auxMatrix.getMatrix());
}

//**********************************************************************//

void MatrixStack::cRotation ( const float ang_gra,const float ex, const float ey, const float ez ){

}

//**********************************************************************//

GLfloat * MatrixStack::getMatrix(){
    return currentMatrix->getMatrix();
}
