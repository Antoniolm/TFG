// *********************************************************************
// **
// ** Copyright (C) 2016 Antonio David L�pez Machado
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

#ifndef AXISROTATION_H
#define AXISROTATION_H

#include "matrix4fdinamic.h"

class AxisRotation : public Matrix4fDinamic
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Constructor
        */
        //////////////////////////////////////////////////////////////////////////
        AxisRotation();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Destructor
        */
        //////////////////////////////////////////////////////////////////////////
        virtual ~AxisRotation();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the Matrix4xf. That change need the
        *    current time in our application
        *    \return the new state of the matrix4f
        */
        //////////////////////////////////////////////////////////////////////////
        Matrix4f updateState(float time);


    protected:

    private:
        float angularVelocity;
        //vec3f axis;
};

#endif // AXISROTATION_H
