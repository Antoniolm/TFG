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
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Camera();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Constructor with parameters
        *   \param eye -> Position of the camera
        *   \param Target -> Target of the camera
        *   \param up -> The inclination of the camera
        */
        //////////////////////////////////////////////////////////////////////////
        Camera(vec3f eye,vec3f aTarget,vec3f aUp);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Camera();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Set the value of some parameters in the object
        *   \param eye -> Position of the camera
        *   \param Target -> Target of the camera
        *   \param up -> The inclination of the camera
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setCamera(vec3f eye,vec3f aTarget,vec3f aUp);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Set the value for the projection
        *   \param fov
        *   \param aspect
        *   \param near
        *   \param far
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setPerspectiveProjection(float fov, float aspect, float near, float far);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Set the value for the projection
        *   \param left
        *   \param right
        *   \param bottom
        *   \param top
        *   \param near
        *   \param far
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setOrthographicProjection(float left,float right,float bottom,float top,float near = -1.0f,float far = 1.0f );

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will create the matrix of the object
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void createCamera();


        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will move the position of our camera
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void moveCamera(const Matrix4f & transformation);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will return our matrix camera
        *   \return Matrix4f
        */
        //////////////////////////////////////////////////////////////////////////
        Matrix4f & getCamera();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will return our projection
        *   \return GLfloat
        */
        //////////////////////////////////////////////////////////////////////////
        GLfloat * getProjection();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will return our camera
        *   \return GLfloat
         */
        //////////////////////////////////////////////////////////////////////////
        GLfloat * getView();

    protected:

    private:
        Matrix4f camera;
        Matrix4f projection;
        vec3f position;
        vec3f target;
        vec3f up;
};

#endif // CAMERA_H
