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

#include "material.h"

Material::Material()
{
    //ctor
}

//**********************************************************************//

Material::Material(const Material & aMaterial){
    ambient=aMaterial.ambient;
    diffuse=aMaterial.diffuse;
    specular=aMaterial.specular;
    shininess=aMaterial.shininess;
    texture=aMaterial.texture;
}

//**********************************************************************//

Material::Material(const vec3f & anAmbient,const vec3f & aDiffuse,const vec3f &aSpecular,float aShini,const string & aFileTextur){
    ambient=anAmbient;
    diffuse=aDiffuse;
    specular=aSpecular;
    shininess=aShini;
    texture=new Texture(aFileTextur);
}

//**********************************************************************//

Material::~Material()
{
}

//**********************************************************************//

void Material::activate(Shader * aShader){

    shaders=aShader;

    //Set value to uniform about material
    GLint matAmbientLoc  = glGetUniformLocation(shaders->getProgram(), "material.ambient");
    GLint matDiffuseLoc  = glGetUniformLocation(shaders->getProgram(), "material.diffuse");
    GLint matSpecularLoc = glGetUniformLocation(shaders->getProgram(), "material.specular");
    GLint matShineLoc    = glGetUniformLocation(shaders->getProgram(), "material.shininess");

    //Bind the texture
    texture->bindTexture();

    glUniform3f(matAmbientLoc,  ambient.x,  ambient.y, ambient.z);
    glUniform3f(matDiffuseLoc,  diffuse.x,  diffuse.y, diffuse.z);
    glUniform3f(matSpecularLoc, specular.x,  specular.y, specular.z);
    glUniform1f(matShineLoc,    shininess);
}

//**********************************************************************//

void Material::setAmbient(const vec3f & anAmbient){
    ambient=anAmbient;
}

//**********************************************************************//

void Material::setDiffuse(const vec3f & aDiffuse){
    diffuse=aDiffuse;
}

//**********************************************************************//

void Material::setSpecular(const vec3f &aSpecular){
    specular=aSpecular;
}

//**********************************************************************//

void Material::setShininess(float aShini){
    shininess=aShini;
}

//**********************************************************************//

void Material::setTexture(const string & aFileTextur){
    texture=new Texture(aFileTextur);
}

//**********************************************************************//

void Material::setTexture(Texture * aTexture){
    texture=aTexture;
}

//**********************************************************************//

vec3f Material::getAmbient(){
    return ambient;
}

//**********************************************************************//

vec3f Material::getDiffuse(){
    return diffuse;
}

//**********************************************************************//

vec3f Material::getSpecular(){
    return specular;
}

//**********************************************************************//

float Material::getShininess(){
    return shininess;
}

//**********************************************************************//

Texture * Material::getTexture(){
    return texture;
}
