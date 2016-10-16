////////////////////////////////////////
//  Author: Antonio David López Machado
////////////////////////////////////////

#include "matrix4f.h"

Matrix4f::Matrix4f()
{
    matrix=new GLdouble[16];
}

//**********************************************************************//

Matrix4f::~Matrix4f()
{
    delete [] matrix;
}

//**********************************************************************//

void Matrix4f::translation(double x,double y,double z){
    matrix[0]= 1; matrix[1]=0;  matrix[2]=0;  matrix[3]=0;
	matrix[4]=0;  matrix[5]=1;  matrix[6]=0;  matrix[7]=0;
	matrix[8]=0;  matrix[9]=0;  matrix[10]=1; matrix[11]=0;
	matrix[12]=x; matrix[13]=y; matrix[14]=z; matrix[15]=1;
}

//**********************************************************************//

void Matrix4f::scale(double x,double y,double z){

	matrix[0]= x; matrix[1]=0;  matrix[2]=0;  matrix[3]=0;
	matrix[4]=0;  matrix[5]=y;  matrix[6]=0;  matrix[7]=0;
	matrix[8]=0;  matrix[9]=0;  matrix[10]=z; matrix[11]=0;
	matrix[12]=0; matrix[13]=0; matrix[14]=0; matrix[15]=1;

}

//**********************************************************************//

void Matrix4f::rotation(float grade,const float x,const float y,const float z){
    int rad=(grade/180)*3.1416;

    if(x>0){
        matrix[0]= 1; matrix[1]=0;          matrix[2]=0;            matrix[3]=0;
        matrix[4]=0;  matrix[5]=cos(rad);   matrix[6]=sin(rad);   matrix[7]=0;
        matrix[8]=0;  matrix[9]=-sin(rad);  matrix[10]=cos(rad);  matrix[11]=0;
        matrix[12]=0; matrix[13]=0;         matrix[14]=0;           matrix[15]=1;
    }
    else if(y>0){
        matrix[0]= cos(rad); matrix[1]=0;   matrix[2]=sin(rad); matrix[3]=0;
        matrix[4]=0;         matrix[5]=1;   matrix[6]=0;        matrix[7]=0;
        matrix[8]=-sin(rad); matrix[9]=0;   matrix[10]=cos(rad);matrix[11]=0;
        matrix[12]=0;        matrix[13]=0;  matrix[14]=0;       matrix[15]=1;
    }
    else if(z>0){
        matrix[0]= cos(rad); matrix[1]=sin(rad);  matrix[2]=0;  matrix[3]=0;
        matrix[4]=-sin(rad); matrix[5]=cos(rad);  matrix[6]=0;  matrix[7]=0;
        matrix[8]=0;         matrix[9]=0;         matrix[10]=1; matrix[11]=0;
        matrix[12]=0;        matrix[13]=0;        matrix[14]=0; matrix[15]=1;
    }

}


//**********************************************************************//

GLdouble * Matrix4f::getMatrix(){
    return matrix;
}
