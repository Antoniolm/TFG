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

#include "moviescreen.h"

MovieScreen::MovieScreen(vec3f pos,const Value & movieFeatures)
{
    currentOption=0;
    MeshCollection * meshCollect =MeshCollection::getInstance();

    if(movieFeatures.Size()==0){
        activated=false;
        root=0;
    }
    else{
        activated=true;
        currentMaterial=new Material(vec3f(1.0,1.0,1.0),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,movieFeatures[0]["texture"].GetString());

        for(unsigned i=0;i<movieFeatures.Size();i++){
            textures.push_back(movieFeatures[i]["texture"].GetString());
        }

        Matrix4f * positionMenu=new Matrix4f();
        positionMenu->translation(pos.x,pos.y+6.77,pos.z+11.0);

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
    }
    currentTime=SDL_GetTicks();
    loadDelay=currentTime;
}

//**********************************************************************//

MovieScreen::~MovieScreen()
{
    if(root!=0)
        delete root;
}

//**********************************************************************//

void MovieScreen::visualization(Context & cv){
    if(activated)
        root->visualization(cv);
}

//**********************************************************************//

void MovieScreen::updateState(GameState & gameState){
    float time=gameState.time;

    if(time-currentTime>200)
        currentTime=time-50;

    if(activated){
        if(gameState.controller->checkButton(cACTION) && loadDelay<(time-500)){ //If the user push the action intro
            currentOption++;

            if((unsigned)currentOption==options.size()){
                activated=false;
                currentOption=0;
            }

            currentMaterial->setTexture(options[currentOption]);
            loadDelay=time;

            gameState.controller->consumeButtons();
        }
    }

    currentTime+=time-currentTime;
}

//**********************************************************************//

void MovieScreen::setActivate(bool value){
    activated=value;
}

//**********************************************************************//

bool MovieScreen::isActivated(){
    return activated;
}

//**********************************************************************//

void MovieScreen::activateAllTexture(){
    if(textures.size()!=0){
        for(unsigned i=0;i<textures.size();i++)
            options.push_back(new Texture(textures[i]));

        //Set the first texture
        currentMaterial->setTexture(options[0]);
    }
}

