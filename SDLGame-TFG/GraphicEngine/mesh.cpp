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
    //ctor
}

//**********************************************************************//

Mesh::Mesh(const string & aFile){
    objFile=aFile;
    numIndex=0;
}

//**********************************************************************//

Mesh::~Mesh()
{
    glDeleteBuffers(1,&vertexArrayObject);
    glDeleteBuffers(1,&vertexArrayBuffers[POSITION_VB]);
    glDeleteBuffers(1,&vertexArrayBuffers[NORMAL_VB]);
    glDeleteBuffers(1,&vertexArrayBuffers[TEXCOORD_VB]);
    glDeleteBuffers(1,&vertexArrayBuffers[INDEX_VB]);
}

//**********************************************************************//

void Mesh::init(){
    vector<GLushort> triangles;
    vector<vec3f> vertex;
    vector<vec3f> normals;
    vector<vec2f> textureCord;

    obj::readEverything(objFile.c_str(),vertex,triangles,normals,textureCord,true,true);

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

}

//**********************************************************************//

void Mesh::visualization(Context & vis){
    //Draw our object
    glBindVertexArray(vertexArrayObject);
    glDrawElements(GL_TRIANGLES,numIndex,GL_UNSIGNED_SHORT,0);
    glBindVertexArray(0);
}

//**********************************************************************//

void Mesh::updateState(float time){
}

//**********************************************************************//

BoundingBox Mesh::getBoundingBox(){
    return boundingBox;
}

