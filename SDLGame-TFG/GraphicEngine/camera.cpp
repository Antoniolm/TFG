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

Camera::Camera()
{
    position=vec3f(0.0,0.0,-3.0);
    target=vec3f(0.0,0.0,1.0);
    up=vec3f(0.0,1.0,0.0);
}

//**********************************************************************//

Camera::Camera(vec3f eye,vec3f aTarget,vec3f aUp){
    position=eye;
    target=aTarget;
    up=aUp;
    zCamera=position-target;
    float modulo=zCamera.normalize();
    cout<< "Modulo :"<< modulo;
    zCamera.x=zCamera.x/modulo;
    zCamera.y=zCamera.y/modulo;
    zCamera.z=zCamera.z/modulo;

    cout<< "Prueba"<< endl;
    cout<< "X : "<< zCamera.x<<endl;
    cout<< "Y : "<< zCamera.y<<endl;
    cout<< "Z : "<< zCamera.z<<endl;

    xCamera=up.cross(zCamera);
    modulo=xCamera.normalize();
    xCamera.x=xCamera.x/modulo;
    xCamera.y=xCamera.y/modulo;
    xCamera.z=xCamera.z/modulo;

    cout<< "Prueba"<< endl;
    cout<< "X : "<< xCamera.x<<endl;
    cout<< "Y : "<< xCamera.y<<endl;
    cout<< "Z : "<< xCamera.z<<endl;

    yCamera=zCamera.cross(xCamera);
    modulo=yCamera.normalize();
    yCamera.x=yCamera.x/modulo;
    yCamera.y=yCamera.y/modulo;
    yCamera.z=yCamera.z/modulo;

    cout<< "Prueba"<< endl;
    cout<< "X : "<< yCamera.x<<endl;
    cout<< "Y : "<< yCamera.y<<endl;
    cout<< "Z : "<< yCamera.z<<endl;

    GLfloat * matrix=new GLfloat[16];
    matrix[0]=xCamera.x;  matrix[1]=xCamera.y;  matrix[2]=xCamera.z;  matrix[3]=0;
	matrix[4]=yCamera.x;  matrix[5]=yCamera.y;  matrix[6]=yCamera.y;  matrix[7]=0;
	matrix[8]=zCamera.x;  matrix[9]=zCamera.y;  matrix[10]=zCamera.z; matrix[11]=0;
	matrix[12]=-position.x; matrix[13]=-position.y; matrix[14]=-position.z; matrix[15]=1;

	camera.setMatrix(matrix);
}

//**********************************************************************//

Camera::~Camera()
{
    //dtor
}

//**********************************************************************//

Matrix4f & Camera::getCamera(){
    return camera;
}

//**********************************************************************//

GLfloat * Camera::getView(){
    return camera.getMatrix();
}
