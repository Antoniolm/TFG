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

#include "mainmenu.h"
#include "game.h"

MainMenu* MainMenu::instance = NULL;

MainMenu::MainMenu()
{
    currentOption=0;
    activateMenu=true;
    MeshCollection * meshCollect =MeshCollection::getInstance();
    MaterialCollection * materialCollect =MaterialCollection::getInstance();
    SoundCollection * soundCollect =SoundCollection::getInstance();

    currentMaterial=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/mainMenuStart.png");
    Material * materialBack=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/mainBackMenu.png");

    positionMenu=new Matrix4f();
    positionMenu->translation(0.0,6.70,11.0);

    Matrix4f * betweenMenu=new Matrix4f();
    betweenMenu->translation(0.0,0.0,-0.2);

    Matrix4f * rotationMenu=new Matrix4f();
    rotationMenu->rotation(20,1.0,0.0,0.0);

    ///////////////////////
    //Text
    Matrix4f * positionText=new Matrix4f();
    positionText->translation(0.725,0.5,0.8);

    Matrix4f * scaleMenu=new Matrix4f();
    scaleMenu->scale(0.35,1.8,0.5);

    NodeSceneGraph * nodeText=new NodeSceneGraph(false,true);
    nodeText->add(positionText);
    nodeText->add(scaleMenu);
    nodeText->add(currentMaterial);
    nodeText->add(meshCollect->getMesh(TEXT));

    ///////////////////////
    //Back
    Matrix4f * scaleMenuBack=new Matrix4f();
    scaleMenuBack->scale(1.0,4.2,1.0);

    NodeSceneGraph * nodeBack=new NodeSceneGraph(false,true);
    nodeBack->add(scaleMenuBack);
    nodeBack->add(materialBack);
    nodeBack->add(meshCollect->getMesh(TEXT));

    root=new NodeSceneGraph(false,true);
    root->add(positionMenu);
    root->add(rotationMenu);
    root->add(betweenMenu);
    root->add(nodeBack);
    root->add(nodeText);
    currentTime=SDL_GetTicks();
    menuDelay=currentTime;

    openSound=soundCollect->getSound(sOpen);
    moveSound=soundCollect->getSound(sCoin);
}

//**********************************************************************//

MainMenu::~MainMenu()
{
    delete root;

    for(unsigned i=0;i<options.size();i++)
        delete options[i];

    delete currentMaterial;


}

//**********************************************************************//

void MainMenu::visualization(Context & cv){
    if(activateMenu)
        root->visualization(cv);
}

//**********************************************************************//

void MainMenu::updateState(GameState & gameState){
    vec3f position;
     string fileLoad;

    float time=gameState.time;
    ControllerManager * controller=gameState.controller;

    if(time-currentTime>200)
        currentTime=time-50;

    if(activateMenu && !gameState.optionMenu->isActivate() && !gameState.controlMenu->isActivate()){ //If the menu is activated
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

        //If the user push an option
        if(controller->checkButton(cACTION) && menuDelay<(time-300)){ //If the user push the action intro
            SavedManager * saveManager;
            switch(actionOption[currentOption]){
                case START: //Start Game
                    activateMenu=false;
                    if(gameState.rootMap!=0)
                        delete gameState.rootMap;

                    SavedManager::getInstance()->save("",0);
                    gameState.rootMap=new RootMap("./maps/map00.json",true);
                    openSound->play();
                break;
                case CONTINUE: //Continue
                    //Catch the saved progress and load the map
                    saveManager=SavedManager::getInstance();
                    saveManager->load();
                    fileLoad=saveManager->getMap();

                    if(fileLoad!=""){
                        activateMenu=false;
                        if(gameState.rootMap!=0)
                            delete gameState.rootMap;

                        gameState.rootMap=new RootMap(fileLoad,true);
                        openSound->play();
                    }
                break;
                case CONTROLS: //Controls
                    gameState.controlMenu->activate();
                    openSound->play();
                break;
                case OPTION: //Option
                    gameState.optionMenu->activate();
                    openSound->play();
                break;
                case EXIT: //Exit
                    (Profile::getInstance())->showResult();
                    Game::getInstance()->setClose(true);
                break;

            }

            menuDelay=time;
            controller->setState(false,cACTION);
        }
    }

    currentTime+=time-currentTime;
}

//**********************************************************************//

void MainMenu::add(string fileName,MainMenuOption aOption){
    addOption(new Texture(fileName.c_str()));
    actionOption.push_back(aOption);
}

//**********************************************************************//

void MainMenu::setPosition(vec3f aPosition){
    positionMenu->translation(aPosition.x,aPosition.y+6.75,aPosition.z+11.0);
}


//**********************************************************************//

void MainMenu::activate(){
    activateMenu=true;
    currentOption=0;
    currentMaterial->setTexture(options[currentOption]);
}


