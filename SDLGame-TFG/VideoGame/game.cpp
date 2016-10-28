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
    vec3f position(0.0,0.0,1);
    vec3f direction(0.0,0.0,0.0);
    vec3f up(0.0,1.0,0.0);
    aContext.camera.setOrthographicProjection(-5,5,-5,5,-5,5);
    aContext.camera.setCamera(position,direction,up);
    aContext.camera.createCamera();

    rootMap->initStatic();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    Matrix4f movCamera,auxCamera;
    vec4f posCamera;

    while (!quit)
    {
        while (SDL_PollEvent(&event)){

            if (event.type == SDL_QUIT){
                quit = true;
            }
            //movCamera.translation(position.x,position.y,position.z);
            posCamera=vec4f();
            //case: Player push a buttom
            if (event.type == SDL_KEYDOWN){

                switch (event.key.keysym.sym){

                    case SDLK_LEFT:
                        movCamera.translation(-0.1,0.0,0.0);
                        break;
                    case SDLK_RIGHT:
                        movCamera.translation(0.1,0.0,0.0);
                        break;
                    case SDLK_UP:
                        movCamera.translation(0.0,0.1,0.0);
                        break;
                    case SDLK_DOWN:
                        movCamera.translation(0.0,-0.1,0.0);
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

                //posCamera.x=position.x;posCamera.y=position.y;posCamera.z=position.z;posCamera.w=1;
                /*movCamera.product(auxCamera.getMatrix());
                posCamera=movCamera.product(posCamera);
                position.x+=posCamera.x; position.y+=posCamera.y; position.z+=0;
                cout<< "posCamera: x-> "<< posCamera.x<< " y-> "<< posCamera.y<<" z-> "<< posCamera.z<<endl;
                cout<< "Position: x-> "<< position.x<< " y-> "<< position.y<<" z-> "<< position.z<<endl;
                aContext.camera.setCamera(position,direction,up);
                aContext.camera.createCamera();*/
                aContext.camera.moveCamera(movCamera);
            }
        }
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        rootMap->visualization(aContext);
        aContext.posObject.clear();
        window->updateScreen();
    }
}
