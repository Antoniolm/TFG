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


#ifndef LINEARMOVEMENT_H
#define LINEARMOVEMENT_H

#include "matrix4fdinamic.h"
#include "structdata.h"

class LinearMovement : public Matrix4fDinamic {

    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor*/
        //////////////////////////////////////////////////////////////////////////
        LinearMovement();
        LinearMovement(float x,float y,float z);
        LinearMovement(vec3f aVelocity);
        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~LinearMovement();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the Matrix4xf. That change need the
        *    current time in our application
        *    \return the new state of the matrix4f
        */
        //////////////////////////////////////////////////////////////////////////
        virtual Matrix4f & updateState(float time);
    protected:

    private:
        vec3f velocity;
};

#endif // LINEARMOVEMENT_H
