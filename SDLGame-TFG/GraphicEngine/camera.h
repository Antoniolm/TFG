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

#ifndef CAMERA_H
#define CAMERA_H

#include "matrix/structdata.h"
#include "matrix/matrix4f.h"
#include "context/shader.h"
#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "controller/controllermanager.h"
#include "gamestate.h"

class RootMap;
class Camera
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Camera();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Constructor with parameters
        *   \param eye -> Position of the camera
        *   \param Target -> Target of the camera
        *   \param up -> The inclination of the camera
        */
        //////////////////////////////////////////////////////////////////////////
        Camera(vec3f eye,vec3f aTarget,vec3f aUp);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Camera();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Set the value of some parameters in the object
        *   \param eye -> Position of the camera
        *   \param Target -> Target of the camera
        *   \param up -> The inclination of the camera
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setCamera(vec3f eye,vec3f aTarget,vec3f aUp);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Set the value for the projection
        *   \param fov
        *   \param aspect
        *   \param near
        *   \param far
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setPerspectiveProjection(float fov, float aspect, float nearPro, float farPro);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Set the value for the projection
        *   \param left
        *   \param right
        *   \param bottom
        *   \param top
        *   \param near
        *   \param far
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setOrthographicProjection(float left,float right,float bottom,float top,float nearPro = -1.0f,float farPro = 1.0f );

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will create the matrix of the object
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void createCamera();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will activate our camera
        *   @param shaderID -> the id of our current activated shader
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activateCamera(GLuint shaderID);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will activate our current orthographic projection
        *   @param shaderID -> the id of our current activated shader
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activateOrthoProjection(GLuint shaderID);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will activate our current perspective projection
        *   @param shaderID -> the id of our current activated shader
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activatePerspecProjection(GLuint shaderID);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will move the position of our camera
        *   @param gameState -> the current state of our game
        *   @param shaderID -> the id of our current activated shader
        *   @param activateMenu -> if the menu is activated or not
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void update(GameState & gameState,GLuint shaderID,bool activateMenu);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will return our matrix camera
        *   \return Matrix4f
        */
        //////////////////////////////////////////////////////////////////////////
        Matrix4f & getCamera();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will return our camera
        *   \return GLfloat *
        */
        //////////////////////////////////////////////////////////////////////////
        GLfloat * getView();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will return our orthographic projection
        *   \return Matrix4f &
        */
        //////////////////////////////////////////////////////////////////////////
        Matrix4f & getOrthoProyection();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will return our perspective projection
        *   \return Matrix4f &
        */
        //////////////////////////////////////////////////////////////////////////
        Matrix4f & getPersProyection();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will return the position of our camera
        *   \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getPosition();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will return the target of our camera
        *   \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getTarget();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will return the up of our camera
        *   \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getUp();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will return if our camera is in viewMode or not
        *   \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isViewMode();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will set the position and direction of our camera
        *   @param aPosition -> the new position of our camera
        *   @param shaderID -> the id of our current activated shader
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setPosition(vec3f aPosition,GLuint shaderID);

    protected:

    private:
        Matrix4f camera;           // Matrix 4x4 of the camera
        Matrix4f orthoProjection;  // Matrix 4x4 of the orthographic projection
        Matrix4f perspecProjection;// Matrix 4x4 of the perspective projection
        vec3f initialPosition;     // Initial position of the camera
        vec3f position;            // Current position of the camera
        vec3f target;              // Current target of the camera
        vec3f up;                  // Current inclination of the camera
        bool viewMode;             // Flag of the view mode
        float currentTime;         // Current time of the system
        float viewDelay;           // Delay in our view mode
};

#endif // CAMERA_H
