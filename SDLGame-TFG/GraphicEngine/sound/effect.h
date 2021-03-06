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

#ifndef EFFECT_H
#define EFFECT_H

#include "sound.h"
#include <unistd.h>


#define MAX_CHANNEl 16
using namespace std;
class Effect : public Sound
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Effect();

        //////////////////////////////////////////////////////////////////////////
        /**  Copy constructor */
        //////////////////////////////////////////////////////////////////////////
        Effect(const Effect & aSound);

        //////////////////////////////////////////////////////////////////////////
        /**  Constructor with some parameters
        *    \param aFile -> string with the name of a file.
        *    \param aType -> int with the type of element(music or effect)
        */
        //////////////////////////////////////////////////////////////////////////
        Effect(const string & aFile,int aVolume=128,int aChannel=-1, int aloop=-1);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Effect();

        /////////////////////////////////////////////////////////////////////////
        /**
        *    The method will load the sound file
        *    \param aFile -> string with the name of a file.
        *    \param aType -> int with the type of element(music or effect)
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        bool loadSound(const string & aFile,int aVolume=128 ,int aChannel=-1, int aloop=-1);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will play the loaded sound and return the channel
        *    where is played
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int play(float distance=0);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will stop the loaded sound
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void stop(int currentChannel=-1);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will pause the loaded sound.
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void pause(int currentChannel=-1);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will resume the loaded sound
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void resume(int currentChannel=-1);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show if the sound is playing or not
        *    \return bool true-> The sound is playing
        *                 false-> The sound is not playing
        */
        //////////////////////////////////////////////////////////////////////////
        bool isPlaying(int currentChannel=-1);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show if the sound is paused or not
        *    \return bool true-> The sound is paused
        *                 false-> The sound is not paused
        */
        //////////////////////////////////////////////////////////////////////////
        bool isPause(int currentChannel=-1);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the name of sound file
        *    \return string
        */
        //////////////////////////////////////////////////////////////////////////
        string & getFile();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the volume of our sound according to the distance
        *    between the hero and the object that will produce the sound
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateVolume(int currentChannel,float distance);

    protected:

    private:
        Mix_Chunk * effect; // Effect object
};

#endif // EFFECT_H
