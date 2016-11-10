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

    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
    glBindBuffer(GL_ARRAY_BUFFER,vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vec3f)*vertex.size(),&vertex[0],GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 , 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLushort)*triangles.size(),&triangles[0],GL_STATIC_DRAW);

    glBindVertexArray(0);
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

    glm::mat4 view;
    view = glm::lookAt(glm::vec3(-2.0f, -2.0f, 3.0f),
  		   glm::vec3(0.0f, 0.0f, 0.0f),
  		   glm::vec3(0.0f, 1.0f, 0.0f));
    GLint viewLocation= glGetUniformLocation(shaders.getProgram(),"view");
    glUniformMatrix4fv(viewLocation,1,GL_FALSE,glm::value_ptr(view));
    //glUniformMatrix4fv(viewLocation,1,GL_FALSE,vis.camera.getView());

    glm::mat4 ProjectionMatrix= glm::mat4(1.0f);
    ProjectionMatrix*= glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 200.0f);
    //ProjectionMatrix*= glm::ortho(0.f, 600.f, 800.f, 0.f, -1.f, 200.f);
    GLint projectionLocation= glGetUniformLocation(shaders.getProgram(),"projection");
    glUniformMatrix4fv(projectionLocation,1,GL_FALSE,glm::value_ptr(ProjectionMatrix));
    //glUniformMatrix4fv(projectionLocation,1,GL_FALSE,vis.camera.getProjection());


    //Set value to uniform variable in fragmentshader
    GLint objectColorLoc = glGetUniformLocation(shaders.getProgram(), "objectColor");
    glUniform3f(objectColorLoc, color.x, color.y, color.z);

    //Draw our object
    glBindVertexArray(vertexArrayObject);
    glDrawElements(GL_TRIANGLES,numIndex,GL_UNSIGNED_SHORT,0);
    glBindVertexArray(0);
	glUseProgram(0);
}

//**********************************************************************//

void Mesh::updateState(float time){
}

//**********************************************************************//

void Mesh::clean(){
    glDeleteBuffers(1,&vertexArrayObject);
    glDeleteBuffers(1,&vertexArrayBuffers[POSITION_VB]);
    glDeleteBuffers(1,&vertexArrayBuffers[INDEX_VB]);
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



