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

#include "matrix4f.h"

Matrix4f::Matrix4f()
{
    matrix=new GLfloat[16];
}

//**********************************************************************//

Matrix4f::~Matrix4f()
{
    delete [] matrix;
}

Matrix4f::Matrix4f(const Matrix4f & aMatrix){
    matrix=new GLfloat[16];
    const GLfloat * apoint=aMatrix.getMatrixc();
    for(int i=0;i<16;i++){
        matrix[i]=apoint[i];
    }
}

//**********************************************************************//

void Matrix4f::translation(float x,float y,float z){
    matrix[0]=1;  matrix[1]=0;  matrix[2]=0;  matrix[3]=0;
	matrix[4]=0;  matrix[5]=1;  matrix[6]=0;  matrix[7]=0;
	matrix[8]=0;  matrix[9]=0;  matrix[10]=1; matrix[11]=0;
	matrix[12]=x; matrix[13]=y; matrix[14]=z; matrix[15]=1;
}

//**********************************************************************//

void Matrix4f::scale(float x,float y,float z){

	matrix[0]= x; matrix[1]=0;  matrix[2]=0;  matrix[3]=0;
	matrix[4]=0;  matrix[5]=y;  matrix[6]=0;  matrix[7]=0;
	matrix[8]=0;  matrix[9]=0;  matrix[10]=z; matrix[11]=0;
	matrix[12]=0; matrix[13]=0; matrix[14]=0; matrix[15]=1;

}

//**********************************************************************//

void Matrix4f::rotation(float grade,const float x,const float y,const float z){
    float rad=(grade*3.14159)/180.0;

    matrix[0]= cos(rad)+((x*x)*(1-cos(rad)));     matrix[1]=((x*y)*(1-cos(rad)))-z*sin(rad);  matrix[2]=((x*z)*(1-cos(rad)))+y*sin(rad);   matrix[3]=0;
    matrix[4]=((y*x)*(1-cos(rad)))+z*sin(rad);    matrix[5]=cos(rad)+((y*y)*(1-cos(rad)));    matrix[6]=((y*z)*(1-cos(rad)))-x*sin(rad);   matrix[7]=0;
    matrix[8]=((z*x)*(1-cos(rad)))-y*sin(rad);    matrix[9]=((z*y)*(1-cos(rad)))+x*sin(rad);  matrix[10]=cos(rad)+((z*z)*(1-cos(rad)));    matrix[11]=0;
    matrix[12]=0;                                 matrix[13]=0;                               matrix[14]=0;                                matrix[15]=1;
}

//**********************************************************************//

void Matrix4f::identity(){
    matrix[0]=1;  matrix[1]=0;  matrix[2]=0;  matrix[3]=0;
	matrix[4]=0;  matrix[5]=1;  matrix[6]=0;  matrix[7]=0;
	matrix[8]=0;  matrix[9]=0;  matrix[10]=1; matrix[11]=0;
	matrix[12]=0; matrix[13]=0; matrix[14]=0; matrix[15]=1;
}

//**********************************************************************//

void Matrix4f::product(const GLfloat * aMatrix){
        GLfloat * newMatrix=new GLfloat[16];
        for(int j=0;j<16;j=j+4){
            for(int k=0;k<4;k++){
                newMatrix[j+k]=(matrix[j]*aMatrix[k])+(matrix[j+1]*aMatrix[k+4])+(matrix[j+2]*aMatrix[k+8])+(matrix[j+3]*aMatrix[k+12]);
            }
        }
        delete [] matrix;
        matrix=newMatrix;
}

//**********************************************************************//

vec4f Matrix4f::product(const vec4f aVector){
        vec4f result(0.0,0.0,0.0,1.0);
        GLfloat * newMatrix=new GLfloat[16];
        int cont=0;
        //cout<< "VECTOR --> x : "<<aVector.x<< ", y : "<< aVector.y<< ", z : "<< aVector.z << ", w : "<< aVector.w<< endl;
        for(int j=0;j<16;j=j+4){
            result.setValue(cont,(matrix[j]*aVector.x)+(matrix[j+1]*aVector.y)+(matrix[j+2]*aVector.z)+(matrix[j+3]*aVector.w));
            cont++;
        }
        //cout<< "RESULT --> x : "<<result.x<< ", y : "<< result.y<< ", z : "<< result.z << ", w : "<< result.w<< endl;
        return result;
}

//**********************************************************************//

GLfloat * Matrix4f::getMatrix(){
    return matrix;
}

//**********************************************************************//

const GLfloat * Matrix4f::getMatrixc() const{
    return matrix;
}



