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

#include "camera.h"

Camera::Camera(){

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
    float f=(float) 1/tan((fov * 3.1416) / 360.0);

    //Create the projection
    GLfloat * matrix=new GLfloat[16];
    matrix[0]=f/(aspect);  matrix[1]=0;        matrix[2]=0;                          matrix[3]=0;
	matrix[4]=0;                matrix[5]=f;   matrix[6]=0;                          matrix[7]=0;
	matrix[8]=0;                matrix[9]=0;   matrix[10]=(far+near)/(near-far);    matrix[11]=-1.0f;
	matrix[12]=0;               matrix[13]=0;  matrix[14]=(2.0f*far*near)/(near-far); matrix[15]=0;

    projection.setMatrix(matrix);
}

//**********************************************************************//

void Camera::setOrthographicProjection(float left,float right,float bottom,float top,float near,float far){

    //Create the projection
    GLfloat * projec=new GLfloat[16];
    projec[0]=2.0f/(right-left);        projec[1]=0;                        projec[2]=0;                 projec[3]=((right+left)/(right-left));
	projec[4]=0;                        projec[5]=2.0f/(top-bottom);        projec[6]=0;                 projec[7]=((top+bottom)/(top-bottom));
	projec[8]=0;                        projec[9]=0;                        projec[10]=(-2.0f/(far-near));  projec[11]=((far+near)/(far-near));
	projec[12]=0;                       projec[13]=0;                       projec[14]=0;                projec[15]=1;

	projection.setMatrix(projec);
}

//**********************************************************************//

void Camera::createCamera(){
    vec3f zCamera;
    vec3f yCamera;
    vec3f xCamera;
    float modulo;

    //Calculate the z-Axis
    zCamera=position-target;
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
	matrix[12]=-(xCamera.dot(position)); matrix[13]=-(yCamera.dot(position)); matrix[14]=-(zCamera.dot(position)); matrix[15]=1;

	camera.setMatrix(matrix);
}

//**********************************************************************//

void Camera::activateCamera(Shader * shader){
    GLint viewLocation= glGetUniformLocation(shader->getProgram(),"view");
    glUniformMatrix4fv(viewLocation,1,GL_FALSE,camera.getMatrix());

    GLint projectionLocation= glGetUniformLocation(shader->getProgram(),"projection");
    glUniformMatrix4fv(projectionLocation,1,GL_FALSE,projection.getMatrix());

    GLint viewPosLoc = glGetUniformLocation(shader->getProgram(), "viewPos");
    glUniform3f(viewPosLoc, position.x, position.y, position.z);
}

//**********************************************************************//

void Camera::moveCamera(vec3f pos,Shader *shader){

    position.x=pos.x;position.y=pos.y+2.0f;position.z=pos.z+3.0f;
    target.x=pos.x;target.y=pos.y;target.z=pos.z;
    createCamera();

    GLint viewLocation= glGetUniformLocation(shader->getProgram(),"view");
    glUniformMatrix4fv(viewLocation,1,GL_FALSE,camera.getMatrix());

    GLint viewPosLoc = glGetUniformLocation(shader->getProgram(), "viewPos");
    glUniform3f(viewPosLoc, position.x, position.y, position.z);
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

//**********************************************************************//

vec3f Camera::getPosition(){
    return position;
}

//**********************************************************************//

vec3f Camera::getTarget(){
    return target;
}

//**********************************************************************//

vec3f Camera::getUp(){
    return up;
}
