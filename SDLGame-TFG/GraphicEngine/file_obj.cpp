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

void readMesh(const char * fileName,std::vector<float> & vertex,std::vector<int> & triangles){
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
            cout<< "x->"<< x<< " y->"<< y<< " z->"<< z<< endl;
            vertex.push_back(x);vertex.push_back(y);vertex.push_back(z);
        }
        else if (line.substr(0,2) == "f ")
        {
            line=line.substr(2);
            value=atoi(&line[0]);
            value--;
            cout<< "Valor-> "<< value<< endl;
            triangles.push_back(value);
            while(!line.empty()){
                while(!line.empty() && line.substr(0,1)!=" "){
                    line=line.substr(1);
                }
                if(!line.empty()){
                    line=line.substr(1);
                    value=atoi(&line[0]);
                    value--;
                    cout<< "Valor-> "<< value<< endl;
                    triangles.push_back(value);
                }
            }
        }
    }

}

void readEverything(const char * fileName,std::vector<float> & vertex,std::vector<int> & triangles,std::vector<float> & normals,std::vector<float> & normalFaces,std::vector<float> & textureCord,std::vector<int> & textureFaces){
    int value;
    char charValue;
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
            cout<< "x->"<< x<< " y->"<< y<< " z->"<< z<< endl;
            vertex.push_back(x);vertex.push_back(y);vertex.push_back(z);
        }
        else if (line.substr(0,2) == "f "){
            line=line.substr(2);
            istringstream s(line);
            for(int i=0;i<3;i++){
                //Extract the triangle face
                s >> value;
                cout<< "Value->"<< value-1<< endl;
                triangles.push_back(value--);

                //Extract the texture face
                s >> charValue; //Extract the char between element
                s >> value;
                textureFaces.push_back(value--);

                //Extract the normals face
                s >> charValue; //Extract the char between element
                s >> value;
                normalFaces.push_back(value--);
            }
        }
        else if (line.substr(0,3) == "vn "){
            istringstream s(line.substr(3));
            float x,y,z;
            s >> x;
            s >> y;
            s >> z;
            cout<< "x->"<< x<< " y->"<< y<< " z->"<< z<< endl;
            normals.push_back(x);normals.push_back(y);normals.push_back(z);

        }
        else if (line.substr(0,3) == "vt "){
            istringstream s(line.substr(3));
            float x,y,z;
            s >> x;
            s >> y;
            textureCord.push_back(x);textureCord.push_back(y);

        }
    }

}


}
