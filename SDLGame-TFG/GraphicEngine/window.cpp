#include "window.h"

Window::Window(){
    title="Test";
    height=800;
    width=600;
}

Window::~Window(){
    SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

Window::Window(string aTitle,int aHeight,int aWidth){
    title=aTitle;
    height=aHeight;
    width=aWidth;
}


/////////////////
//
//
//
/////////////////
bool Window::createWindow(){
    bool salida=true;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL_Error: %s\n", SDL_GetError());
		salida=false;
	}
	else {
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		window = SDL_CreateWindow(title.c_str() , SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, height, width, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
		if (window == NULL) {
			printf("SDL_Error: %s\n", SDL_GetError());
			salida=false;
		}
		else {
			context = SDL_GL_CreateContext(window);
			glOrtho(0.0f, 900.0f, 650.0f, 0.0f, -1.0f, 1.0f);

		}
	}
    SDL_GL_SetSwapInterval(1);
    glewExperimental=true;
    GLenum err=glewInit();
    return salida;
}

void Window::onRender(){
    SDL_GL_SwapWindow(window);
    SDL_Delay(1000 / 60); // 60 FPS
}

