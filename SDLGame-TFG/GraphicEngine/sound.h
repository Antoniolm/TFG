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

#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>
#include <string>
#include <iostream>
#include <unistd.h>

using namespace std;

class sound
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        sound();

        //////////////////////////////////////////////////////////////////////////
        /**  Copy constructor */
        //////////////////////////////////////////////////////////////////////////
        sound(const sound & aSound);

        //////////////////////////////////////////////////////////////////////////
        /**  Constructor with some parameters
        *    \param aFile -> string with the name of a file.
        *    \param aType -> int with the type of element(music or effect)
        */
        //////////////////////////////////////////////////////////////////////////
        sound(const string & aFile,unsigned int aType,int aChannel=-1, int aloop=-1);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~sound();

        /////////////////////////////////////////////////////////////////////////
        /**
        *    The method will load the sound file
        *    \param aFile -> string with the name of a file.
        *    \param aType -> int with the type of element(music or effect)
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        bool loadSound(const string & aFile,unsigned int aType, int aChannel=-1, int aloop=-1);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will play the loaded sound
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void play();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will stop the loaded sound
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void stop();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will pause the loaded sound.
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void pause();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will resume the loaded sound
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void resume();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show if the sound is playing or not
        *    \return bool true-> The sound is playing
        *                 false-> The sound is not playing
        */
        //////////////////////////////////////////////////////////////////////////
        bool isPlaying();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show if the sound is paused or not
        *    \return bool true-> The sound is paused
        *                 false-> The sound is not paused
        */
        //////////////////////////////////////////////////////////////////////////
        bool isPause();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the type of sound that the object has.
        *    \return unsigned int
        */
        //////////////////////////////////////////////////////////////////////////
        unsigned int getType();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the name of sound file
        *    \return string
        */
        //////////////////////////////////////////////////////////////////////////
        string & getFile();

    protected:

    private:
        unsigned int type;   //0=background music, 1=effect
        int channel; //Variable for effect
        int loop; //Variable for all type of sound. -> Number of loop in a reproduction
        union{
            Mix_Music * music;
            Mix_Chunk * effect;
        };

        string file;
};

#endif // SOUND_H
