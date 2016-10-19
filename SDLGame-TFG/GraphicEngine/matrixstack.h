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

#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H

#include "matrix4f.h"
#include <vector>

class MatrixStack
{
    public:
        /** Default constructor */
        MatrixStack();
        /** Default destructor */
        virtual ~MatrixStack();
        void push();
        void pop();
        void asignIdentity();
        void cMatrix( const Matrix4f & mat ) ;
        void cTraslation( const float dx, const float dy, const float dz ) ;
        void cScale ( const float sx, const float sy, const float sz ) ;
        void cRotation ( const float ang_gra,const float ex, const float ey, const float ez ) ;

    protected:

    private:
        Matrix4f * currentMatrix;
        std::vector<Matrix4f> mainStack;
};

#endif // MATRIXSTACK_H
