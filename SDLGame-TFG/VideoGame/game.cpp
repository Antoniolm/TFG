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
    vec3f posHero;

    TTF_Font *font=TTF_OpenFont( "font/lazy.ttf", 28 );
    Text aText("Esto es una prueba para ver si hace falta tocar las dimensiones de nuestro mesh","now",100,100,vec3f(0.0,2.0,0.0),font);
    aText.init();

    hero=new Hero();
    rootMap->setHero(hero);

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

    //Show our window.
    window->showScreen();
    while (!quit)
    {
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }
        }
        window->cleanScreen();
        rootMap->updateState(SDL_GetTicks());

        //Update the camera
        posHero=hero->getPosition();
        posHero.y+=3.0f;posHero.z+=8.0f;
        aContext.camera.moveCamera(posHero,hero->getPosition(),&aContext.currentShader);

        rootMap->visualization(aContext);
        //Context a;
        aText.visualization(aContext);

        window->updateScreen();
    }
}
