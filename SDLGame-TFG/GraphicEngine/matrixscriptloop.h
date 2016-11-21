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

#ifndef MATRIXSCRIPTLOOP_H
#define MATRIXSCRIPTLOOP_H

#include <vector>
#include "matrix4fdynamic.h"

class MatrixScriptLoop : public Matrix4fDynamic
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        MatrixScriptLoop();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~MatrixScriptLoop();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will add a new element to our script
        *    \param loop -> Loop of our new element
        *    \param matrix -> matrix of this new element
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void add(int loop, Matrix4fDynamic * matrix);

        int getNumElement();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the Matrix4xf. That change need the
        *    current time in our application
        *    \return the new state of the matrix4f
        */
        //////////////////////////////////////////////////////////////////////////
        virtual Matrix4f & updateState(float time);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will reset to the initial state
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void resetState();

        Matrix4f & getMatrix();

    protected:

    private:
        int currentLoop;
        int currentMove;
        vector<pair<int,Matrix4fDynamic *> > script;
};

#endif // MATRIXSCRIPTLOOP_H
