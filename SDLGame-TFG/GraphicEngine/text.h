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

#ifndef TEXT_H
#define TEXT_H

#include "object3d.h"
#include "structdata.h"
#include "shader.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_mixer.h>
#include <SDL_TTF.h>
#include "shader.h"
#include <vector>
#include "mesh.h"
#include "nodescenegraph.h"

using namespace std;

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
        Text(const string &  aStringText,const string & aFile,int aHeight,int aWidth,vec3f aPosition,TTF_Font * aFont);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Text();

        void setParameters(const string &  aStringText,const string & aFile,int aHeight,int aWidth,vec3f aPosition,TTF_Font * aFont);
        void init();

        void visualization(Context & vis);

        void updateState(float time);

    protected:

    private:
        vec3f position;
        float height,width;
        SDL_Surface * surface;
        string fileTexture;
        string message;
        GLuint texture;
        TTF_Font* font;
        NodeSceneGraph * textNode;
};

#endif // TEXT_H
