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

#ifndef MESHMATERIAL_H
#define MESHMATERIAL_H

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
#include "rootmap.h"
#include "shader.h"
#include <file_ply_stl.hpp>
#include <file_obj.h>
//#include <../lib/glm/glm.hpp>

struct Vertex {
    vec3f position;
    vec3f normal;
    vec2f textCoord;
    Vertex(vec3f pos,vec3f norm,vec2f tCoord){
        position=pos;
        normal=norm;
        textCoord=tCoord;
    }
};

using namespace std;

class MeshMaterial : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        MeshMaterial();

        //////////////////////////////////////////////////////////////////////////
        /**  Constructor */
        /////////////////////////////////////////////////////////////////////////
        MeshMaterial(const string & aFile,vec3f aColor=vec3f(1.0,0.5,0.5));

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~MeshMaterial();

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
        *    The method will load the files(vexterShader,FragmentShader) and it
        *    links the shaders to a program too.
        *    \return bool true -> Shaders load successfully
        *                 false-> Shaders don't load successfully
        */
        //////////////////////////////////////////////////////////////////////////
        bool LoadShader(const string & vertexShader,const string & FragmentShader);

    protected:

    private:
        vector<GLushort> triangles;
        vector<float> vertex;
        vector<Vertex> vertexAndNormal;
        vector<float> normals;
        vector<int> normalFaces;
        vector<float> textureCord;
        vector<int> textureFaces;
        vec3f color;
        Matrix4f * transformation;
        GLuint vertexbuffer;
        Shader shaders;
        GLuint trianglebuffer;
};

#endif // MESHMATERIAL_H
