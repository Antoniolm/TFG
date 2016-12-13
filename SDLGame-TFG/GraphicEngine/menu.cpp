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
    activateMenu=false;
    Mesh * textObject=new Mesh(string("geometries/text.obj"));
    textObject->init();

    Material * material=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/menuBack.png");

    positionMenu=new Matrix4f();
    positionMenu->identity();
    positionMenu->translation(1.0,2.5,0.5);
    Matrix4f * scaleMenu=new Matrix4f();
    scaleMenu->scale(4.0,10.0,4.0);

    root=new NodeSceneGraph();
    root->add(positionMenu);
    root->add(scaleMenu);
    root->add(material);
    root->add(textObject);
}

//**********************************************************************//

Menu::~Menu()
{
    //dtor
}

//**********************************************************************//

void Menu::visualization(Context & cv){
    if(activateMenu)
        root->visualization(cv);
}

//**********************************************************************//

void Menu::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap){
    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_ESCAPE)]){
        activateMenu=!activateMenu;
    }
}
