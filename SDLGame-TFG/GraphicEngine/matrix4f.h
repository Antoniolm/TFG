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

#ifndef MATRIX4F_H
#define MATRIX4F_H

#include <SDL_opengl.h>
#include <math.h>

class Matrix4f
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Constructor
        */
        //////////////////////////////////////////////////////////////////////////
        Matrix4f();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Destructor
        */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Matrix4f();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will make a translation transform
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void translation(double x,double y,double z);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will make a Scale transform
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void scale(double x,double y,double z);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will make a rotation transform
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void rotation(float grade,const float x,const float y,const float z);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    \return Return our current matrix4f
        */
        //////////////////////////////////////////////////////////////////////////
        GLdouble * getMatrix();

    protected:

    private:
        GLdouble * matrix;
};

#endif // MATRIX4F_H
