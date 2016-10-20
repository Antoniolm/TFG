// *********************************************************************
// **
// ** Copyright (C) 2016 Antonio David López Machado
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

#include <glew.h>
#include <math.h>
#include <iostream>

using namespace std;

class Matrix4f
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Matrix4f();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Matrix4f();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will make a translation transform
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void translation(float x,float y,float z);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will make a Scale transform
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void scale(float x,float y,float z);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will make a rotation transform
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void rotation(float grade,const float x,const float y,const float z);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will make the identity matrix
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void identity();


        void product(const GLfloat * aMatrix);
        //////////////////////////////////////////////////////////////////////////
        /**
        *    \return Return our current matrix4f
        */
        //////////////////////////////////////////////////////////////////////////
        GLfloat * getMatrix();


    protected:

    private:
        GLfloat * matrix;
};

#endif // MATRIX4F_H
