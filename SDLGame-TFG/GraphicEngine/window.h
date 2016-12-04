// *********************************************************************
// **
// ** Copyright (C) 2016-2017 Antonio David L�pez Machado
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
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Window();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with some parameters */
        //////////////////////////////////////////////////////////////////////////
        Window(const string & aFile,int aHeight,int aWidth);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Window();

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


    protected:

    private:
        SDL_Window* window;
        SDL_GLContext context;
        Mix_Music * music;
        string title;
        int height;
        int width;
};

#endif // WINDOW_H
