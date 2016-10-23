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
    int tam=mainStack.size();
    currentMatrix=new Matrix4f();

    if(tam>0){
        currentMatrix=new Matrix4f(mainStack[tam-1]);
    }
    else{
        currentMatrix->identity();
    }
    mainStack.push_back((*currentMatrix));
}

//**********************************************************************//

void MatrixStack::pop(){
    mainStack.pop_back();
    if(mainStack.size()>0)
        currentMatrix=&mainStack[mainStack.size()-1];
    else{
        currentMatrix->identity();
    }

}

//**********************************************************************//

void MatrixStack::asignIdentity(){
    currentMatrix->identity();
}

//**********************************************************************//

void MatrixStack::cMatrix( Matrix4f & mat ){
    currentMatrix->product(mat.getMatrix());
    mainStack[mainStack.size()-1]=(*currentMatrix);
}

//**********************************************************************//

void MatrixStack::cTraslation( const float dx, const float dy, const float dz ){
    Matrix4f auxMatrix;
    auxMatrix.translation(dx,dy,dz);
    currentMatrix->product(auxMatrix.getMatrix());
    mainStack[mainStack.size()-1]=(*currentMatrix);
}

//**********************************************************************//

void MatrixStack::cScale ( const float sx, const float sy, const float sz ){
    Matrix4f auxMatrix;
    auxMatrix.scale(sx,sy,sz);
    currentMatrix->product(auxMatrix.getMatrix());
    mainStack[mainStack.size()-1]=(*currentMatrix);
}

//**********************************************************************//

void MatrixStack::cRotation ( const float ang_gra,const float ex, const float ey, const float ez ){
    Matrix4f auxMatrix;
    auxMatrix.rotation(ang_gra,ex,ey,ez);
    currentMatrix->product(auxMatrix.getMatrix());
    mainStack[mainStack.size()-1]=(*currentMatrix);
}

//**********************************************************************//

Matrix4f * MatrixStack::getMatrix(){
    return currentMatrix;
}
