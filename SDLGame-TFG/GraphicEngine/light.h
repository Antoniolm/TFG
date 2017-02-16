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
#include "shader.h"
#include <string>
#include <cstdlib>
#include "../lib/rapidjson/document.h"

enum typeLight{
    directional,
    point

};

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
        /** Constructor with parameters */
        //////////////////////////////////////////////////////////////////////////
        Light(const vec3f & aPos,const vec3f & anAmbient,const vec3f & aDiffuse,const vec3f &aSpecular,string nlight="0");

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters */
        //////////////////////////////////////////////////////////////////////////
        Light(const vec3f & aPos,const vec3f & anAmbient,const vec3f & aDiffuse,const vec3f &aSpecular,float aConstant,float aLinear,float aQuadratic,string nlight="0");

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with json */
        //////////////////////////////////////////////////////////////////////////
        Light(const rapidjson::Value & lightFeature);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Light();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will activate our light in the currentShader
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activate(GLuint shaderID);


        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will set the position in our light
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setPosition(const vec3f & aPos);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will set a directional light
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setDirectionalLight(const vec3f & aDir,const vec3f & anAmbient,const vec3f & aDiffuse,const vec3f &aSpecular);


        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will set a point light
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setPointLight(const vec3f & aPos,const vec3f & anAmbient,const vec3f & aDiffuse,const vec3f &aSpecular,float aConstant,float aLinear,float aQuadratic);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will get the position in our light
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getPosition();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will get the ambient in our light
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getAmbient();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will get the diffuse in our light
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getDiffuse();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will get the specular in our light
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getSpecular();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will get the shininess in our light
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        float getShininess();

    protected:

    private:
        typeLight type;
        vec3f position;
        vec3f ambient;
        vec3f diffuse;
        vec3f specular;

        float constant;
        float linear;
        float quadratic;
        string nLight;
};

#endif // LIGHT_H
