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

#ifndef AVATAR_H
#define AVATAR_H

#include "../GraphicEngine/object3d.h"
#include "../GraphicEngine/context.h"
#include "../GraphicEngine/nodescenegraph.h"

enum avatarDirection
{
	FORWARD,       //0
	FOR_LEFTWARD,  //1
	LEFTWARD,      //2
	BACK_LEFTWARD, //3
	BACKWARD,      //4
	BACK_RIGHTWARD,//5
	RIGHTWARD,     //6
	FOR_RIGHTWARD  //7
};

class Avatar: public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Avatar();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Avatar();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void visualization(Context & vis);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap );

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will set the life of an avatar
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setLife(float aLife);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the life of an avatar
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getLite();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will add the value to our life
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void addLife(float value);

    protected:
        NodeSceneGraph * root;
        float life;
    private:

};

#endif // AVATAR_H
