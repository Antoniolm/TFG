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
    triangles=aMesh.triangles;
    vertex=aMesh.vertex;
    transformation=aMesh.transformation;
    vertexbuffer=aMesh.vertexbuffer;
    trianglebuffer=aMesh.trianglebuffer;
    shaders=aMesh.shaders;
}

//**********************************************************************//

Mesh::Mesh(const string & aTextur,unsigned char aType){
    texture=aTextur;
    type=aType;
    std::vector<float> vertex_obj; // vertex
    std::vector<float> normal_obj; // vertex
    std::vector<float> normalf_obj; // vertex
    std::vector<float> textureCoord_obj; // vertex
    std::vector<int>   faces_obj ;    // face
    std::vector<int>   texturef_obj ;    // face
    cout<< "Mission complete"<< endl;
    obj::readMesh("geometries/foot.obj",vertex_obj,faces_obj);//,normal_obj,normalf_obj,textureCoord_obj,texturef_obj);
    for(int i=0;i<vertex_obj.size();i=i+3){
        vertex.push_back(*(new vec3f(vertex_obj[i],vertex_obj[i+1],vertex_obj[i+2])));
    }
    for(int i=0;i<faces_obj.size();i=i+3){
        triangles.push_back(*(new vec3i(faces_obj[i],faces_obj[i+1],faces_obj[i+2])));
	}
}

//**********************************************************************//
Mesh::Mesh(const string & aFile,vec3f aColor){
    std::vector<float> vertex_ply ; // vertex
    std::vector<int>   faces_ply ;    // face

    color=aColor;

    ply::read( aFile.c_str(), vertex_ply,faces_ply);
    for(int i=0;i<vertex_ply.size();i=i+3){
        vertex.push_back(*(new vec3f(vertex_ply[i],vertex_ply[i+1],vertex_ply[i+2])));
    }
    for(int i=0;i<faces_ply.size();i=i+3){
        triangles.push_back(*(new vec3i(faces_ply[i],faces_ply[i+1],faces_ply[i+2])));
	}
}

//**********************************************************************//

Mesh::~Mesh()
{
    //dtor
}

//**********************************************************************//

void Mesh::init(){
    int j=0;
    GLfloat verts[vertex.size()*3];
    for(int i=0;i<vertex.size();i++){
        verts[j]=vertex[i].x;
        verts[j+1]=vertex[i].y;
        verts[j+2]=vertex[i].z;
        j+=3;
    }

    glGenBuffers(1,&vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(verts),verts,GL_STATIC_DRAW);

    j=0;
    GLushort index[triangles.size()*3];
    for(int i=0;i<triangles.size();i++){
        index[j]=triangles[i].x;
        index[j+1]=triangles[i].y;
        index[j+2]=triangles[i].z;
        j+=3;
    }

    glGenBuffers(1,&trianglebuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,trianglebuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(index),index,GL_STATIC_DRAW);

}

//**********************************************************************//

void Mesh::visualization(Context & vis){
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
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,trianglebuffer);

    //Draw our object
    glDrawElements(GL_TRIANGLES,triangles.size()*3,GL_UNSIGNED_SHORT,0);
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



