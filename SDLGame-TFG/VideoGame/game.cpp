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

    Context aContext;

    sound sonido;
    sonido.loadSound("beat.wav",0,0);
    //sonido.play();

    Matrix4f matrixone;
    matrixone.scale(0.5,0.2,1);

    Matrix4f matrixtwo;
    matrixtwo.translation(-0.5,-0.5,0);

    LinearMovement movet(0,0.1,0.0);


    MatrixStatic matrix(matrixone);
    MatrixStatic matrix2(matrixtwo);

    NodeSceneGraph *root2;
    matrixtwo.translation(0.5,0.5,0.0);
    MatrixStatic matrix3(matrixtwo);
    //root2->add(&matrix3);
    //root2->add(static_cast<Object3D*>(aObject));
    root.add(&matrix);
    root.add(static_cast<Object3D*>(aObject));

    //root.add(&movet);
    root.add(&matrix);
    root.add(&matrix2);
    root.add(static_cast<Object3D*>(aObject));

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
