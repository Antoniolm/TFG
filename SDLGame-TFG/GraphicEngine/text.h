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

#ifndef TEXT_H
#define TEXT_H

#include "object3d.h"
#include "structdata.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_TTF.h>

class Text : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Text();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters */
        //////////////////////////////////////////////////////////////////////////
        Text(const string & aFile,int aHeight,int aWidth);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Text();

        void init();

        void visualization();

        void updateState(float time);

    protected:

    private:
        vec3f position;
        float height,width;
        SDL_Surface * surface;
        string fileTexture;
        GLuint texture;
        TTF_Font* font;
};

#endif // TEXT_H
