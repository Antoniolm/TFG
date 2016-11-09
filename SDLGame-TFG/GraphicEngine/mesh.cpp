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

#include "mesh.h"

Mesh::Mesh()
{
}

//**********************************************************************//

Mesh::Mesh(const Mesh & aMesh){
    vertexbuffer=aMesh.vertexbuffer;
    trianglebuffer=aMesh.trianglebuffer;
    shaders=aMesh.shaders;
}

//**********************************************************************//

Mesh::Mesh(const string & aTextur,unsigned char aType){
    color=vec3f(1.0,0.5,0.5);
    //

}

//**********************************************************************//
Mesh::Mesh(const string & aFile,vec3f aColor){
    color=aColor;
    file=aFile;
}

//**********************************************************************//

Mesh::~Mesh()
{
    //dtor
}

//**********************************************************************//

void Mesh::init(){
    vector<GLushort> triangles;
    vector<vec3f> vertex;

    obj::readMesh(file.c_str(),vertex,triangles);

    numIndex=triangles.size();

    //glGenVertexArrays(1, &vertexArrayObject);
	//glBindVertexArray(vertexArrayObject);

    glGenBuffers(1,&vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vec3f)*vertex.size(),&vertex[0],GL_STATIC_DRAW);

    glGenBuffers(1,&trianglebuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,trianglebuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLushort)*triangles.size(),&triangles[0],GL_STATIC_DRAW);

    //glBindVertexArray(0);
}

//**********************************************************************//

void Mesh::visualization(Context & vis){
    position=(*new vec4f());

    Matrix4f * transformation = &(vis.matrixStack.getMatrix());
    position=transformation->product(position);

	//Set value to uniform variable in vertexshader
	glUseProgram(shaders.getProgram());
    GLint transformaLocation= glGetUniformLocation(shaders.getProgram(),"transform");
    glUniformMatrix4fv(transformaLocation,1,GL_FALSE,transformation->getMatrix());

    GLint viewLocation= glGetUniformLocation(shaders.getProgram(),"view");
    glUniformMatrix4fv(viewLocation,1,GL_FALSE,vis.camera.getView());

    //glm::mat4 ProjectionMatrix= glm::mat4(1.0f);
    //ProjectionMatrix*= glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 200.0f);
    GLint projectionLocation= glGetUniformLocation(shaders.getProgram(),"projection");
    glUniformMatrix4fv(projectionLocation,1,GL_FALSE,vis.camera.getProjection());

    //Set value to uniform variable in fragmentshader
    GLint objectColorLoc = glGetUniformLocation(shaders.getProgram(), "objectColor");
    GLint lightColorLoc = glGetUniformLocation(shaders.getProgram(), "lightColor");
    glUniform3f(objectColorLoc, color.x, color.y, color.z);
    glUniform3f(lightColorLoc, 0.5f, 0.5f, 0.5f); //

    //Set value to uniform about material
    GLint matAmbientLoc  = glGetUniformLocation(shaders.getProgram(), "material.ambient");
    GLint matDiffuseLoc  = glGetUniformLocation(shaders.getProgram(), "material.diffuse");
    GLint matSpecularLoc = glGetUniformLocation(shaders.getProgram(), "material.specular");
    GLint matShineLoc    = glGetUniformLocation(shaders.getProgram(), "material.shininess");
    glUniform3f(matAmbientLoc,  1.0f, 0.5f, 0.31f);
    glUniform3f(matDiffuseLoc,  1.0f, 0.5f, 0.31f);
    glUniform3f(matSpecularLoc, 0.5f, 0.5f, 0.5f);
    glUniform1f(matShineLoc,    90.0f);

    //Set value to uniform about light
    GLint lightPosLoc      = glGetUniformLocation(shaders.getProgram(), "light.position");
    GLint lightAmbientLoc  = glGetUniformLocation(shaders.getProgram(), "light.ambient");
    GLint lightDiffuseLoc  = glGetUniformLocation(shaders.getProgram(), "light.diffuse");
    GLint lightSpecularLoc = glGetUniformLocation(shaders.getProgram(), "light.specular");
    GLint viewPosLoc = glGetUniformLocation(shaders.getProgram(), "viewPos");

    glUniform3f(lightPosLoc,  1.2f, 1.0f, 2.0f);
    glUniform3f(lightAmbientLoc,  0.2f, 0.2f, 0.2f);
    glUniform3f(lightDiffuseLoc,  0.5f, 0.5f, 0.5f);
    glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
    vec3f camPos=vis.camera.getPosition();
    glUniform3f(viewPosLoc, camPos.x, camPos.y, camPos.z);

    //Bind our buffer
    glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,trianglebuffer);

    //Draw our object
    glDrawElements(GL_TRIANGLES,numIndex,GL_UNSIGNED_SHORT,0);
	glUseProgram(0);
}

//**********************************************************************//

void Mesh::updateState(float time){
}

//**********************************************************************//

void Mesh::clean(){
    glDeleteBuffers(1,&vertexbuffer);
    glDeleteBuffers(1,&trianglebuffer);
}

//**********************************************************************//

vec4f Mesh::getPosition(){
    return position;
}

//**********************************************************************//

bool Mesh::LoadShader(const string & vertexShaderFile,const string & fragmentShaderFile){
    shaders.setFiles(vertexShaderFile,fragmentShaderFile);
    bool result=shaders.createProgram();
    return result;
}



