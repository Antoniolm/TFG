////////////////////////////////////////
//  Author: Antonio David López Machado
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

    while (!quit)
    {
        while (SDL_PollEvent(&event)){

            if (event.type == SDL_QUIT){
                quit = true;
            }
        }
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        root.visualization(aContext);
        window->updateScreen();
    }
}
