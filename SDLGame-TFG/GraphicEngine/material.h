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

#ifndef MATERIAL_H
#define MATERIAL_H

#include "structdata.h"
#include <string>
#include "texture.h"

using namespace std;

class Material
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Material();

        //////////////////////////////////////////////////////////////////////////
        /** Copy constructor */
        //////////////////////////////////////////////////////////////////////////
        Material(const Material & aMaterial);

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters*/
        //////////////////////////////////////////////////////////////////////////
        Material(const vec3f & anAmbient,const vec3f & aDiffuse,const vec3f &aSpecular,float aShini,const string & aFileTextur);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Material();

        void setAmbient(const vec3f & anAmbient);
        void setDiffuse(const vec3f & aDiffuse);
        void setSpecular(const vec3f &aSpecular);
        void setShininess(float aShini);
        void setTexture(const string & aFileTextur);
        void setTexture(const Texture & aTexture);


        vec3f getAmbient();
        vec3f getDiffuse();
        vec3f getSpecular();
        float getShininess();

        Texture & getTexture();

    protected:

    private:
        vec3f ambient;
        vec3f diffuse;
        vec3f specular;
        float shininess;
        Texture texture;
};

#endif // MATERIAL_H
