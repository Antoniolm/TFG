// *********************************************************************
// **
// ** Copyright (C) 2016 Antonio David López Machado
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
    vertex.push_back(*(new vec3f(-0.5f,0.5f,0.0f)));
    vertex.push_back(*(new vec3f(-0.5f,-0.5f,0.0f)));
    vertex.push_back(*(new vec3f(0.5f,-0.5f,0.0f)));
    vertex.push_back(*(new vec3f(0.5f,0.5f,0.0f)));

    triangles.push_back(*(new vec3i(0,1,2)));
    triangles.push_back(*(new vec3i(0,2,3)));

    //matrix=new Matrix4f();
    //matrix->translation(0.0f,0.5f,0.0f);
}

//**********************************************************************//

Mesh::Mesh(string & aTextur,float aHeight,float aWidth,unsigned char aType){
    texture=aTextur;
    height=aHeight;
    width=aWidth;
    type=aType;
}

//**********************************************************************//
Mesh::Mesh(string & aFile){

}

//**********************************************************************//

Mesh::~Mesh()
{
    //dtor
}

//**********************************************************************//

void Mesh::init(){
    LoadShader("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    glEnableVertexAttribArray(0);

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
    //Clear the screen
	glClear( GL_COLOR_BUFFER_BIT );

	//Set value to uniform variable
	glUseProgram(programID);
    GLint transformaLocation= glGetUniformLocation(programID,"transform");
    glUniformMatrix4fv(transformaLocation,1,GL_FALSE,vis.matrixStack.getMatrix());

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

bool Mesh::LoadShader(string vertexShaderFile,string fragmentShaderFile){

    bool result=true;
    GLint isShaderCompiled;
    GLint isProgramRight;
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    string vShaderCode;
    string fShaderCode;

    //Obtaining the code of our shaders
    vShaderCode = LoadFileTxt(vertexShaderFile);
    fShaderCode = LoadFileTxt(fragmentShaderFile);

    //Compiling our vertexShader
    const char *VertexSourcePointer = vShaderCode.c_str();
    glShaderSource(VertexShaderID,1,&VertexSourcePointer,NULL);
    glCompileShader(VertexShaderID);

    //Check Vertex Shader
    glGetShaderiv( VertexShaderID, GL_COMPILE_STATUS, &isShaderCompiled );
    if(!isShaderCompiled)
    {
        cout<< "Unable to compile vertex shader"<< vertexShaderFile<<endl;
        result = false;
    }

	//Compiling our FragmentShader
    char const * FragmentSourcePointer = fShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	//Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &isShaderCompiled);
    if(!isShaderCompiled)
    {
        cout<< "Unable to compile Fragment shader"<< fragmentShaderFile<<endl;
        result = false;
    }

	//Creating our program and linking the shaders
    programID = glCreateProgram();
    glAttachShader(programID, VertexShaderID);
    glAttachShader(programID, FragmentShaderID);
    glLinkProgram(programID);

    //Check the program
	glGetProgramiv(programID, GL_LINK_STATUS, &isProgramRight);
	if (!isProgramRight){
        cout<< "Unable to link the program"<<endl;
        result = false;
	}

	//Delete compiled shaderss
	glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return result;

}

//**********************************************************************//
//* Private Methods

string Mesh::LoadFileTxt(string file){

    string content;
    ifstream sourceFile;
    sourceFile.open(file.c_str(),ifstream::in);

    if( sourceFile.is_open() )
	{
        content.assign( ( istreambuf_iterator< char >( sourceFile ) ), istreambuf_iterator< char >() );
        sourceFile.close();
	}
    else{
        content="Unable to access the file"+ file;
    }

    return content;
}

