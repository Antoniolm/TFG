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

#ifndef WINDOW_H
#define WINDOW_H

#include <glew.h>
#include <SDL.h>
#include <SDL_gamecontroller.h>
#include <SDL_opengl.h>
#include <SDL_mixer.h>
#include <SDL_TTF.h>
#include <gl/glu.h>
#include <gl/gl.h>
#include <stdio.h>
#include <string>
#include "sound.h"

using namespace std;
class Window
{
    public:


        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Window();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Will set the initial parameters
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setParameters(const string & aTitle,int aHeight,int aWidth);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Will create a SDL2 window
        *    \return true if the window was created and false if
        *    the window had an error
        */
        //////////////////////////////////////////////////////////////////////////
        bool createWindow();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Will destroy a SDL2 window
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void closeWindow();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Will show the window
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void showScreen();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Will hide the window
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void hideScreen();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Will update the current screen in the window.
        */
        //////////////////////////////////////////////////////////////////////////
        void updateScreen();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Will clean the screen in the window.
        */
        //////////////////////////////////////////////////////////////////////////
        void cleanScreen();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will resize our window
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void resizeWindow(int windowH,int windowW);

        static Window * getInstance(){
            if(instance == NULL)
                instance = new Window();

            return instance;
        }

        void fullScreen(bool value);
    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Window();

        static Window* instance;
        SDL_Window * window;
        SDL_GLContext context;
        string title;
        int height;
        int width;
};

#endif // WINDOW_H
