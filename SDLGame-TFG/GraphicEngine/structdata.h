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

#ifndef STRUCTDATA_H
#define STRUCTDATA_H


struct vec3f{
    float x;
    float y;
    float z;
    vec3f(){}
    vec3f(float dx,float dy,float dz){
        x=dx;
        y=dy;
        z=dz;
    }
};

struct vec3i{
    int x;
    int y;
    int z;
    vec3i(){}
    vec3i(int dx,int dy,int dz){
        x=dx;
        y=dy;
        z=dz;
    }
};

#endif
