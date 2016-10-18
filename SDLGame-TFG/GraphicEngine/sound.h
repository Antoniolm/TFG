// *********************************************************************
// **
// ** Copyright (C) 2016 Antonio David López Machado
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
        /** Default constructor */
        sound();

        sound(const sound & aSound);
        sound(const string & aFile,unsigned int aType);

        /** Default destructor */
        virtual ~sound();

        bool loadSound(const string & aFile,unsigned int aType);
        void play();
        void stop();
        void pause();
        void resume();
        bool isPlaying();
        bool isPause();
        unsigned int getType();
        string & getFile();

    protected:

    private:
        unsigned int type;   //0=background music, 1=effect

        union{
            Mix_Music * music;
            Mix_Chunk * effect;
        };

        string file;
};

#endif // SOUND_H
