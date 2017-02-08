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

#ifndef CONTEXT_H
#define CONTEXT_H

#include "matrixstack.h"
#include "structdata.h"
#include "materialcollection.h"
#include "object3d.h"
#include "materialstack.h"
#include "light.h"
#include "shader.h"
#include <vector>

class MaterialStack;
class Object3D;
class Context
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Context();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Context();

        unsigned int visualization_mode;
        unsigned camera_mode;
        MatrixStack matrixStack;
        MaterialStack materialStack;
        Shader currentShader;
        Matrix4f currentTransf;
        MaterialIndex currentMaterialIndex;
        vec3f minVisualPosition,maxVisualPosition;


    protected:

    private:
};

#endif // CONTEXT_H
