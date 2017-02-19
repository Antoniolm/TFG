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
////////////////////////////////////////

#include "game.h"

Game* Game::instance = NULL;

//**********************************************************************//

Game::Game(){
    window=Window::getInstance();
    window->setParameters("NapMare",1200,800);
    window->createWindow();

    //Create our shader
    context.currentShader.setFiles("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    context.currentShader.createProgram();
    glUseProgram(context.currentShader.getProgram()); //We use the program now

    //Create ours menus
    MeshCollection::getInstance();
    MaterialCollection::getInstance();

    mainMenu=MainMenu::getInstance();
    pauseMenu = new PauseMenu();
    deadMenu = new DeadMenu();
    loadScreen=new LoadingScreen(250);

    notiGamePad=new Notification(vec3f(0.0,0.0,0.0),vec3f(0.0,0.0,0.0),0,mVOID);

    //////////////////////////////////////////////////////
    /////             Initialize text                /////
    //////////////////////////////////////////////////////
    TTF_Font *font=TTF_OpenFont( "font/Xolonium-Regular.ttf", 10);
    SDL_Color color= {255,0,0};
    lifeText=new Text(mVOID,font,color,false);

    SDL_Color color2= {0,255,0};
    coinText=new Text(mVOID,font,color2,false);

    //////////////////////////////////////////////////////
    /////             Initialize controller          /////
    //////////////////////////////////////////////////////
    controller=new ControllerManager();

}

//**********************************************************************//

Game::~Game(){
    delete instance;
    delete window;
    delete rootMap;
    delete pauseMenu;
    delete mainMenu;
    delete deadMenu;
    delete loadScreen;
    delete lifeText;
    delete coinText;
    delete controller;

    delete notiGamePad;

    MeshCollection * meshCollect= MeshCollection::getInstance();
    delete meshCollect;

    MaterialCollection * materialCollect= MaterialCollection::getInstance();
    delete materialCollect;

    SoundCollection * soundCollect= SoundCollection::getInstance();
    delete soundCollect;
}

//**********************************************************************//

void Game::loop(){
    bool quit = false;
    SDL_Event event;
    vec3f posHero;
    float time;
    bool wasActivatedMenu=false;
    bool firstTime=true;
    int windowH=800,windowW=600;
    int lastLife=160,currentCoin=-10;
    Profile * profile=Profile::getInstance();
    GameState gameState;
    gameState.controller=controller;

    //Create our camera
    vec3f position(0,8.0f,13.0f);
    vec3f direction(0.0,0.0,0.0);
    vec3f up(0.0,1.0,0.0);
    Camera camera;
    camera.setPerspectiveProjection(30.0f,(float)( 1200.0f / 800.0f), 0.1f, 200.0f);
    camera.setOrthographicProjection(-1,1,-1,1,-3,3);
    camera.setCamera(position,direction,up);
    camera.createCamera();
    camera.activateCamera(context.currentShader.getProgram());
    camera.activateOrthoProjection(context.currentShader.getProgram());

    //Show our window.
    window->showScreen();
    while (!quit)
    {
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }
            if(event.type==SDL_WINDOWEVENT && event.window.event==SDL_WINDOWEVENT_RESIZED ){
                if(event.window.data2<800)windowH=800; //MinHeight
                else windowH=event.window.data2;

                if(event.window.data1<1000) windowW=1000; //MinWidth
                else windowW=event.window.data1;

                window->resizeWindow(windowH,windowW);
            }

            if((event.type==SDL_CONTROLLERBUTTONDOWN || event.type==SDL_CONTROLLERBUTTONUP || event.type==SDL_CONTROLLERDEVICEADDED
              || event.type==SDL_CONTROLLERDEVICEREMOVED || event.type==SDL_CONTROLLERAXISMOTION)){
                controller->checkEvent(event);;
            }

           if(event.type==SDL_CONTROLLERDEVICEADDED) //If the game is connected
                notiGamePad=new Notification(vec3f(0.3,7.4,10.6),vec3f(0.1,0.35,0.1),2000,mGMPADV);
            else if(event.type==SDL_CONTROLLERDEVICEREMOVED) //If the game is disconnected
                notiGamePad=new Notification(vec3f(0.3,7.4,10.6),vec3f(0.1,0.35,0.1),2000,mGMPADX);
        }

        controller->catchKeyBoardState(SDL_GetKeyboardState(NULL));
        window->cleanScreen();

        //CASE -> MAINMENU
        if(mainMenu->isActivate()){
            gameState.time=SDL_GetTicks();
            camera.setPosition(vec3f(0.0,0.0,0.0),context.currentShader.getProgram());
            mainMenu->updateState(gameState);

            camera.activateOrthoProjection(context.currentShader.getProgram());
            mainMenu->visualization(context);
            firstTime=true;
        }

        //CASE -> LOADING
        else if(RootMap::isLoading()){
            //loading screen here
            gameState.time=SDL_GetTicks();
            camera.setPosition(vec3f(0.0,0.0,0.0),context.currentShader.getProgram());
            loadScreen->updateState(gameState);

            camera.activateOrthoProjection(context.currentShader.getProgram());
            loadScreen->visualization(context);
            firstTime=true;
        }

        //CASE -> PLAYING
        else{
            if(firstTime){
                rootMap=gameState.rootMap;
                rootMap->activatedLight(context.currentShader.getProgram());
                rootMap->activatedObjectGroup();
                hero=rootMap->getHero();
                firstTime=false;
            }
            ///////////////////
            // UPDATE STATE
            ///////////////////
            gameState.time=SDL_GetTicks();

            if(hero->getLife()<=0.0){ //check if the hero is dead
                deadMenu->activate();
            }

            if(!deadMenu->isActivate() && !camera.isViewMode()) //if  mainMenu and deadMenu is not activate
                pauseMenu->updateState(gameState);
            else{ //If some of that menu are activate
                deadMenu->updateState(gameState);
            }


            if(!pauseMenu->isActivate() && !deadMenu->isActivate() && !camera.isViewMode()){ //If  menu is not activate
                rootMap->updateState(gameState);
                if(wasActivatedMenu) //If is the first time that it is not activated
                    rootMap->enableSound(true);
                wasActivatedMenu=false;
            }
            else{ //Else menu is activated
                if(!wasActivatedMenu) //If is the first time that it is activated
                    rootMap->enableSound(false);
                wasActivatedMenu=true;
            }

            //Update the camera, lifeText, coinText, profile
            posHero=hero->getPosition();

            camera.update(gameState,context.currentShader.getProgram(),
                          (pauseMenu->isActivate() || deadMenu->isActivate() || mainMenu->isActivate()));

            updateLife(lastLife);
            updateCoin(currentCoin);

            profile->addUpdateTime(SDL_GetTicks()-gameState.time);

            notiGamePad->updateState(gameState);

            ///////////////////
            // VISUALIZATION
            ///////////////////
            time=SDL_GetTicks();

            camera.activatePerspecProjection(context.currentShader.getProgram());
            rootMap->visualization(context);

            camera.activateOrthoProjection(context.currentShader.getProgram());
            lifeText->visualization(context);
            coinText->visualization(context);
            pauseMenu->visualization(context);
            deadMenu->visualization(context);
            notiGamePad->visualization(context);


            profile->addVisualTime(SDL_GetTicks()-time);
            profile->incrementFrames();

            if(rootMap->isFinished()){
                //delete gameState.rootMap;
                gameState.rootMap=new RootMap("./maps/map.json",true);

                controller->consumeButtons();
                firstTime=true;
            }

        }
        window->updateScreen();
    }

    profile->showResult();
}

//**********************************************************************//

void Game::updateLife(int & lastLife){
    vec3f posHero=hero->getPosition();
    lifeText->setPosition(vec3f(posHero.x-0.72,posHero.y+7.4,posHero.z+10.6));

    std::stringstream life;
    life<< hero->getLife();
    if(lastLife!=hero->getLife()){ //If the life has changed
        lifeText->setMessage(life.str()+"/150");
        lifeText->init();
        lastLife=hero->getLife();
    }
}

//**********************************************************************//

void Game::updateCoin(int & currentCoin){
    vec3f posHero=hero->getPosition();
    coinText->setPosition(vec3f(posHero.x+0.72,posHero.y+7.4,posHero.z+10.6));

    std::stringstream coin;
    coin<< hero->getCoin();
    if(currentCoin!=hero->getCoin()){ //If the life has changed
        coinText->setMessage("Crystal:"+coin.str());
        coinText->init();
        currentCoin=hero->getCoin();
    }
}
