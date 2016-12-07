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
#include "rootmap.h"
#include "shader.h"
#include <file_ply_stl.hpp>
#include <file_obj.h>

using namespace std;

enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	INDEX_VB
};

class Mesh : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Mesh();

        //////////////////////////////////////////////////////////////////////////
        /**  Constructor */
        /////////////////////////////////////////////////////////////////////////
        Mesh(const string & aFile);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
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
        void visualization(Context & vis);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will obtain the boundingBox of the object.
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        BoundingBox getBoundingBox();


    protected:

    private:
        void generateBoundingBox(vector<vec3f> & vertex);
        static const unsigned int NUM_BUFFERS = 4;
        GLuint vertexArrayBuffers[NUM_BUFFERS];
        GLuint vertexArrayObject;
        string objFile;
        int numIndex;
};

#endif // MESH_H
