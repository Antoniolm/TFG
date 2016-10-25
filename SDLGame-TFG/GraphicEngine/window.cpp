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

#include "window.h"

Window::Window(){
    title="Test";
    height=800;
    width=600;
}

//**********************************************************************//

Window::~Window(){
    SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	Mix_Quit();
	SDL_Quit();

}

//**********************************************************************//

Window::Window(const string & aTitle,int aHeight,int aWidth){
    title=aTitle;
    height=aHeight;
    width=aWidth;
}

//**********************************************************************//

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
            //Initialize SDL_mixer
            if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ){
                    printf( "SDL_mxer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    salida = false;
            }
			context = SDL_GL_CreateContext(window);
		}
	}
    SDL_GL_SetSwapInterval(1);
    glewExperimental=true;
    GLenum err=glewInit();

    return salida;
}

//**********************************************************************//

void Window::updateScreen(){
    SDL_GL_SwapWindow(window);
    SDL_Delay(1000 / 60); // 60 FPS
}

