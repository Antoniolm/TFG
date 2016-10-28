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

#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H

#include "matrix4f.h"
#include <vector>

class MatrixStack
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        MatrixStack();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~MatrixStack();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will push a new Matrix in the stack
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void push();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will pop the matrix in the top of stack
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void pop(int cont);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will asign the identity matrix to the currentMatrix
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void asignIdentity();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will make the product between the currentMatrix and the matrix parameter
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void cMatrix(const Matrix4f & mat ) ;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will make the product between the currentMatrix and a translation matrix
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void cTraslation( const float dx, const float dy, const float dz ) ;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will make the product between the currentMatrix and a scale matrix
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void cScale ( const float sx, const float sy, const float sz ) ;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will make the product between the currentMatrix and a rotation matrix
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void cRotation ( const float ang_gra,const float ex, const float ey, const float ez ) ;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the currentMatrix
        *    \return GLfloat -> the matrix
        */
        //////////////////////////////////////////////////////////////////////////
        Matrix4f & getMatrix();

        void clean();

    protected:

    private:
        Matrix4f currentMatrix;
        std::vector<Matrix4f> mainStack;
};

#endif // MATRIXSTACK_H
