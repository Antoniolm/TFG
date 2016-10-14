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
Mesh::~Mesh()
{
    //dtor
}
//**********************************************************************//
void Mesh::visualization( Context & vis){}
//**********************************************************************//
void Mesh::updateState(float time){}
//**********************************************************************//
void Mesh::clean(){}
//**********************************************************************//
void Mesh::LoadShader(string vertexShader,string FragmentShader){}
