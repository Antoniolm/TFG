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

#include "sound.h"

Sound::Sound()
{
    file="";
}

//**********************************************************************//

Sound::~Sound()
{
    Mix_FreeMusic(music);
    music=NULL;
}

//**********************************************************************//

Sound::Sound(const Sound & aSound){
    file=aSound.file;
    type=aSound.type;
    channel=aSound.channel;
    loop=aSound.loop;
    volume=aSound.volume;

    switch(type){
        case 0: //Background music
            music= Mix_LoadMUS(&file[0u]);
            if( music == NULL ) cout<< "Unable to load the background music ->"<< file<<endl;
        break;

        case 1: //Effect
            effect= Mix_LoadWAV(&file[0u]);
            if( effect == NULL) cout<< "Unable to load the effect ->"<< file<<endl;
        break;
    }
}

//**********************************************************************//

Sound::Sound(const string & aFile,unsigned int aType,int aVolume,int aChannel,int aloop){
    file=aFile;
    type=aType;
    channel=aChannel;
    loop=aloop;
    volume=aVolume;

    switch(type){
        case 0: //Background music
            music= Mix_LoadMUS(&file[0u]);
            if( music == NULL ) cout<< "Unable to load the background music ->"<< file<<endl;
        break;

        case 1: //Effect
            effect= Mix_LoadWAV(&file[0u]);
            if( effect == NULL) cout<< "Unable to load the effect ->"<< file<<endl;
        break;
    }
}

//**********************************************************************//

void Sound::play(){

    switch(type){
        case 0: //Background music
            if(Mix_PlayingMusic()==0){
                Mix_PlayMusic(music, loop);
                Mix_VolumeMusic(volume);
            }
        break;

        case 1: //Effect
            if(Mix_Playing(channel)==0){
                Mix_PlayChannel(channel,effect,loop);
                Mix_Volume(channel,volume);
            }

        break;
    }
}

//**********************************************************************//

void Sound::stop(){
    switch(type){
        case 0: //Background music
            if(Mix_PlayingMusic()==1)
                Mix_HaltMusic();
        break;

        case 1: //Effect
            if(Mix_Playing(channel)==1)
                Mix_HaltChannel(channel);

        break;
    }
}

//**********************************************************************//

void Sound::pause(){
    switch(type){
        case 0: //Background music
            if(Mix_PausedMusic()==0)
                Mix_PauseMusic();
        break;

        case 1: //Effect
            if(Mix_Paused(channel)==0)
                Mix_Pause(channel);

        break;
    }
}

//**********************************************************************//

void Sound::resume(){
    switch(type){
        case 0: //Background music
            if(Mix_PausedMusic()==1)
                Mix_ResumeMusic();
        break;

        case 1: //Effect
            if(Mix_Paused(channel)==1)
                Mix_Resume(channel);

        break;
    }

}

//**********************************************************************//

bool Sound::isPlaying(){
    bool result=false;
    switch(type){
        case 0: //Background music
            if(Mix_PlayingMusic()==1)
                result=true;
        break;

        case 1: //Effect
            if(Mix_Playing(channel)==1)
                result=true;
        break;
    }

    return result;
}

//**********************************************************************//

bool Sound::isPause(){
    bool result=false;

    switch(type){
        case 0: //Background music
            if(Mix_PausedMusic()==1)
                result=true;
        break;

        case 1: //Effect
            if(Mix_Paused(channel)==1)
                result=true;

        break;
    }
    return result;
}

//**********************************************************************//

bool Sound::loadSound(const string & aFile,unsigned int aType,int aVolume,int aChannel,int aloop){
    file=aFile;
    type=aType;
    channel=aChannel;
    loop=aloop;
    volume=aVolume;

    bool result = true;

    switch(type){
        case 0: //Background music
        music= Mix_LoadMUS(&file[0u]);
        if( music == NULL ){
          cout<< "Unable to load the background music ->"<< file<<endl;
          result=false;
        }
        break;

        case 1: //Effect
        effect= Mix_LoadWAV(&file[0u]);
        if( effect == NULL){
          cout<< "Unable to load the effect ->"<< file<<endl;
          result=false;
        }
        break;
    }

    return result;
}

//**********************************************************************//

string & Sound::getFile(){
    return file;
}
