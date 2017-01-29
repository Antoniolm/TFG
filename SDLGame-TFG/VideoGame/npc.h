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

#ifndef NPC_H
#define NPC_H

#include "../GraphicEngine/ianpc.h"
#include "avatar.h"
#include "../GraphicEngine/mesh.h"
#include "../GraphicEngine/meshcollection.h"
#include "../GraphicEngine/text.h"
#include "../GraphicEngine/structdata.h"
#include "../GraphicEngine/scriptlmd.h"
#include <SDL_TTF.h>

class Text;
class Npc : public Avatar
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Npc();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters*/
        //////////////////////////////////////////////////////////////////////////
        Npc(vec3f aPosition);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Npc();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will add a new dialog in our avatar
        *    \param state -> the new element of our vector
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void addDialog(const string state,speakerMessage speaker);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will show the current dialog of our avatar
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void currentDialog();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will pass for the next dialog of our avatar
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void nextDialog();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void visualization(Context & cv);

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
        *    It will activate our npc
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activateNpc(bool value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return if the avatar is activate or not.
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool getActivate();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the speaker of the current message
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        speakerMessage getSpeaker();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the string of the current message
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        string & getMessage();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the position of our avatar
        *    \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getPosition();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will check if that npc is in the first state.
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isInitialState();


    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will initialize the animation of our npc
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void initAnimation();
        IANpc stateMachine;
        Text * currentText;
        ScriptLMD animation;
        vector<Matrix4f *> moveMatrix;
        bool npcActivate;
};

#endif // NPC_H
