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
    //Load the options of our user
    options=OptionManager::getInstance();
    options->load();

    pair<int,int> resolution=options->getResolution();
    window=Window::getInstance();
    window->setParameters("NapMare",1200,800);
    window->createWindow();
    window->fullScreen(!options->getWindow());

    //Set the setting of our user
    SoundCollection::getInstance()->updateVolume((float)options->getVolume()/100.0);

    //Create our shader
    normalShader=new Shader("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    shadowShader=new Shader("shaders/depthShader.vs","shaders/depthShader.fs");
    context.currentShader=normalShader;
    glUseProgram(context.currentShader->getProgram()); //We use the program now

    //Create ours menus
    MeshCollection::getInstance();
    MaterialCollection::getInstance();

    gameState.mainMenu=MainMenu::getInstance();
    gameState.pauseMenu = new PauseMenu();
    gameState.deadMenu = new DeadMenu();
    gameState.loadScreen=new LoadingScreen(250);
    gameState.optionMenu=new OptionMenu();

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
    gameState.controller=new ControllerManager();

}

//**********************************************************************//

Game::~Game(){
    delete instance;
    delete window;
    delete lifeText;
    delete coinText;
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
    string fileMap;
    bool firstTime=true;
    int windowH=800,windowW=600;
    int lastLife=160,currentCoin=-10;
    Profile * profile=Profile::getInstance();

    //Create our camera
    vec3f position(0,8.0f,13.0f);
    vec3f direction(0.0,0.0,0.0);
    vec3f up(0.0,1.0,0.0);

    gameState.camera=new Camera(position,direction,up);
    gameState.camera->activateCamera(context.currentShader->getProgram());

    pair<int,int> resolution=options->getResolution();
    gameState.camera->setPerspectiveProjection(30.0f,(float)( (float) resolution.first / (float) resolution.second), 0.1f, 200.0f);
    gameState.camera->setOrthographicProjection(-1,1,-1,1,-3,3);
    gameState.camera->activateOrthoProjection(context.currentShader->getProgram());

    //Show our window.
    window->showScreen();
    while (!quit)
    {
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }
            if(event.type==SDL_WINDOWEVENT && event.window.event==SDL_WINDOWEVENT_RESIZED ){
                if(event.window.data2<600)windowH=600; //MinHeight
                else windowH=event.window.data2;

                if(event.window.data1<800) windowW=800; //MinWidth
                else windowW=event.window.data1;

                window->resizeWindow(windowH,windowW);
            }

            if((event.type==SDL_CONTROLLERBUTTONDOWN || event.type==SDL_CONTROLLERBUTTONUP || event.type==SDL_CONTROLLERDEVICEADDED
              || event.type==SDL_CONTROLLERDEVICEREMOVED || event.type==SDL_CONTROLLERAXISMOTION)){
                gameState.controller->checkEvent(event);;
            }

           if(event.type==SDL_CONTROLLERDEVICEADDED) //If the game is connected
                notiGamePad=new Notification(vec3f(0.4,7.4,10.6),vec3f(0.05,0.175,0.05),2000,mGMPADV);
            else if(event.type==SDL_CONTROLLERDEVICEREMOVED) //If the game is disconnected
                notiGamePad=new Notification(vec3f(0.4,7.4,10.6),vec3f(0.05,0.175,0.05),2000,mGMPADX);
        }

        gameState.controller->catchKeyBoardState(SDL_GetKeyboardState(NULL));
        window->cleanScreen();

        //CASE -> MAINMENU
        if(gameState.mainMenu->isActivate()){
            gameState.time=SDL_GetTicks();
            gameState.camera->setPosition(vec3f(0.0,0.0,0.0),context.currentShader->getProgram());
            gameState.mainMenu->updateState(gameState);
            gameState.optionMenu->updateState(gameState);

            gameState.camera->activateOrthoProjection(context.currentShader->getProgram());
            if(!gameState.optionMenu->isActivate())
                gameState.mainMenu->visualization(context);
            gameState.optionMenu->visualization(context);
            firstTime=true;
        }

        //CASE -> LOADING
        else if(gameState.rootMap->isLoading()){
            //loading screen here
            gameState.time=SDL_GetTicks();
            gameState.camera->setPosition(vec3f(0.0,0.0,0.0),context.currentShader->getProgram());
            gameState.loadScreen->updateState(gameState);

            gameState.camera->activateOrthoProjection(context.currentShader->getProgram());
            gameState.loadScreen->visualization(context);
            firstTime=true;

            //Consume events
            gameState.controller->consumeButtons();
        }

        //CASE -> PLAYING
        else{
            if(firstTime){
                gameState.rootMap->activatedLight(context.currentShader->getProgram());
                gameState.rootMap->activatedObjectGroup();

                hero=gameState.rootMap->getHero();
                hero->setCoin(SavedManager::getInstance()->getCoin());

                gameState.movie=gameState.rootMap->getMovie();
                gameState.movie->activateAllTexture();
                firstTime=false;
            }
            ///////////////////
            // UPDATE STATE
            ///////////////////
            gameState.time=SDL_GetTicks();

            if(hero->getLife()<=0.0){ //check if the hero is dead
                gameState.deadMenu->activate();
            }

            gameState.movie->updateState(gameState);
            gameState.pauseMenu->updateState(gameState);
            gameState.deadMenu->updateState(gameState);
            gameState.rootMap->updateState(gameState);

            //Update the camera, lifeText, coinText, profile
            posHero=hero->getPosition();

            gameState.camera->update(gameState,context.currentShader->getProgram(),
                          (gameState.pauseMenu->isActivate() || gameState.deadMenu->isActivate() || gameState.mainMenu->isActivate()));

            updateLife(lastLife);
            updateCoin(currentCoin);
            notiGamePad->updateState(gameState);

            profile->addUpdateTime(SDL_GetTicks()-gameState.time);


            ///////////////////
            // VISUALIZATION
            ///////////////////
            time=SDL_GetTicks();

            gameState.camera->activatePerspecProjection(context.currentShader->getProgram());
            gameState.rootMap->visualization(context);

            gameState.camera->activateOrthoProjection(context.currentShader->getProgram());
            lifeText->visualization(context);
            coinText->visualization(context);
            gameState.pauseMenu->visualization(context);
            gameState.deadMenu->visualization(context);
            gameState.movie->visualization(context);
            notiGamePad->visualization(context);


            profile->addVisualTime(SDL_GetTicks()-time);
            profile->incrementFrames();

            if(gameState.rootMap->isFinished()){
                //Get the next Map and save the match
                fileMap=gameState.rootMap->getNextMap();
                SavedManager::getInstance()->save(fileMap,hero->getCoin());

                //Delete the currentMap
                delete gameState.rootMap;

                //Save the progress and create the new map
                SavedManager::getInstance()->save(fileMap,hero->getCoin());
                gameState.rootMap=new RootMap(fileMap,true);

                gameState.controller->consumeButtons();
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
