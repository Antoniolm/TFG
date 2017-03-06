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
#include "file_obj.h"

Window* Window::instance = NULL;

//**********************************************************************//

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
	TTF_Quit();
	delete instance;

}

//**********************************************************************//

void Window::setParameters(const string & aTitle,int aHeight,int aWidth){
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
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

        window = SDL_CreateWindow(title.c_str() , 20, 30, height, width, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
		if (window == NULL) {
			printf("SDL_Error: %s\n", SDL_GetError());
			salida=false;
		}
		else {
            //Initialize SDL_mixer
            if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 512 ) == -1 ){
                    cout<< "SDL_mixer could not initialize!"<<endl;
                    salida = false;
            }
			context = SDL_GL_CreateContext(window);
		}
	}

    if ( TTF_Init( )== -1 ){
        cout << "SDL_ttf could not initialize! SDL_ttf Error:"<< endl;
        salida=false;
    }

    /////////////////////////////////////////////////////////////

    glewInit();

    glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glCullFace(GL_BACK);
    //glEnable(GL_FRAMEBUFFER_SRGB);
    Mix_AllocateChannels(16);

    return salida;
}

//**********************************************************************//

void Window::showScreen(){
    SDL_ShowWindow(window);
}

//**********************************************************************//

void Window::hideScreen(){
    SDL_HideWindow(window);
}

//**********************************************************************//

void Window::updateScreen(){
    SDL_GL_SwapWindow(window);
}

//**********************************************************************//

void Window::cleanScreen(){
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//**********************************************************************//

void Window::resizeWindow(int windowH,int windowW){
    height =windowH;
    width = windowW;

    SDL_SetWindowSize(window,width,height);
    glViewport(0,0,width,height);
}
