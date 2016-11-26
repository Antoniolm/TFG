// *********************************************************************
// **
// ** Copyright (C) 2016-2017 Antonio David L�pez Machado
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

    type=directional;
}

//**********************************************************************//

Light::Light(const vec3f & aPos,const vec3f & anAmbient,const vec3f & aDiffuse,const vec3f &aSpecular,float aConstant,float aLinear,float aQuadratic){
    position=aPos;
    ambient=anAmbient;
    diffuse=aDiffuse;
    specular=aSpecular;

    constant=aConstant;
    linear=aLinear;
    quadratic=aQuadratic;

    type=point;
}

//**********************************************************************//

Light::~Light()
{
    //dtor
}

//**********************************************************************//

void Light::activate(Shader * shader,string nLight){

    GLuint program=shader->getProgram();

    //Set value to uniform about light
    switch(type){
        case directional:
            glUniform3f(glGetUniformLocation(program, "dirLight.direction"),  position.x,  position.y, position.z);
            glUniform3f(glGetUniformLocation(program, "dirLight.ambient"),  ambient.x,  ambient.y, ambient.z);
            glUniform3f(glGetUniformLocation(program, "dirLight.diffuse"),  diffuse.x,  diffuse.y, diffuse.z);
            glUniform3f(glGetUniformLocation(program, "dirLight.specular"), specular.x,  specular.y, specular.z);
        break;

        case point:
            glUniform3f(glGetUniformLocation(program,("pointLights[" + nLight + "].position").c_str()),  position.x,  position.y, position.z);
            glUniform3f(glGetUniformLocation(program,("pointLights[" + nLight + "].ambient").c_str()),  ambient.x,  ambient.y, ambient.z);
            glUniform3f(glGetUniformLocation(program,("pointLights[" + nLight + "].diffuse").c_str()),  diffuse.x,  diffuse.y, diffuse.z);
            glUniform3f(glGetUniformLocation(program,("pointLights[" + nLight + "].specular").c_str()), specular.x,  specular.y, specular.z);
            glUniform1f(glGetUniformLocation(program,("pointLights[" + nLight + "].constant").c_str()), constant);
            glUniform1f(glGetUniformLocation(program,("pointLights[" + nLight + "].linear").c_str()), linear);
            glUniform1f(glGetUniformLocation(program,("pointLights[" + nLight + "].quadratic").c_str()), quadratic);
        break;
    }


}

//**********************************************************************//

void Light::setPosition(const vec3f & aPos){
    position=aPos;
}

//**********************************************************************//

void Light::setDirectionalLight(const vec3f & aDir,const vec3f & anAmbient,const vec3f & aDiffuse,const vec3f &aSpecular){
    position=aDir;
    ambient=anAmbient;
    diffuse=aDiffuse;
    specular=aSpecular;

    type=directional;
}

//**********************************************************************//

void Light::setPointLight(const vec3f & aPos,const vec3f & anAmbient,const vec3f & aDiffuse,const vec3f &aSpecular,float aConstant,float aLinear,float aQuadratic){
    position=aPos;
    ambient=anAmbient;
    diffuse=aDiffuse;
    specular=aSpecular;

    constant=aConstant;
    linear=aLinear;
    quadratic=aQuadratic;

    type=point;
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
