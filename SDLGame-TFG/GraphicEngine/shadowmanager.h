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

#ifndef SHADOWMANAGER_H
#define SHADOWMANAGER_H

#include "shadowtexture.h"
#include "shader.h"
#include "matrix/matrix4f.h"
#include "camera.h"
#include "matrix/structdata.h"

class ShadowManager
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        ShadowManager(Shader * aShader);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~ShadowManager();

        void setOrthoProjection(float left,float right,float bottom,float top,float nearPro,float farPro);
        void setCamera(vec3f posLight,vec3f targetLight, vec3f upLight);
        Camera * getCamera();

        void setShader(Shader * aShader);
        Shader * getShader();

        void generateShadow(GameState & gameState);
        void activateShadowTexture();
        Matrix4f & getLightSpace();
    protected:

    private:
        Shader * shader;
        Camera * lightCamera;
        Matrix4f lightSpace;
        ShadowTexture * depthTexture;

};

#endif // SHADOWMANAGER_H
