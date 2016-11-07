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

#include "light.h"

Light::Light()
{
    //ctor
}

//**********************************************************************//

Light::Light(const Light & aLight){
    position=aLight.position;
    ambient=aLight.ambient;
    diffuse=aLight.diffuse;
    specular=aLight.specular;
}

//**********************************************************************//

Light::Light(const vec3f & aPos,const vec3f & anAmbient,const vec3f & aDiffuse,const vec3f &aSpecular){
    position=aPos;
    ambient=anAmbient;
    diffuse=aDiffuse;
    specular=aSpecular;
}

//**********************************************************************//

Light::~Light()
{
    //dtor
}

//**********************************************************************//

void Light::setPosition(const vec3f & aPos){
    position=aPos;
}

//**********************************************************************//

void Light::setAmbient(const vec3f & anAmbient){
    ambient=anAmbient;
}

//**********************************************************************//

void Light::setDiffuse(const vec3f & aDiffuse){
    diffuse=aDiffuse;
}

//**********************************************************************//

void Light::setSpecular(const vec3f &aSpecular){
    specular=aSpecular;
}

//**********************************************************************//

vec3f Light::getPosition(){
    return position;
}

//**********************************************************************//

vec3f Light::getAmbient(){
    return ambient;
}

//**********************************************************************//

vec3f Light::getDiffuse(){
    return diffuse;
}

//**********************************************************************//

vec3f Light::getSpecular(){
    return specular;
}
