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

    //Create hero and our map
    hero=new Hero();
    rootMap=new RootMap(hero);
}

//**********************************************************************//

Game::~Game(){
}

//**********************************************************************//

void Game::loop(){
    bool quit = false;
    bool hasMove=false;
    SDL_Event event;
    const Uint8* currentKeyStates;
    Context aContext;

    //Create our shader
    aContext.currentShader.setFiles("shaders/vertexshader.vs","shaders/fragmentshader.fs");
    aContext.currentShader.createProgram();
    glUseProgram(aContext.currentShader.getProgram()); //We use the program now
    glUniform1i(glGetUniformLocation(aContext.currentShader.getProgram(), "numActivateLight"), 2);

    //Create our camera
    vec3f position(2.0,4.0,5.0);
    vec3f direction(2.0,3.0,0.0);
    vec3f up(0.0,1.0,0.0);
    aContext.camera.setPerspectiveProjection(30.0f,(float)( 800.0f / 600.0f), 0.1f, 200.0f);
    aContext.camera.setCamera(position,direction,up);
    aContext.camera.createCamera();
    aContext.camera.activateCamera(&aContext.currentShader);

    //Create our light
    Light dirLight(vec3f(0.0f, -1.0f, 0.0f),vec3f(0.3f, 0.3f, 0.3f),vec3f(0.2f, 0.2f, 0.2f),vec3f(0.2f, 0.2f, 0.2f));
    Light pointLight(vec3f(1.0f, 1.0f, 1.0f),vec3f(0.4f, 0.4f, 0.4f),vec3f(0.5f, 0.5f, 0.5f),vec3f(1.0f, 1.0f, 1.0f),1.0f,0.09,0.032);
    Light pointLight2(vec3f(4.0f, 1.0f, 1.0f),vec3f(0.4f, 0.4f, 0.4f),vec3f(0.5f, 0.5f, 0.5f),vec3f(1.0f, 1.0f, 1.0f),1.0f,0.09,0.032);

    //Activate our light
    dirLight.activate(&aContext.currentShader);
    pointLight.activate(&aContext.currentShader,"0");
    pointLight2.activate(&aContext.currentShader,"1");

    avatarDirection heroDir;
    vec3f moveHero;
    vec3f posHero;

    //Show our window.
    window->showScreen();

    while (!quit)
    {
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }
        }
        //case: Player push a bottom
        currentKeyStates = SDL_GetKeyboardState( NULL );

        //Case-> Push Left bottom
        if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)] && !currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)] &&
        !currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)]){
            moveHero.x=-3.0;moveHero.y=0.0;moveHero.z=0.0;
            heroDir=LEFTWARD;
            hasMove=true;
        }
        //Case-> Push Right bottom
        else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)]&& !currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)] &&
        !currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)]){
            moveHero.x=3.0;moveHero.y=0.0;moveHero.z=0.0;
            heroDir=RIGHTWARD;
            hasMove=true;
        }
        //Case-> Push Up bottom
        else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)]&& !currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)] &&
        !currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)]){
            moveHero.x=0.0;moveHero.y=0.0;moveHero.z=-3.0;
            heroDir=BACKWARD;
            hasMove=true;
        }
        //Case-> Push Down bottom
        else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)]&& !currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)] &&
        !currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)]){
            moveHero.x=0.0;moveHero.y=0.0;moveHero.z=3.0;
            heroDir=FORWARD;
            hasMove=true;
        }
        //Case-> Push Dowm-Left bottoms
        else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)] && currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)] ){
            moveHero.x=-2.0;moveHero.y=0.0;moveHero.z=2.0;
            heroDir=FOR_LEFTWARD;
            hasMove=true;
        }
        //Case-> Push Dowm-Right bottoms
        else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)] && currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)] ){
            moveHero.x=2.0;moveHero.y=0.0;moveHero.z=2.0;
            heroDir=FOR_RIGHTWARD;
            hasMove=true;
        }
        //Case-> Push Up-Left bottoms
        else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)] && currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)] ){
            moveHero.x=-2.0;moveHero.y=0.0;moveHero.z=-2.0;
            heroDir=BACK_LEFTWARD;
            hasMove=true;
        }
        //Case-> Push Up-Right bottoms
        else if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)] && currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)] ){
            moveHero.x=2.0;moveHero.y=0.0;moveHero.z=-2.0;
            heroDir=BACK_RIGHTWARD;
            hasMove=true;
        }
        else{ //Case-> If not move
            hasMove=false;
            if(!hero->isJump() && !hero->isFall()){
                hero->noMove();
            }
        }
        //Case-> Push Scape bottom to jump
        if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_SPACE)] && !hero->isJump() && !hero->isFall())
        {
            moveHero.x=0.0;moveHero.y=0.0;moveHero.z=0.0;
            hero->activeJump(50.0,60.0);
        }

        //Move the body
        if(hasMove &&hero->moveBody(moveHero,heroDir))
        {
            posHero=hero->getPosition();
            posHero.y+=4.0f;posHero.z+=8.0f;
            aContext.camera.moveCamera(posHero,hero->getPosition(),&aContext.currentShader);
        }

        window->cleanScreen();
        rootMap->updateState(SDL_GetTicks());
        rootMap->visualization(aContext);

        //If the jump is activate
        if(hero->isJump()){
            if(hero->jump()){
                posHero=hero->getPosition();
                posHero.y+=4.0f;posHero.z+=8.0f;
                aContext.camera.moveCamera(posHero,hero->getPosition(),&aContext.currentShader);
            }
        }
        //If the jump is not activate
        else if(hero->gravity(-20.0)){
                posHero=hero->getPosition();
                posHero.y+=4.0f;posHero.z+=8.0f;
                aContext.camera.moveCamera(posHero,hero->getPosition(),&aContext.currentShader);
        }
        window->updateScreen();
    }
}
