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
    window->setParameters("SDL_Game",800,600);
    window->createWindow();

    //Create our shader
    context.currentShader.setFiles("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    context.currentShader.createProgram();
    glUseProgram(context.currentShader.getProgram()); //We use the program now

    //Create the json document-> We changed that when the game has more maps.
    FILE* fp = fopen("./maps/map.json", "rb"); // non-Windows use "r"
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document document;
    document.ParseStream(is);
    rootMap=new RootMap(document,context.currentShader);
    fclose(fp);

    pauseMenu = new PauseMenu();
    mainMenu = new MainMenu();
    mainMenu->activate();
    deadMenu = new DeadMenu();

    //////////////////////////////////////////////////////
    /////             Initialize text                /////
    //////////////////////////////////////////////////////
    TTF_Font *font=TTF_OpenFont( "font/lazy.ttf", 15);
    SDL_Color color= {255,0,0};
    lifeText=new Text("",font,color,false);

    SDL_Color color2= {0,255,0};
    coinText=new Text("",font,color2,false);
}

//**********************************************************************//

Game::~Game(){
    delete instance;
    delete window;
    delete rootMap;
    delete hero;
}

//**********************************************************************//

void Game::loop(){
    bool quit = false;
    SDL_Event event;
    const Uint8* currentKeyStates;
    vec3f posHero;
    float time;
    bool wasActivatedMenu=false;
    int windowH=800,windowW=600;
    int lastLife=160,currentCoin=-10;

    hero=new Hero();
    rootMap->setHero(hero);

    //Create our camera
    vec3f position(2.0,4.0,5.0);
    vec3f direction(2.0,3.0,0.0);
    vec3f up(0.0,1.0,0.0);
    context.camera.setPerspectiveProjection(30.0f,(float)( 800.0f / 600.0f), 0.1f, 200.0f);
    context.camera.setCamera(position,direction,up);
    context.camera.createCamera();
    context.camera.activateCamera(&context.currentShader);

    //Show our window.
    window->showScreen();
    while (!quit)
    {
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }
            if( event.window.event==SDL_WINDOWEVENT_RESIZED ){
                if(event.window.data2<600)windowH=600; //MinHeight
                else windowH=event.window.data2;

                if(event.window.data1<400) windowW=400; //MinWidth
                else windowW=event.window.data1;

                window->resizeWindow(windowH,windowW);
                if(windowW > windowH)
                    context.camera.setPerspectiveProjection(30.0f,(float)( windowW / windowH), 0.1f, 200.0f);
                else //fix
                    context.camera.setPerspectiveProjection(30.0f,(float)( windowH / windowW), 0.1f, 200.0f);
                context.camera.activateCamera(&context.currentShader);
            }
        }

        currentKeyStates=SDL_GetKeyboardState(NULL);

        window->cleanScreen();

        //Update the states
        time=SDL_GetTicks();

        if(!mainMenu->isActivate() && !deadMenu->isActivate()) //if  mainMenu and deadMenu is not activate
            pauseMenu->updateState(time,currentKeyStates,rootMap);
        else{ //If some of that menu are activate
            if(mainMenu->isActivate())
                mainMenu->updateState(time,currentKeyStates,rootMap);
            else
                deadMenu->updateState(time,currentKeyStates,rootMap);
        }


        if(!pauseMenu->isActivate() && !mainMenu->isActivate() && !deadMenu->isActivate()){ //If  menu is not activate
            rootMap->updateState(time,currentKeyStates,rootMap);
            if(wasActivatedMenu) //If is the first time that it is not activated
                rootMap->enableSound(true);
            wasActivatedMenu=false;
        }
        else{ //Else menu is activated
            if(!wasActivatedMenu) //If is the first time that it is activated
                rootMap->enableSound(false);
            wasActivatedMenu=true;
        }

        //Update the camera, lifeText, coinText
        posHero=hero->getPosition();
        context.camera.moveCamera(vec3f(posHero.x,posHero.y+4.0f,posHero.z+10.0f),posHero,&context.currentShader);
        updateLife(lastLife);
        updateCoin(currentCoin);

        //context.camera.setPerspectiveProjection(30.0f,(float)( 800 / 600), 0.1f, 200.0f);
        //context.camera.activateCamera(&context.currentShader);
        rootMap->visualization(context);

        //context.camera.setOrthographicProjection(-1,1,-1,1,-3,3);
        //context.camera.activateCamera(&context.currentShader);
        lifeText->visualization(context);
        coinText->visualization(context);
        pauseMenu->visualization(context);
        mainMenu->visualization(context);
        deadMenu->visualization(context);

        window->updateScreen();

        if(hero->getLife()<=0.0)
            deadMenu->activate();
    }
}

//**********************************************************************//

void Game::updateLife(int & lastLife){
    vec3f posHero=hero->getPosition();
    lifeText->setPosition(vec3f(posHero.x-0.75,posHero.y+3.55,posHero.z+7.0));
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
    coinText->setPosition(vec3f(posHero.x+0.75,posHero.y+3.55,posHero.z+7.0));
    std::stringstream coin;
    coin<< hero->getCoin();
    if(currentCoin!=hero->getCoin()){ //If the life has changed
        coinText->setMessage("Coins:"+coin.str());
        coinText->init();
        currentCoin=hero->getCoin();
    }
}
