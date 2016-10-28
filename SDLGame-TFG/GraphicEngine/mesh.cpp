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
}

//**********************************************************************//
Mesh::Mesh(const string & aFile){
    std::vector<float> vertex_ply ; // vertex
    std::vector<int>   faces_ply ;    // face

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

    if(!vis.visualization_static){
        //cout<<"False false"<< endl;
        transformation = vis.matrixStack.getMatrix();
    }

	//Set value to uniform variable
	glUseProgram(shaders.getProgram());
    GLint transformaLocation= glGetUniformLocation(shaders.getProgram(),"transform");
    glUniformMatrix4fv(transformaLocation,1,GL_FALSE,transformation.getMatrix());

    GLint viewLocation= glGetUniformLocation(shaders.getProgram(),"view");
    glUniformMatrix4fv(viewLocation,1,GL_FALSE,vis.camera.getView());

    GLint projectionLocation= glGetUniformLocation(shaders.getProgram(),"projection");
    glUniformMatrix4fv(projectionLocation,1,GL_FALSE,vis.camera.getProjection());

    position=transformation.product(position);
    vis.posObject.push_back(this);
    //cout<< "Position --> x:"<< position.x << " y : "<< position.y<< " z: "<< position.z<< endl;
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

void Mesh::updateState(float time){}

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



