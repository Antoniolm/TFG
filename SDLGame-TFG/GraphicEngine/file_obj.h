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

#ifndef FILE_OBJ_H
#define FILE_OBJ_H

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <istream>
#include "glew.h"
#include <cstdlib>
#include <math.h>
#include "structdata.h"

namespace obj{

void readMesh(const char * fileName,std::vector<float> & vertex,std::vector<GLushort> & triangles);

void readEverything(const char * fileName,std::vector<vec3f> & vertex,std::vector<GLushort> & triangles,std::vector<vec3f> & normals,std::vector<int> & normalFaces,std::vector<vec2f> & textureCord,std::vector<int> & textureFaces);

};

#endif // FILE_OBJ_H
