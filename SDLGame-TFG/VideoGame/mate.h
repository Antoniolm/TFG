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

#ifndef MATE_H
#define MATE_H

#include "../GraphicEngine/object3d.h"
#include "../GraphicEngine/nodescenegraph.h"
#include "../GraphicEngine/material.h"
#include "../GraphicEngine/matrix4f.h"
#include "../GraphicEngine/matrix4fdynamic.h"
#include "../GraphicEngine/meshcollection.h"
#include "../GraphicEngine/soundcollection.h"
#include "../GraphicEngine/axisrotation.h"
#include "../GraphicEngine/sound.h"
#include "../GraphicEngine/text.h"
#include "../GraphicEngine/animationlist.h"
#include "avatar.h"

class Mate : public Avatar
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Mate(vec3f aPosition);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Mate();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void visualization(Context & cv);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void updateState(GameState & gameState);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set a new message for our text
        *    \param message -> it is the new message that our text will show
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setDialog(string message);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will activate the text of our hero
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activateDialog(bool value);

    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will initialize the animation of our mate
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void initAnimation();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will give to our mate his next direction and position
        *    \return pair<avatarDirection,vec3f>
        */
        //////////////////////////////////////////////////////////////////////////
        pair<avatarDirection,vec3f> nextPosition(vec3f posHero);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will move our mate
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void moveMate(float time,vec3f aMove,avatarDirection aDir);

        vector<Matrix4f *> moveMatrix;
        pair<avatarDirection,vec3f> currentMove;
        Matrix4f * moveAvatar;
        avatarDirection direction;
        ScriptLMD * animation;
        Text * currentText;
        bool textActivated;
};

#endif // MATE_H
