#include "game.h"

Game::Game(){
    window=new Window("Prueba",800,600);
    window->createWindow();
}

Game::~Game(){
}

void Game::loop(){
    bool quit = false;
    SDL_Event event;
    while (!quit)
    {
        while (SDL_PollEvent(&event)){

            if (event.type == SDL_QUIT){
                quit = true;
            }

        }
        //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        //glClear(GL_COLOR_BUFFER_BIT);

        window->onRender();
    }
}
