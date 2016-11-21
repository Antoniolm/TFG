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

Game::Game(){
    window=new Window("SDL_Game",800,600);
    window->createWindow();
    rootMap=new RootMap();
    window->showScreen();
}

//**********************************************************************//

Game::~Game(){
}

//**********************************************************************//

void Game::loop(){
    bool quit = false;
    SDL_Event event;
    Context aContext;

    //Create our shader
    aContext.currentShader.setFiles("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    aContext.currentShader.createProgram();
    glUseProgram(aContext.currentShader.getProgram()); //We use the program now

    //Create our camera
    vec3f position(2.0,4.0,5.0);
    vec3f direction(2.0,3.0,0.0);
    vec3f up(0.0,1.0,0.0);
    aContext.camera.setPerspectiveProjection(30.0f,(float)( 800.0f / 600.0f), 0.1f, 200.0f);
    aContext.camera.setCamera(position,direction,up);
    aContext.camera.createCamera();
    aContext.camera.activateCamera(&aContext.currentShader);


    //Create our light
    Light dirLight(vec3f(0.0f, -1.0f, 0.0f),vec3f(0.4f, 0.4f, 0.4f),vec3f(0.5f, 0.5f, 0.5f),vec3f(0.2f, 0.2f, 0.2f));
    Light pointLight(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.4f, 0.4f, 0.4f),vec3f(0.5f, 0.5f, 0.5f),vec3f(1.0f, 1.0f, 1.0f),1.0f,0.09,0.032);

    //Activate our light
    dirLight.activate(&aContext.currentShader);
    pointLight.activate(&aContext.currentShader);

    avatarDirection heroDir;
    hero=new Hero();
    rootMap->setHero(hero);
    vec3f moveHero,movCamera;

    while (!quit)
    {
        //while (SDL_PollEvent(&event)){
            SDL_PollEvent(&event);
            if (event.type == SDL_QUIT){
                quit = true;
            }

            //case: Player push a buttom
            const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
            if (event.type == SDL_KEYDOWN){
                if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)]){
                    movCamera.x=-0.05; movCamera.y=0.0; movCamera.z=0.0;
                    moveHero.x=-3.0; moveHero.y=0.0; moveHero.z=0.0;
                    heroDir=LEFTWARD;
                }
                if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)]){
                    movCamera.x=+0.05; movCamera.y=0.0; movCamera.z=0.0;
                    moveHero.x=3.0; moveHero.y=0.0; moveHero.z=0.0;
                    heroDir=RIGHTWARD;
                }
                if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)]){
                    movCamera.x=0.0; movCamera.y=0.0; movCamera.z=-0.05;
                    moveHero.x=0.0; moveHero.y=0.0; moveHero.z=-3.0;
                    heroDir=BACKWARD;
                }
                if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)]){
                    movCamera.x=0.0; movCamera.y=0.0; movCamera.z=0.05;
                    moveHero.x=0.0; moveHero.y=0.0; moveHero.z=3.0;
                    heroDir=FORWARD;
                }
                if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)] && currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)] ){
                    movCamera.x=-0.05; movCamera.y=0.0; movCamera.z=0.05;
                    moveHero.x=-3.0; moveHero.y=0.0; moveHero.z=3.0;
                    heroDir=FOR_LEFTWARD;
                }
                if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)] && currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)] ){
                    movCamera.x=0.05; movCamera.y=0.0; movCamera.z=0.05;
                    moveHero.x=3.0; moveHero.y=0.0; moveHero.z=3.0;
                    heroDir=FOR_RIGHTWARD;
                }
                if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)] && currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)] ){
                    movCamera.x=-0.05; movCamera.y=0.0; movCamera.z=-0.05;
                    moveHero.x=-3.0; moveHero.y=0.0; moveHero.z=-3.0;
                    heroDir=BACK_LEFTWARD;
                }
                if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)] && currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)] ){
                    movCamera.x=0.05; movCamera.y=0.0; movCamera.z=-0.05;
                    moveHero.x=3.0; moveHero.y=0.0; moveHero.z=-3.0;
                    heroDir=BACK_RIGHTWARD;
                }


                if(hero->moveBody(moveHero,heroDir))
                    aContext.camera.moveCamera(movCamera,&aContext.currentShader);

            }
            else{
                hero->noMove();
            }
        //}
        window->cleanScreen();
        rootMap->visualization(aContext);
        hero->gravity(-60.0);
        aContext.posObject.clear();
        window->updateScreen();
    }
}
