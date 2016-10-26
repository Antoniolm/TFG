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

#ifndef CAMERA_H
#define CAMERA_H

#include "structdata.h"
#include "matrix4f.h"
#include <glew.h>

class Camera
{
    public:
        /** Default constructor */
        Camera();
        Camera(vec3f eye,vec3f aTarget,vec3f aUp);
        /** Default destructor */
        virtual ~Camera();

        Matrix4f & getCamera();
        GLfloat * getView();

    protected:

    private:
        Matrix4f camera;
        vec3f position;
        vec3f target;
        vec3f up;
        vec3f zCamera;
        vec3f yCamera;
        vec3f xCamera;
};

#endif // CAMERA_H
