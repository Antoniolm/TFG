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

#include "matrixstack.h"

MatrixStack::MatrixStack()
{

}

//**********************************************************************//

MatrixStack::~MatrixStack()
{
    //dtor
}

//**********************************************************************//

void MatrixStack::push(){
    int tam=mainStack.size();

    currentMatrix.identity();
    Matrix4f newMatrix(currentMatrix);
    pair<int,Matrix4f> aux;
    aux.first=0;
    aux.second=newMatrix;
    mainStack.push_back(aux);
}

//**********************************************************************//

void MatrixStack::pop(){
    vector<pair<int,Matrix4f> >::reverse_iterator it;
    bool finish=false;

    for(it=mainStack.rbegin();it!=mainStack.rend() && !finish;it++){
        if((*it).first==0){
            finish=false;
        }
        mainStack.erase(it.base());
    }
    //mainStack.pop_back();
    for(int i=0;i<mainStack.size();i++){
        cout<< "<"<< mainStack[i].first<<"> "<<endl;
        GLfloat *matrix=mainStack[i].second.getMatrix();
        cout<< matrix[0]<< " "<<matrix[1]<< " "<<matrix[2]<< " "<<matrix[3]<< " "<< endl;
        cout<< matrix[4]<< " "<<matrix[5]<< " "<<matrix[6]<< " "<<matrix[7]<< " "<< endl;
        cout<< matrix[8]<< " "<<matrix[9]<< " "<<matrix[10]<< " "<<matrix[11]<< " "<< endl;
        cout<< matrix[12]<< " "<<matrix[13]<< " "<<matrix[14]<< " "<<matrix[15]<< " "<< endl;
    }


}

//**********************************************************************//

void MatrixStack::asignIdentity(){
    currentMatrix.identity();
}

//**********************************************************************//

void MatrixStack::cMatrix(int cont,const Matrix4f & mat ){
    Matrix4f newMatrix(mat);
    pair<int,Matrix4f> aux;
    aux.first=cont;
    aux.second=newMatrix;
    mainStack.push_back(aux);
    //currentMatrix.product(mat.getMatrixc());
    //mainStack[mainStack.size()-1]=*new Matrix4f(currentMatrix);

}

//**********************************************************************//

void MatrixStack::cTraslation( const float dx, const float dy, const float dz ){
    /*Matrix4f auxMatrix;
    auxMatrix.translation(dx,dy,dz);
    currentMatrix.product(auxMatrix.getMatrix());
    mainStack[mainStack.size()-1]=currentMatrix;*/
}

//**********************************************************************//

void MatrixStack::cScale ( const float sx, const float sy, const float sz ){
    /*Matrix4f auxMatrix;
    auxMatrix.scale(sx,sy,sz);
    currentMatrix.product(auxMatrix.getMatrix());
    mainStack[mainStack.size()-1]=currentMatrix;*/
}

//**********************************************************************//

void MatrixStack::cRotation ( const float ang_gra,const float ex, const float ey, const float ez ){
    /*Matrix4f auxMatrix;
    auxMatrix.rotation(ang_gra,ex,ey,ez);
    currentMatrix.product(auxMatrix.getMatrix());
    mainStack[mainStack.size()-1]=currentMatrix;*/
}

void MatrixStack::clean(){
    mainStack.clear();
}
//**********************************************************************//

Matrix4f & MatrixStack::getMatrix(){
    vector<pair<int,Matrix4f> >::reverse_iterator it;
    bool finish=false;

    currentMatrix.identity();
    for(it=mainStack.rbegin();it!=mainStack.rend() && !finish;it++){
        if((*it).first==0){
            finish=false;
        }
        currentMatrix.product((*it).second.getMatrix());
    }
    it--;

    /*currentMatrix.identity();
    vector<pair<int,Matrix4f> >::iterator it2;
    it2=it.base();
    for(;it2!=mainStack.end() && !finish;it2++){
        currentMatrix.product((*it2).second.getMatrix());
    }*/
    return currentMatrix;
}
