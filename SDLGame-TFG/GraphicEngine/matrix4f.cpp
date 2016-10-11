////////////////////////////////////////
//  Author: Antonio David López Machado
////////////////////////////////////////

#include "matrix4f.h"

Matrix4f::Matrix4f()
{
    matrix=new GLdouble[16];
}

//**********************************************************************\\

Matrix4f::~Matrix4f()
{
    delete [] matrix;
}

//**********************************************************************\\

void Matrix4f::translation(double x,double y,double z){
    matrix[0]= 1; matrix[1]=0; matrix[2]=0; matrix[3]=0;
	matrix[4]=0; matrix[5]=1; matrix[6]=0; matrix[7]=0;
	matrix[8]=0; matrix[9]=0; matrix[10]=1; matrix[11]=0;
	matrix[12]=x; matrix[13]=y; matrix[14]=z; matrix[15]=1;
}

//**********************************************************************\\

void Matrix4f::scale(double x,double y,double z){

	matrix[0]= x; matrix[1]=0; matrix[2]=0; matrix[3]=0;
	matrix[4]=0; matrix[5]=y; matrix[6]=0; matrix[7]=0;
	matrix[8]=0; matrix[9]=0; matrix[10]=z; matrix[11]=0;
	matrix[12]=0; matrix[13]=0; matrix[14]=0; matrix[15]=1;

}

//**********************************************************************\\

void Matrix4f::rotation(){}



//**********************************************************************\\

GLdouble * Matrix4f::getMatrix(){
    return matrix;
}
