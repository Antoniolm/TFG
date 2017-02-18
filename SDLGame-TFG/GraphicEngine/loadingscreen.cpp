// *********************************************************************
// **
// ** Copyright (C) 2016-2017 Antonio David L�pez Machado
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

#include "loadingscreen.h"

LoadingScreen::LoadingScreen()
{
    currentOption=0;
    MeshCollection * meshCollect =MeshCollection::getInstance();

    currentMaterial=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/loading1.png");

    Matrix4f * positionMenu=new Matrix4f();
    positionMenu->translation(0.0,6.77,11.0);

    Matrix4f * scaleMenu=new Matrix4f();
    scaleMenu->scale(1.0,4.1,0.5);

    Matrix4f * rotationMenu=new Matrix4f();
    rotationMenu->rotation(20,1.0,0.0,0.0);

    root=new NodeSceneGraph(false,true);
    root->add(positionMenu);
    root->add(rotationMenu);
    root->add(scaleMenu);
    root->add(currentMaterial);
    root->add(meshCollect->getMesh(TEXT));

    //Add the options
    options.push_back(new Texture("./textures/loading1.png"));
    options.push_back(new Texture("./textures/loading2.png"));
    options.push_back(new Texture("./textures/loading3.png"));

    currentTime=SDL_GetTicks();
    menuDelay=currentTime;
}

//**********************************************************************//

LoadingScreen::~LoadingScreen()
{
    delete root;

    for(unsigned i=0;i<options.size();i++)
        delete options[i];
}

//**********************************************************************//

void LoadingScreen::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void LoadingScreen::updateState(GameState & gameState){
    float time=gameState.time;

    if(time-currentTime>200)
        currentTime=time-50;

    currentTime+=time-currentTime;
}
