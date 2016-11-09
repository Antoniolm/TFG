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

#include "meshmaterial.h"

MeshMaterial::MeshMaterial()
{
    //ctor
}

//**********************************************************************//

MeshMaterial::MeshMaterial(const string & aFile){
    objFile=aFile;
    numIndex=0;
}

//**********************************************************************//

MeshMaterial::~MeshMaterial()
{
    glDeleteBuffers(1,&vertexArrayObject);
    glDeleteBuffers(1,&vertexArrayBuffers[POSITION_VB]);
    glDeleteBuffers(1,&vertexArrayBuffers[NORMAL_VB]);
    glDeleteBuffers(1,&vertexArrayBuffers[TEXCOORD_VB]);
    glDeleteBuffers(1,&vertexArrayBuffers[INDEX_VB]);
}

//**********************************************************************//

void MeshMaterial::init(){
    vector<GLushort> triangles;
    vector<vec3f> vertex;
    vector<vec3f> normals;
    vector<vec2f> textureCord;

    obj::readEverything(objFile.c_str(),vertex,triangles,normals,textureCord);
    numIndex=triangles.size();

    glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	//Vertex buffer
    glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
    glBindBuffer(GL_ARRAY_BUFFER,vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vec3f)*vertex.size(),&vertex[0],GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 , 0);

    //Normal buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3f)* normals.size(), &normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Texture Coord buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2f) * textureCord.size(), &textureCord[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

    //Triangles buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLushort)*triangles.size(),&triangles[0],GL_STATIC_DRAW);

    glBindVertexArray(0);

    Texture texture("./textures/wood2.jpg");
    texture.Bind();
}

//**********************************************************************//

void MeshMaterial::visualization(Context & vis){
    position=vec4f();

    Matrix4f * transformation = &(vis.matrixStack.getMatrix());
    position=transformation->product(position);

	//Set value to uniform variable in vertexshader
	glUseProgram(shaders.getProgram());
    GLint transformaLocation= glGetUniformLocation(shaders.getProgram(),"transform");
    glUniformMatrix4fv(transformaLocation,1,GL_FALSE,transformation->getMatrix());

    GLint viewLocation= glGetUniformLocation(shaders.getProgram(),"view");
    glUniformMatrix4fv(viewLocation,1,GL_FALSE,vis.camera.getView());

    GLint projectionLocation= glGetUniformLocation(shaders.getProgram(),"projection");
    glUniformMatrix4fv(projectionLocation,1,GL_FALSE,vis.camera.getProjection());

    //Set value to uniform variable in fragmentshader
    GLint lightColorLoc = glGetUniformLocation(shaders.getProgram(), "lightColor");
    glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

    //Set value to uniform about material
    GLint matAmbientLoc  = glGetUniformLocation(shaders.getProgram(), "material.ambient");
    GLint matDiffuseLoc  = glGetUniformLocation(shaders.getProgram(), "material.diffuse");
    GLint matSpecularLoc = glGetUniformLocation(shaders.getProgram(), "material.specular");
    GLint matShineLoc    = glGetUniformLocation(shaders.getProgram(), "material.shininess");

    Material material(vec3f(1.0f, 0.5f, 0.5f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f);
    vec3f ambient=material.getAmbient();
    vec3f diffuse=material.getDiffuse();
    vec3f specular=material.getAmbient();
    float shini=material.getShininess();

    glUniform3f(matAmbientLoc,  ambient.x,  ambient.y, ambient.z);
    glUniform3f(matDiffuseLoc,  diffuse.x,  diffuse.y, diffuse.z);
    glUniform3f(matSpecularLoc, specular.x,  specular.y, specular.z);
    glUniform1f(matShineLoc,    shini);

    //Set value to uniform about light
    GLint lightPosLoc      = glGetUniformLocation(shaders.getProgram(), "light.position");
    GLint lightAmbientLoc  = glGetUniformLocation(shaders.getProgram(), "light.ambient");
    GLint lightDiffuseLoc  = glGetUniformLocation(shaders.getProgram(), "light.diffuse");
    GLint lightSpecularLoc = glGetUniformLocation(shaders.getProgram(), "light.specular");
    GLint viewPosLoc = glGetUniformLocation(shaders.getProgram(), "viewPos");

    glUniform3f(lightPosLoc,  1.0f, 2.0f, 2.0f);
    glUniform3f(lightAmbientLoc,  0.2f, 0.2f, 0.2f);
    glUniform3f(lightDiffuseLoc,  0.5f, 0.5f, 0.5f);
    glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
    vec3f camPos=vis.camera.getPosition();
    glUniform3f(viewPosLoc, camPos.x, camPos.y, camPos.z);

    //Draw our object
    glBindVertexArray(vertexArrayObject);
    glDrawElements(GL_TRIANGLES,numIndex,GL_UNSIGNED_SHORT,0);
    glBindVertexArray(0);

	glUseProgram(0);
}

//**********************************************************************//

void MeshMaterial::updateState(float time){
}

//**********************************************************************//

bool MeshMaterial::LoadShader(const string & vertexShaderFile,const string & fragmentShaderFile){
    shaders.setFiles(vertexShaderFile,fragmentShaderFile);
    bool result=shaders.createProgram();
    return result;
}
