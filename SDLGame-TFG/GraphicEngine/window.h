#ifndef WINDOW_H
#define WINDOW_H

#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl/glu.h>
#include <gl/gl.h>
#include <stdio.h>
#include <string>

using namespace std;
class Window
{
    public:
        Window();
        Window(const Window & aWin);
        Window(string aFile,int aHeight,int aWidth);
        virtual ~Window();
        bool createWindow();
        void closeWindow();
        void render();


    protected:

    private:
        SDL_Window* window;
        SDL_GLContext context;
        string title;
        int height;
        int width;
};

#endif // WINDOW_H
