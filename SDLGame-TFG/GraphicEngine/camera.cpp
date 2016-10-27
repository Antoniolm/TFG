// *********************************************************************
// **
// ** Copyright (C) 2016-2017 Antonio David L�pez Machado
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

#include "camera.h"

Camera::Camera()
{
    position=vec3f(0.0,0.0,1.0);
    target=vec3f(0.0,0.0,0.0);
    up=vec3f(0.0,1.0,0.0);
}

//**********************************************************************//

Camera::Camera(vec3f eye,vec3f aTarget,vec3f aUp){
    position=eye;
    target=aTarget;
    up=aUp;

    createCamera();
}

//**********************************************************************//

Camera::~Camera()
{
    //dtor
}

//**********************************************************************//

void Camera::setCamera(vec3f eye,vec3f aTarget,vec3f aUp){
    position=eye;
    target=aTarget;
    up=aUp;

}

//**********************************************************************//

void Camera::setPerspectiveProjection(float fov, float aspect, float near, float far){
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

    projection.setMatrix(matrix);
}

//**********************************************************************//

void Camera::setOrthographicProjection(float left,float right,float bottom,float top,float near,float far){
    GLfloat * projec=new GLfloat[16];
    projec[0]=2/(right-left);           projec[1]=0;                        projec[2]=0;                 projec[3]=((right+left)/(right-left));
	projec[4]=0;                        projec[5]=2/(top-bottom);           projec[6]=0;                 projec[7]=((top+bottom)/(top-bottom));
	projec[8]=0;                        projec[9]=0;                        projec[10]=(-2/(far-near));  projec[11]=((far+near)/(far-near));
	projec[12]=0;                       projec[13]=0;                       projec[14]=0;                projec[15]=1;

	projection.setMatrix(projec);
}

//**********************************************************************//

void Camera::createCamera(){
    vec3f zCamera;
    vec3f yCamera;
    vec3f xCamera;

    zCamera=position-target;
    float modulo=zCamera.normalize();
    zCamera.x=zCamera.x/modulo;
    zCamera.y=zCamera.y/modulo;
    zCamera.z=zCamera.z/modulo;

    xCamera=up.cross(zCamera);
    modulo=xCamera.normalize();
    xCamera.x=xCamera.x/modulo;
    xCamera.y=xCamera.y/modulo;
    xCamera.z=xCamera.z/modulo;

    yCamera=zCamera.cross(xCamera);
    modulo=yCamera.normalize();
    yCamera.x=yCamera.x/modulo;
    yCamera.y=yCamera.y/modulo;
    yCamera.z=yCamera.z/modulo;

    GLfloat * matrix=new GLfloat[16];
    matrix[0]=xCamera.x;  matrix[1]=xCamera.y;  matrix[2]=xCamera.z;  matrix[3]=0;
	matrix[4]=yCamera.x;  matrix[5]=yCamera.y;  matrix[6]=yCamera.y;  matrix[7]=0;
	matrix[8]=zCamera.x;  matrix[9]=zCamera.y;  matrix[10]=zCamera.z; matrix[11]=0;
	matrix[12]=-position.x; matrix[13]=-position.y; matrix[14]=-position.z; matrix[15]=1;

	camera.setMatrix(matrix);
}

//**********************************************************************//

Matrix4f & Camera::getCamera(){
    return camera;
}

//**********************************************************************//

GLfloat * Camera::getProjection(){
    return projection.getMatrix();
}

//**********************************************************************//

GLfloat * Camera::getView(){
    return camera.getMatrix();
}
