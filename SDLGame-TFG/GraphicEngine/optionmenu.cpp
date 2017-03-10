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

#include "optionmenu.h"

OptionMenu::OptionMenu()
{
    currentOption=0;
    activateMenu=false;
    MeshCollection * meshCollect =MeshCollection::getInstance();
    SoundCollection * soundCollect =SoundCollection::getInstance();

    currentMaterial=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/optionResol.png");
    Material * materialBack=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/mainBackMenu.png");

    //Initialize text
    TTF_Font *font=TTF_OpenFont( "font/Xolonium-Regular.ttf", 15);
    resolText=new Text(mVOID,font);
    resolText->setMessage("1408x1900");
    resolText->init();
    resolText->setScaleDialog(vec3f(0.1,0.2,0.5));
    resolText->setScaleText(vec3f(0.1,0.2,0.5));
    resolText->setPosition(vec3f(0.15,7.07,11.1));
    windText=new Text(mVOID,font);
    windText->setMessage("Window");
    windText->init();
    windText->setScaleDialog(vec3f(0.1,0.2,0.5));
    windText->setScaleText(vec3f(0.1,0.2,0.5));
    windText->setPosition(vec3f(0.15,6.95,11.2));
    volText=new Text(mVOID,font);
    volText->setMessage("100");
    volText->init();
    volText->setScaleDialog(vec3f(0.05,0.2,0.5));
    volText->setScaleText(vec3f(0.05,0.2,0.5));
    volText->setPosition(vec3f(0.15,6.83,11.3));

    //Transformation
    positionMenu=new Matrix4f();
    positionMenu->translation(0.0,6.752,11.0);

    Matrix4f * betweenMenu=new Matrix4f();
    betweenMenu->translation(0.0,0.0,-0.2);

    Matrix4f * scaleMenu=new Matrix4f();
    scaleMenu->scale(0.4,1.8,0.5);
    Matrix4f * scaleMenuBack=new Matrix4f();
    scaleMenuBack->scale(2.5,2.275,2.5);

    Matrix4f * rotationMenu=new Matrix4f();
    rotationMenu->rotation(20,1.0,0.0,0.0);

    root=new NodeSceneGraph(false,true);
    root->add(positionMenu);
    root->add(rotationMenu);
    root->add(scaleMenu);
    root->add(currentMaterial);
    root->add(meshCollect->getMesh(TEXT));
    root->add(betweenMenu);
    root->add(scaleMenuBack);
    root->add(materialBack);
    root->add(meshCollect->getMesh(TEXT));
    currentTime=SDL_GetTicks();
    menuDelay=currentTime;

    openSound=soundCollect->getSound(sOpen);
    moveSound=soundCollect->getSound(sCoin);

    //Add the options
    addOption(new Texture("./textures/optionResol.png"));
    addOption(new Texture("./textures/optionWindow.png"));
    addOption(new Texture("./textures/optionVolume.png"));
    addOption(new Texture("./textures/optionSave.png"));
    addOption(new Texture("./textures/optionQuit.png"));
}

//**********************************************************************//

OptionMenu::~OptionMenu()
{
    delete root;

    for(unsigned i=0;i<options.size();i++)
        delete options[i];
}

//**********************************************************************//

void OptionMenu::visualization(Context & cv){
    if(activateMenu){
        root->visualization(cv);

        resolText->visualization(cv);
        windText->visualization(cv);
        volText->visualization(cv);
    }
}

//**********************************************************************//

void OptionMenu::updateState(GameState & gameState){
    vec3f position;
     string fileLoad;

    float time=gameState.time;
    ControllerManager * controller=gameState.controller;

    if(time-currentTime>200)
        currentTime=time-50;

    if(activateMenu){ //If the menu is activated
        if(controller->checkButton(cUP) && menuDelay<(time-300)){ //If the user push the action move on the menu
            currentOption-=1;
            if(currentOption==-1)
                currentOption=(options.size()-1);

            currentMaterial->setTexture(options[currentOption]);
            menuDelay=time;
            moveSound->play();
        }
        else if(controller->checkButton(cDOWN) && menuDelay<(time-300)){ //If the user push the action move on the menu
            currentOption++;
            if((unsigned)currentOption==options.size())
                currentOption=0;

            currentMaterial->setTexture(options[currentOption]);
            menuDelay=time;
            moveSound->play();
        }
        if(controller->checkButton(cLEFT) && menuDelay<(time-300)){ //If the user push the action move on the menu
            switch(currentOption){
                case 0: //Exit
                    //activateMenu=false;
                break;
                case 1: //Exit
                    //activateMenu=false;
                break;
                case 2: //Exit
                    //activateMenu=false;
                break;
            }
            menuDelay=time;
            moveSound->play();
        }

        if(controller->checkButton(cRIGHT) && menuDelay<(time-300)){ //If the user push the action move on the menu
            switch(currentOption){
                case 0: //Exit
                    //activateMenu=false;
                break;
                case 1: //Exit
                    //activateMenu=false;
                break;
                case 2: //Exit
                    //activateMenu=false;
                break;
            }
            menuDelay=time;
            moveSound->play();
        }


        if(controller->checkButton(cACTION) && menuDelay<(time-300)){ //If the user push the action intro
            SavedManager * saveManager;
            switch(currentOption){
                case 3: //Exit
                    activateMenu=false;
                break;
                case 4: //Exit
                    activateMenu=false;
                break;
            }

            menuDelay=time;
            controller->setState(false,cACTION);
        }
    }

    currentTime+=time-currentTime;
}

//**********************************************************************//

void OptionMenu::setPosition(vec3f aPosition){
    positionMenu->translation(aPosition.x,aPosition.y+6.75,aPosition.z+11.0);
}


//**********************************************************************//

void OptionMenu::activate(){
    activateMenu=true;
    currentOption=0;
    currentMaterial->setTexture(options[currentOption]);
}
