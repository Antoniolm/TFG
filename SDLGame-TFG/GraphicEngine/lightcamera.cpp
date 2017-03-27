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

#include "lightcamera.h"

LightCamera::LightCamera()
{
    //ctor
}

//**********************************************************************//

LightCamera::~LightCamera()
{
    //dtor
}

//**********************************************************************//

void LightCamera::createLightSpace(){
    lightSpace.setMatrix(camera.getMatrix());
    lightSpace.product(proyection.getMatrix());
}

//**********************************************************************//

void LightCamera::setCamera(vec3f eye,vec3f target,vec3f up){
    vec3f zCamera;
    vec3f yCamera;
    vec3f xCamera;

    //Calculate the z-Axis
    zCamera=eye-target;
    zCamera.normalize();

    //Calculate the x-Axis
    xCamera=up.cross(zCamera);
    xCamera.normalize();

    //Calculate the y-Axis
    yCamera=zCamera.cross(xCamera);

    //Create the camera
    GLfloat * matrix=new GLfloat[16];
    matrix[0]=xCamera.x;  matrix[1]=yCamera.x;  matrix[2]=zCamera.x;  matrix[3]=0;
	matrix[4]=xCamera.y;  matrix[5]=yCamera.y;  matrix[6]=zCamera.y;  matrix[7]=0;
	matrix[8]=xCamera.z;  matrix[9]=yCamera.z;  matrix[10]=zCamera.z; matrix[11]=0;
	matrix[12]=-(xCamera.dot(eye)); matrix[13]=-(yCamera.dot(eye)); matrix[14]=-(zCamera.dot(eye)); matrix[15]=1;

	camera.setMatrix(matrix);
}

//**********************************************************************//

void LightCamera::setOrthoProyection(float left,float right,float bottom,float top,float nearPro,float farPro){
    //Create the projection
    GLfloat * projec=new GLfloat[16];
    projec[0]=2.0f/(right-left);        projec[1]=0;                        projec[2]=0;                 projec[3]=((right+left)/(right-left));
	projec[4]=0;                        projec[5]=2.0f/(top-bottom);        projec[6]=0;                 projec[7]=((top+bottom)/(top-bottom));
	projec[8]=0;                        projec[9]=0;                        projec[10]=-2.0f/(farPro-nearPro); projec[11]=0.0;
	projec[12]=0;                       projec[13]=0;                       projec[14]=-(farPro+nearPro)/(farPro-nearPro);projec[15]=1;

	proyection.setMatrix(projec);
}

//**********************************************************************//

Matrix4f LightCamera::getCamera(){
    return camera;
}

//**********************************************************************//

Matrix4f LightCamera::getOrthoProyection(){
    return proyection;
}

//**********************************************************************//

Matrix4f LightCamera::getLightSpace(){
    return lightSpace;
}
