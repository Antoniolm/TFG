// *********************************************************************
// **
// ** Copyright (C) 2016 Antonio David López Machado
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
    window=new Window("Prueba",800,600);
    window->createWindow();
}

//**********************************************************************//

Game::~Game(){
}

//**********************************************************************//

void Game::loop(){
    bool quit = false;
    SDL_Event event;

    NodeSceneGraph root;
    Mesh * aObject=new Mesh();
    aObject->init();
    root.add(static_cast<Object3D*>(aObject));
    Context aContext;

    sound sonido;
    sonido.loadSound("beat.wav",0,0);
    sonido.play();

    while (!quit)
    {
        while (SDL_PollEvent(&event)){

            if (event.type == SDL_QUIT){
                quit = true;
            }
            if( event.type== SDL_KEYDOWN){
                sonido.pause();
            }
            if( event.type== SDL_KEYUP){
                sonido.resume();
            }
        }
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        root.visualization(aContext);
        window->updateScreen();
    }
}
