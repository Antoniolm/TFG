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

#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include "context.h"
#include "object3d.h"
#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl/glu.h>
#include <gl/gl.h>
#include <fstream>
#include "matrix4f.h"
#include <iostream>
#include "structdata.h"
#include "shader.h"
#include <file_ply_stl.hpp>

using namespace std;

class Mesh : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Default constructor */
        //////////////////////////////////////////////////////////////////////////
        Mesh();

        //////////////////////////////////////////////////////////////////////////
        /**  Copy constructor */
        /////////////////////////////////////////////////////////////////////////
        Mesh(const Mesh & aMesh);

        //////////////////////////////////////////////////////////////////////////
        /**  Constructor */
        /////////////////////////////////////////////////////////////////////////
        Mesh(const string & aTextur,unsigned char aType);

        //////////////////////////////////////////////////////////////////////////
        /**  Constructor */
        /////////////////////////////////////////////////////////////////////////
        Mesh(const string & aFile);

        //////////////////////////////////////////////////////////////////////////
        /** Default destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Mesh();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will initialize the information for the visualization
        *    \return void
        */
        /////////////////////////////////////////////////////////////////////////
        void init();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        /////////////////////////////////////////////////////////////////////////
        virtual void visualization(Context & vis);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void updateState(float time);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will clean the object
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void clean();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will load the files(vexterShader,FragmentShader) and it
        *    links the shaders to a program too.
        *    \return bool true -> Shaders load successfully
        *                 false-> Shaders don't load successfully
        */
        //////////////////////////////////////////////////////////////////////////
        bool LoadShader(const string & vertexShader,const string & FragmentShader);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will return the position
        *    \return vec3f with the position of our object
        */
        //////////////////////////////////////////////////////////////////////////
        vec4f getPosition();

    protected:

    private:
        vector<vec3i> triangles;
        vector<vec3f> vertex;
        Matrix4f transformation;
        unsigned char type;
        GLuint vertexbuffer;
        GLuint trianglebuffer;
        Shader shaders;
        string texture;
};

#endif // MESH_H
