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
        /**  \brief Window::Window
        *    Constructor primitive
        */
        Window();

        /**  \brief Window::Window
        *    Constructor per copy
        */
        Window(const Window & aWin);

        /**  \brief Window::Window
        *    Constructor
        */
        Window(string aFile,int aHeight,int aWidth);

        /**  \brief Window::Window
        *    Destructor primitive
        */
        virtual ~Window();

        /**  \brief Window::createWindow
        *    Will create a window by SDL2
        */
        bool createWindow();

        /**  \brief Window::createWindow
        *    Will destroy a window by SDL2
        */
        void closeWindow();

        /**  \brief Window::createWindow
        *    Will update the current screen in the window.
        */
        void onRender();


    protected:

    private:
        SDL_Window* window;
        SDL_GLContext context;
        string title;
        int height;
        int width;
};

#endif // WINDOW_H
