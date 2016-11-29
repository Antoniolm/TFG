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

#ifndef AVATARMOVE_H
#define AVATARMOVE_H

#include "avatar.h"
#include "../GraphicEngine/matrix4f.h"
#include "../GraphicEngine/acceleratedmovement.h"

class RootMap;
class AvatarMove: public Avatar
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        AvatarMove();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~AvatarMove();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will move our avatar
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        bool moveBody(vec3f aMove,avatarDirection aDir);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will create the gravity for our avatar
        *    \param velocity ->
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        bool gravity(float velocity);


        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will jump our avatar
        *    \param velocity ->
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activeJump(float velocity,float acceleration);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will jump our avatar
        *    \param velocity ->
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        bool jump();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will return if the avatar is jumping or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isJump();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will return if the avatar is falling or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isFall();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the position of our avatar
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getPosition();

    protected:
        RootMap * rootMap;
        Matrix4f * moveAvatar;
        avatarDirection direction;
        AcceleratedMovement * acceleratedMove;
        bool isMoving,isFalling,isJumping;
        float currentTime;
    private:
};

#endif // AVATARMOVE_H
