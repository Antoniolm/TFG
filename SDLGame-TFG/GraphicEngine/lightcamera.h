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

#ifndef LIGHTCAMERA_H
#define LIGHTCAMERA_H

#include "structdata.h"
#include "matrix4f.h"

class LightCamera
{
    public:
        /** Default constructor */
        LightCamera();
        /** Default destructor */
        virtual ~LightCamera();

        void createLightSpace();
        void setCamera(vec3f eye,vec3f aTarget,vec3f aUp);
        void setOrthoProyection(float left,float right,float bottom,float top,float nearPro = -1.0f,float farPro = 1.0f );
        Matrix4f getCamera();
        Matrix4f getOrthoProyection();
        Matrix4f getLightSpace();
    protected:

    private:
        Matrix4f camera;
        Matrix4f proyection;
        Matrix4f lightSpace;

};

#endif // LIGHTCAMERA_H
