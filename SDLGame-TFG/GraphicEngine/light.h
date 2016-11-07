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

#ifndef LIGHT_H
#define LIGHT_H

#include "structdata.h"

class Light
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Light();

        //////////////////////////////////////////////////////////////////////////
        /** Copy constructor */
        //////////////////////////////////////////////////////////////////////////
        Light(const Light & aLight);

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters*/
        //////////////////////////////////////////////////////////////////////////
        Light(const vec3f & aPos,const vec3f & anAmbient,const vec3f & aDiffuse,const vec3f &aSpecular);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Light();


        void setPosition(const vec3f & aPos);
        void setAmbient(const vec3f & anAmbient);
        void setDiffuse(const vec3f & aDiffuse);
        void setSpecular(const vec3f &aSpecular);


        vec3f getPosition();
        vec3f getAmbient();
        vec3f getDiffuse();
        vec3f getSpecular();

    protected:

    private:
        vec3f position;
        vec3f ambient;
        vec3f diffuse;
        vec3f specular;
};

#endif // LIGHT_H
