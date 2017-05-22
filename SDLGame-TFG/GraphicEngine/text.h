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
#include "matrix/structdata.h"
#include "shader.h"
#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include <vector>
#include "mesh.h"
#include "nodescenegraph.h"
#include "texture.h"
#include "material.h"

using namespace std;
class NodeSceneGraph;
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
        Text(MaterialIndex material,TTF_Font * aFont,SDL_Color aColor=SDL_Color{0,0,0},bool ahasDialog=true);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Text();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set all the parameters for the use of our text
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setParameters(MaterialIndex material,TTF_Font * aFont,SDL_Color aColor=SDL_Color{0,0,0},bool ahasDialog=true);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set a new message for our text
        *    \param aMessage -> it is the new message that our text will show
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setMessage(const string & aMessage);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will get our current message
        *    \return string -> it is the new message that our text will show
        */
        //////////////////////////////////////////////////////////////////////////
        string getMessage();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set a new position for our text
        *    \param position -> it is the new position that our text
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setPosition(vec3f position);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It Will init our message for its visualization
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void init();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void visualization(Context & vis);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateState(GameState & gameState);

        void setScaleDialog(vec3f value);
        void setScaleText(vec3f value);
    protected:

    private:
        Matrix4f * positionText,* scaleText;
        Matrix4f * positionBack,* scaleBack;
        SDL_Surface * surface;
        bool hasDialog;
        string fileTexture;
        string message;
        GLuint textureText;
        TTF_Font* font;
        SDL_Color color;
        NodeSceneGraph * textNode,* backNode;
};

#endif // TEXT_H

