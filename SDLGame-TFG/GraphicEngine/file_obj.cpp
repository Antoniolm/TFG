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

void readMesh(const char * fileName,std::vector<float> & vertex,std::vector<GLushort> & triangles){
    int value;
    ifstream in(fileName, ios::in);
    if (!in)
    {
        cout<< "Cannot open " << fileName << endl;
    }

    string line;
    while (getline(in, line))
    {
        if (line.substr(0,2) == "v ")
        {
            istringstream s(line.substr(2));
            float x,y,z;
            s >> x;
            s >> y;
            s >> z;
            vertex.push_back(x);vertex.push_back(y);vertex.push_back(z);
        }
        else if (line.substr(0,2) == "f ")
        {
            istringstream s(line.substr(2));
            string aux;
            for(int i=0;i<3;i++){
                s >> value;
                triangles.push_back((GLushort)--value);
                s >> aux;
            }
        }
    }

}

void readEverything(const char * fileName,std::vector<vec3f> & vertex,std::vector<GLushort> & triangles,std::vector<vec3f> & normals,std::vector<int> & normalFaces,std::vector<vec2f> & textureCord,std::vector<int> & textureFaces){
    int value;
    char charValue;
    std::vector<vec3f> vertexAux;
    std::vector<vec3f> normalsVertex;
    std::vector<vec2f> textureVertex;
    std::vector<GLushort> trianglesIndex;
    ifstream in(fileName, ios::in);
    if (!in)
    {
        cout<< "Cannot open " << fileName << endl;
    }

    string line;
    while (getline(in, line))
    {
        if (line.substr(0,2) == "v ")
        {
            istringstream s(line.substr(2));
            float x,y,z;
            s >> x;
            s >> y;
            s >> z;
            vertexAux.push_back(vec3f(x,y,z));
        }
        else if (line.substr(0,2) == "f "){
            line=line.substr(2);
            istringstream s(line);
            for(int i=0;i<3;i++){
                //Extract the triangle face
                s >> value;
                trianglesIndex.push_back(--value);

                //Extract the texture face
                s >> charValue; //Extract the char between element
                s >> value;
                textureFaces.push_back(--value);

                //Extract the normals face
                s >> charValue; //Extract the char between element
                s >> value;
                normalFaces.push_back(--value);
            }
        }
        else if (line.substr(0,3) == "vn "){
            istringstream s(line.substr(3));
            float x,y,z;
            s >> x;
            s >> y;
            s >> z;
            normalsVertex.push_back(vec3f(x,y,z));

        }
        else if (line.substr(0,3) == "vt "){
            istringstream s(line.substr(3));
            float x,y;
            s >> x;
            s >> y;
            textureVertex.push_back(vec2f(x,y));

        }
    }

    for(int i=0;i<trianglesIndex.size();i++){
        vertex.push_back(vertexAux[trianglesIndex[i]]);
        normals.push_back(normalsVertex[normalFaces[i]]);
        textureCord.push_back(textureVertex[textureFaces[i]]);
        triangles.push_back(i);
    }

    /*float module;

    for(int k=0;k<normals.size();k=k+3){
		module=sqrt(normals[k]*normals[k]+normals[k+1]*normals[k+1]+normals[k+2]*normals[k+2]);

		normals[k]=normals[k]/module;
		normals[k+1]=normals[k+1]/module;
		normals[k+2]=normals[k+2]/module;
	}*/
}

    void calc_Normals(std::vector<float> & normals){


    }

}
