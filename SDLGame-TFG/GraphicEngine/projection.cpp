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

#include "projection.h"

Projection::Projection()
{
    //ctor
}

//**********************************************************************//

Projection::~Projection()
{
    //dtor
}

//**********************************************************************//

void Projection::createPerspective(float fov, float aspect, float near, float far){
    float top, right,left,bottom;
    top =(float) (near * tan(fov * 3.1416 / 360.0));
    right = top * aspect;
    left= -right;
    bottom=-top;

    GLfloat * matrix=new GLfloat[16];
    matrix[0]=(2*near)/(right-left);    matrix[1]=0;                        matrix[2]=(right+left)/(right-left);  matrix[3]=0;
	matrix[4]=0;                        matrix[5]=(2*near)/(top-bottom);    matrix[6]=(top+bottom)/(top-bottom);  matrix[7]=0;
	matrix[8]=0;                        matrix[9]=0;                        matrix[10]=-((far+near)/(far-near));  matrix[11]=-((2*far*near)/(far-near));
	matrix[12]=0;                       matrix[13]=0;                       matrix[14]=-1;                        matrix[15]=0;

    perspective.setMatrix(matrix);
}

//**********************************************************************//

void Projection::createOrthographic(float left,float right,float bottom,float top,float near,float far ){
    cout<< "pedo de mono"<<endl;
    GLfloat * matrix=new GLfloat[16];
    matrix[0]=2/(right-left);           matrix[1]=0;                        matrix[2]=0;                 matrix[3]=((right+left)/(right-left));
	matrix[4]=0;                        matrix[5]=2/(top-bottom);           matrix[6]=0;                 matrix[7]=((top+bottom)/(top-bottom));
	matrix[8]=0;                        matrix[9]=0;                        matrix[10]=(-2/(far-near));  matrix[11]=((far+near)/(far-near));
	matrix[12]=0;                       matrix[13]=0;                       matrix[14]=0;                matrix[15]=1;

	perspective.setMatrix(matrix);
}

//**********************************************************************//

Matrix4f Projection::getMatrix(){
    return perspective;
}

//**********************************************************************//

GLfloat * Projection::getProjection(){
    return perspective.getMatrix();
}
