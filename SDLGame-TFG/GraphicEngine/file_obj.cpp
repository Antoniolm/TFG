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

#include "file_obj.h"

namespace obj{
using namespace std;

void readMesh(const char * fileName,std::vector<vec3f> & vertex,std::vector<GLushort> & triangles){
    int value;
    float x,y,z;
    string aux;
    istringstream * stream;
    ifstream in(fileName, ios::in);
    if (!in)
    {
        cout<< "Cannot open " << fileName << endl;
    }

    string line;
    while (getline(in, line))
    {
        if (line.substr(0,2) == "v ") { //Extract vertex
            stream=new istringstream(line.substr(2));
            (*stream) >> x;
            (*stream) >> y;
            (*stream) >> z;
            vertex.push_back(vec3f(x,y,z));
        }
        else if (line.substr(0,2) == "f "){ //Extract face
            stream=new istringstream(line.substr(2));
            for(int i=0;i<3;i++){
                (*stream) >> value;
                triangles.push_back((GLushort)--value);
                (*stream) >> aux;
            }
        }
    }

}

void readEverything(const char * fileName,std::vector<vec3f> & vertex,std::vector<GLushort> & triangles,std::vector<vec3f> & normals,std::vector<vec2f> & textureCord,bool flagNormal){
    int value;
    char charValue;
    float x,y,z;
    istringstream * stream;
    std::vector<vec3f> vertexAux;
    std::vector<vec3f> normalsVertex;
    std::vector<vec2f> textureVertex;
    std::vector<GLushort> trianglesIndex;
    std::vector<int> normalFaces;
    std::vector<int> textureFaces;
    ifstream in(fileName, ios::in);
    if (!in)
    {
        cout<< "Cannot open " << fileName << endl;
    }

    string line;
    while (getline(in, line))
    {
        if (line.substr(0,2) == "v "){ //Extract vertex
            stream=new istringstream(line.substr(2));
            (*stream) >> x;
            (*stream) >> y;
            (*stream) >> z;
            vertexAux.push_back(vec3f(x,y,z));
        }
        else if (line.substr(0,3) == "vn "){ //Extract normal face
            stream=new istringstream(line.substr(3));
            (*stream) >> x;
            (*stream) >> y;
            (*stream) >> z;
            normalsVertex.push_back(vec3f(x,y,z));

        }
        else if (line.substr(0,3) == "vt "){ //Extract texture Coord
            stream=new istringstream(line.substr(3));
            (*stream) >> x;
            (*stream) >> y;
            textureVertex.push_back(vec2f(x,y));

        }
        else if (line.substr(0,2) == "f "){
            stream=new istringstream(line.substr(2));
            for(int i=0;i<3;i++){
                //Extract the triangle face
                (*stream) >> value;
                trianglesIndex.push_back(--value);

                //Extract the texture face
                (*stream) >> charValue; //Extract the char between element
                (*stream) >> value;
                textureFaces.push_back(--value);

                //Extract the normals face
                (*stream) >> charValue; //Extract the char between element
                (*stream) >> value;
                normalFaces.push_back(--value);
            }
        }

    }
    std::vector<vec3f> normalAux;
    if(flagNormal)
        //calculate_normals(vertexAux,trianglesIndex,normalAux);

    for(int i=0;i<trianglesIndex.size();i++){
        vertex.push_back(vertexAux[trianglesIndex[i]]);
        normals.push_back(normalsVertex[normalFaces[i]]);
        textureCord.push_back(textureVertex[textureFaces[i]]);
        triangles.push_back(i);
    }
}

void calculate_normals(std::vector<vec3f> & vertex,std::vector<GLushort> & triangles,std::vector<vec3f> & normals){
    //Calculate face normals
    std::vector<vec3f> normalFace;
    vec3f p,k,n;
	float modulo;
	for(int i=0;i<triangles.size();i=i+3){

		p.x=vertex[triangles[i+1]].x-vertex[triangles[i]].x;
		p.y=vertex[triangles[i+1]].y-vertex[triangles[i]].y;
		p.z=vertex[triangles[i+1]].z-vertex[triangles[i]].z;

		k.x=vertex[triangles[i+2]].x-vertex[triangles[i+1]].x;
		k.y=vertex[triangles[i+2]].y-vertex[triangles[i+1]].y;
		k.z=vertex[triangles[i+2]].z-vertex[triangles[i+1]].z;

		n.x=(p.y*k.z)-(p.z*k.y);
		n.y=(p.z*k.x)-(p.x*k.z);
		n.z=(p.x*k.y)-(p.y*k.x);

		modulo = sqrt(n.x*n.x+n.y*n.y+n.z*n.z);
		n.x=n.x/modulo;
		n.y=n.y/modulo;
		n.z=n.z/modulo;

		normalFace.push_back(n);
	}

	//Calculate vertex normals
	for(int i=0;i<vertex.size();i++){
		normals.push_back(vec3f(0.0,0.0,0.0));
	}

    int cont=0;
	for(int j=0;j<triangles.size();j=j+3){
		normals[triangles[j]]=normals[triangles[j]] + normalFace[cont];
		normals[triangles[j+1]]=normals[triangles[j+1]] + normalFace[cont];
		normals[triangles[j+2]]=normals[triangles[j+2]] + normalFace[cont];
        cont++;
	}
    for(int k=0;k<normals.size();k++){
        modulo=sqrt(normals[k].x*normals[k].x+normals[k].y*normals[k].y+normals[k].z*normals[k].z);
        normals[k].x=normals[k].x/modulo;
        normals[k].y=normals[k].y/modulo;
        normals[k].z=normals[k].z/modulo;
	}

}

}


