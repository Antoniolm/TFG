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

#include "menu.h"

Menu::Menu()
{
    Mesh * textObject=new Mesh(string("geometries/text.obj"));
    textObject->init();

    positionMenu=new Matrix4f();
    positionMenu->identity();
    Matrix4f * scaleMenu=new Matrix4f();
    scaleMenu->scale(1.0,0.3,1.0);

    root=new NodeSceneGraph();
    root->add(positionMenu);
    root->add(scaleMenu);
    root->add(textObject);
}

//**********************************************************************//

Menu::~Menu()
{
    //dtor
}

//**********************************************************************//

void Menu::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void Menu::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap  ){
}
