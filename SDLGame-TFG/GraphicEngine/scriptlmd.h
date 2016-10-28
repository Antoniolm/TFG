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

#ifndef SCRIPTLMD_H
#define SCRIPTLMD_H

#include "scriptanimation.h"
#include "matrix4fdinamic.h"
#include <vector>

using namespace std;

class ScriptLMD : public ScriptAnimation
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        ScriptLMD();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~ScriptLMD();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will add a new element in our script
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void add(const Matrix4fDinamic & aMatrix);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of all our Matrix4xfDinamic. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void updateState(float time);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will return one of our Matrix4fDinamic.
        *    \param index -> The position in the vector of our return Matrix
        *    \return Matrix4f
        */
        //////////////////////////////////////////////////////////////////////////
        virtual Matrix4f readMatrix(int index);
    protected:

    private:
        vector<Matrix4fDinamic> script;
        float currentTime;

};

#endif // SCRIPTLMD_H
