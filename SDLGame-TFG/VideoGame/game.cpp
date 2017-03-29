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
    gameState.controlMenu=new ControlMenu();
    heroState=new HeroState();

    isClosing=false;

    notiGamePad=new Notification(vec3f(0.0,0.0,0.0),vec3f(0.0,0.0,0.0),0,mVOID);

    //////////////////////////////////////////////////////
    /////         Initialize controller              /////
    //////////////////////////////////////////////////////
    gameState.controller=new ControllerManager();
}

//**********************************************************************//

Game::~Game(){
    delete window;
    delete notiGamePad;
    delete shadowShader;
    delete normalShader;
    delete options;

    MeshCollection * meshCollect= MeshCollection::getInstance();
    delete meshCollect;

    MaterialCollection * materialCollect= MaterialCollection::getInstance();
    delete materialCollect;

    SoundCollection * soundCollect= SoundCollection::getInstance();
    delete soundCollect;
}

//**********************************************************************//

void Game::setClose(bool value){
    isClosing=value;
}

//**********************************************************************//

void Game::loop(){
    SDL_Event event;
    float time;
    string fileMap;
    bool firstTime=true;
    int windowH=800,windowW=1200;
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

    // Configure depth map FBO
    ShadowTexture * depthTexture=new ShadowTexture();

    //Show our window.
    window->showScreen();
    while (!isClosing)
    {
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                isClosing = true;
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
            gameState.controlMenu->updateState(gameState);

            gameState.camera->activateOrthoProjection(context.currentShader->getProgram());
            if(!gameState.optionMenu->isActivate() && !gameState.controlMenu->isActivate())
                gameState.mainMenu->visualization(context);

            gameState.optionMenu->visualization(context);
            gameState.controlMenu->visualization(context);
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
            heroState->updateState(gameState);

            //Update the camera, lifeText, coinText, profile
            gameState.camera->update(gameState,context.currentShader->getProgram(),
                          (gameState.pauseMenu->isActivate() || gameState.deadMenu->isActivate() || gameState.mainMenu->isActivate()));

            notiGamePad->updateState(gameState);

            profile->addUpdateTime(SDL_GetTicks()-gameState.time);

            ///////////////////
            // VISUALIZATION
            ///////////////////
            time=SDL_GetTicks();
            vec3f pos=hero->getPosition();

            //1- Render of our deph map for shadow mapping
            GLfloat near_plane = -1.0f, far_plane = 10.0f;
            Camera lightCamera(vec3f(pos.x-1.0, pos.y+5.0f,pos.z-2.0),vec3f(pos.x,0.0,pos.z),vec3f(0.0,1.0,0.0));
            lightCamera.setOrthographicProjection(-20.0,20.0,-20.0,20.0,near_plane,far_plane);

            Matrix4f lightSpace;
            lightSpace.setMatrix(lightCamera.getView());
            lightSpace.product(lightCamera.getOrthoProyection().getMatrix());

            context.currentShader=shadowShader;
            glUseProgram(context.currentShader->getProgram()); //We use the program now
            glUniformMatrix4fv(glGetUniformLocation(context.currentShader->getProgram(), "lightSpaceMatrix"), 1, GL_FALSE, lightSpace.getMatrix());

            depthTexture->setShadowBuffer(true);
            gameState.rootMap->visualization(context);
            depthTexture->setShadowBuffer(false);


            //2- Normal render of our scene
            glViewport(0, 0, windowW, windowH);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            context.currentShader=normalShader;
            glUseProgram(context.currentShader->getProgram()); //We use the program now
            gameState.camera->activateCamera(context.currentShader->getProgram());
            gameState.rootMap->activatedLight(context.currentShader->getProgram());
            glUniform1i(glGetUniformLocation(context.currentShader->getProgram(), "ourTexture"), 0);
            glUniform1i(glGetUniformLocation(context.currentShader->getProgram(), "normalMap"), 1);
            glUniform1i(glGetUniformLocation(context.currentShader->getProgram(), "shadowMap"), 2);
            glUniform3f(glGetUniformLocation(context.currentShader->getProgram(), "lightPosVertex"),pos.x-1.0, pos.y+5.0f,pos.z-2.0);
            gameState.camera->activatePerspecProjection(context.currentShader->getProgram());
            glUniformMatrix4fv(glGetUniformLocation(context.currentShader->getProgram(), "lightSpaceMatrix"), 1, GL_FALSE, lightSpace.getMatrix());

            glActiveTexture(GL_TEXTURE2);
            depthTexture->bindTexture();
            gameState.rootMap->visualization(context);


            gameState.camera->activateOrthoProjection(context.currentShader->getProgram());
            heroState->visualization(context);
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
