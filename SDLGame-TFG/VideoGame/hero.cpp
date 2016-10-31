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

#include "hero.h"

Hero::Hero()
{
    string file("geometries/cube.ply");
    Mesh * cube=new Mesh(file);
    cube->LoadShader("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    cube->init();

    file=string("geometries/sphere.ply");
    Mesh * sphere=new Mesh(file);
    sphere->LoadShader("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    sphere->init();

    file=string("geometries/cylinder.ply");
    Mesh * cylinder=new Mesh(file);
    cylinder->LoadShader("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    cylinder->init();

    root->add(static_cast<Object3D*>(cube));
}

//**********************************************************************//

Hero::~Hero()
{
    //dtor
}
