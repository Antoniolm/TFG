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

#ifndef CONTEXT_H
#define CONTEXT_H

#include "matrixstack.h"
#include "camera.h"
#include "structdata.h"
#include "projection.h"
#include "object3d.h"
#include <list>

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
        bool visualization_static;
        unsigned visualization_mode;
        unsigned camera_mode;
        MatrixStack matrixStack;
        Camera camera;
        list<Object3D *> posObject;

    protected:

    private:
};

#endif // CONTEXT_H
