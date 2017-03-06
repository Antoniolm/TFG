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

#include "sound.h"

Sound::Sound()
{
    file="";
}

//**********************************************************************//

Sound::~Sound()
{

  switch(type){
        case 0: //Background music
            Mix_FreeMusic(music);
        break;

        case 1: //Effect
            Mix_FreeChunk(effect);
        break;
    }


}

//**********************************************************************//

Sound::Sound(const Sound & aSound){
    file=aSound.file;
    type=aSound.type;
    channel=aSound.channel;
    currentChannel=0;
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
            currentChannel=-1;
            if(channel!=-1){ //if have a channel
                Mix_PlayChannel(channel,effect,loop);
                Mix_Volume(channel,volume);
            }
            else{ //if sound has channel -1 ->take the first free channel
                for(int i=0;i<MAX_CHANNEl && currentChannel==-1;i++){
                    if(Mix_Playing(i)==0){
                        currentChannel=i;
                    }
                }

                Mix_PlayChannel(currentChannel,effect,loop);
                Mix_Volume(currentChannel,volume);
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
            if(channel!=-1 && Mix_Playing(channel)==1){
                Mix_HaltChannel(channel);
            }
            else if(channel==-1){
                for(int i=0;i<MAX_CHANNEl;i++){
                    if(Mix_GetChunk(i)==effect)
                        Mix_HaltChannel(i);
                }
            }

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
            if(channel!=-1 && Mix_Paused(channel)==0){
                Mix_Pause(channel);
            }
            else if(channel==-1){
                for(int i=0;i<MAX_CHANNEl;i++){
                    if(Mix_GetChunk(i)==effect)
                        Mix_Pause(i);
                }
            }

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
            if(channel!=-1 && Mix_Paused(channel)==1){
                Mix_Resume(channel);
            }
            else if(channel==-1){
                for(int i=0;i<MAX_CHANNEl;i++){
                    if(Mix_GetChunk(i)==effect)
                        Mix_Resume(i);
                }
            }

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
            if(channel!=-1 && Mix_Playing(channel)==1){
                result=true;
            }
            else if(channel==-1){
                for(int i=0;i<MAX_CHANNEl;i++){
                    if(Mix_Playing(i)==1 && Mix_GetChunk(i)==effect)
                        result=true;
                }
            }

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
            if(channel!=-1 && Mix_Paused(channel)==1){
                result=true;
            }
            else if(channel==-1){
                for(int i=0;i<MAX_CHANNEl;i++){
                    if(Mix_Paused(channel)==1 && Mix_GetChunk(i)==effect)
                        result=true;
                }
            }
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
