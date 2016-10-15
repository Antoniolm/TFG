////////////////////////////////////////
//  Author: Antonio David López Machado
////////////////////////////////////////

#include "mesh.h"

Mesh::Mesh()
{
    //ctor
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
    glGenVertexArrays(1,&VertexArrayID);
    glBindVertexArray(VertexArrayID);

    LoadShader("shaders/vertexshader.vs","shaders/fragmentshader.fs");

    vertex.push_back(*(new vec3f(-1.0,-1.0,0.0)));
    vertex.push_back(*(new vec3f(1.0, -1.0, 0.0)));
    vertex.push_back(*(new vec3f(0.0,  1.0, 0.0)));

    int j=0;
	for(int i=0;i<vertex.size();i++)
    {
        vertexBufferData[j]=vertex[i].x;
        vertexBufferData[j+1]=vertex[i].y;
        vertexBufferData[j+2]=vertex[i].z;
        j+=3;
    }

    glGenBuffers(1,&vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertexBufferData),vertexBufferData,GL_STATIC_DRAW);
}

//**********************************************************************//

void Mesh::visualization(Context & vis){
    //Clear the screen
	glClear( GL_COLOR_BUFFER_BIT );

	//Use our program
	glUseProgram(programID);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

	//Draw the object
	glDrawArrays(GL_TRIANGLES, 0, vertex.size());

	glDisableVertexAttribArray(0);
}

//**********************************************************************//

void Mesh::updateState(float time){}

//**********************************************************************//

void Mesh::clean(){
    glDeleteBuffers(1,&vertexbuffer);
    glDeleteVertexArrays(1,&VertexArrayID);
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
        content="Fail";
    }

    return content;
}

