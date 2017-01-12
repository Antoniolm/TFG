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
#include "../GraphicEngine/linearmovement.h"

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
        bool gravity(float time);


        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will jump our avatar
        *    \param velocity ->
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activeJump(vec3f velocity,vec3f acceleration);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will jump our avatar
        *    \param time ->
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        bool jump(float time);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the position of our avatar
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getPosition();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the direction of our avatar
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        avatarDirection getDirection();

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
        virtual void updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap);

        bool detectHit(vec3f posAvatar,avatarDirection dirAvatar);
        void activeImpact(avatarDirection dirAvatar);
        void impactMove(float time);

    protected:
        RootMap * currentMap;
        Matrix4f * moveAvatar;
        avatarDirection direction;
        AcceleratedMovement * acceleratedMove;
        vec3f impactMovement;
        bool isMoving,isFalling,isJumping,isMoveCollision,isHitting,isImpacted,isShielded;
        float currentTime,dmgDelay,impactTime;
    private:
};

#endif // AVATARMOVE_H
