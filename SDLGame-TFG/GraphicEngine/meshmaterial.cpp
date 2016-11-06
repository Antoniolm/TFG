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

MeshMaterial::MeshMaterial(const string & aFile,vec3f aColor){
    color=aColor;
    std::vector<int> normalf_obj; // vertex
    std::vector<float> textureCoord_obj; // vertex
    std::vector<int>   texturef_obj ;    // face
    cout<< "Mission complete"<< endl;
    obj::readEverything("geometries/untitled3.obj",vertex,triangles,normals,normalf_obj,textureCoord_obj,texturef_obj);
    for(int i=0;i<vertex.size();i=i+3){
        vec3f vert=vec3f(vertex[i],vertex[i+1],vertex[i+2]);
        vec3f norm=vec3f(normals[i],normals[i+1],normals[i+2]);
        Vertex aux(vert,norm);
        vertexAndNormal.push_back(aux);
    }
}

//**********************************************************************//

void MeshMaterial::init(){

    glGenBuffers(1,&vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*vertexAndNormal.size()*6,&vertexAndNormal[0],GL_STATIC_DRAW);

    glGenBuffers(1,&trianglebuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,trianglebuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLushort)*triangles.size(),&triangles[0],GL_STATIC_DRAW);
}


//**********************************************************************//

MeshMaterial::~MeshMaterial()
{
    //dtor
}

//**********************************************************************//

void MeshMaterial::visualization(Context & vis){
    position=(*new vec4f());

    transformation = &(vis.matrixStack.getMatrix());
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
    GLint objectColorLoc = glGetUniformLocation(shaders.getProgram(), "objectColor");
    GLint lightColorLoc = glGetUniformLocation(shaders.getProgram(), "lightColor");
    glUniform3f(objectColorLoc, color.x, color.y, color.z);
    glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f); // Also set light’s color (

    //Bind our buffer
    glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float), (GLvoid*)0);

    // Vertex Normals
    glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3,(GLvoid*)sizeof(normals.size()));
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3,&normals[0]);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,trianglebuffer);

    //Draw our object
    glDrawElements(GL_TRIANGLES,triangles.size(),GL_UNSIGNED_SHORT,0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
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
