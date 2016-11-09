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
    window=new Window("Prueba",800,600);
    window->createWindow();
    rootMap=new RootMap();
}

//**********************************************************************//

Game::~Game(){
}

//**********************************************************************//

void Game::loop(){
    bool quit = false;
    SDL_Event event;
    Context aContext;
    vec3f position(0.0,-1.0,-1.0);
    vec3f direction(0.0,0.0,0.0);
    vec3f up(0.0,1.0,0.0);
    aContext.camera.setOrthographicProjection(-5,5,-5,5,-5,5);
    aContext.camera.setCamera(position,direction,up);
    aContext.camera.createCamera();

    hero=new Hero();
    rootMap->setHero(hero);
    Matrix4f movCamera;
    Matrix4f * moveHero=new Matrix4f();
    moveHero->identity();
    while (!quit)
    {
        while (SDL_PollEvent(&event)){

            if (event.type == SDL_QUIT){
                quit = true;
            }
            //case: Player push a buttom
            if (event.type == SDL_KEYDOWN){

                switch (event.key.keysym.sym){

                    case SDLK_LEFT:
                        movCamera.identity();
                        moveHero->translation(-0.1,0.0,0.0);
                        break;
                    case SDLK_RIGHT:
                        movCamera.identity();
                        moveHero->translation(0.1,0.0,0.0);
                        break;
                    case SDLK_UP:
                        movCamera.identity();
                        moveHero->translation(0.0,0.0,0.1);
                        break;
                    case SDLK_DOWN:
                        movCamera.identity();
                        moveHero->translation(0.0,0.0,0.1);
                        break;
                    case SDLK_k:
                        movCamera.scale(1.1,1.1,1.1);
                        break;
                    case SDLK_l:
                        movCamera.scale(0.9,0.9,0.9);
                        break;
                    case SDLK_w:
                        movCamera.rotation(5,1.0,0.0,0.0);
                        break;
                    case SDLK_s:
                        movCamera.rotation(-5,1.0,0.0,0.0);
                        break;
                    case SDLK_a:
                        movCamera.rotation(5,0.0,1.0,0.0);
                        break;
                    case SDLK_d:
                        movCamera.rotation(-5,0.0,1.0,0.0);
                        break;
                }
                hero->moveBody(moveHero);
                aContext.camera.moveCamera(movCamera);

            }
        }
        window->cleanScreen();
        rootMap->visualization(aContext);
        aContext.posObject.clear();
        window->updateScreen();
    }
}
