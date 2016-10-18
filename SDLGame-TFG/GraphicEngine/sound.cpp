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

#include "sound.h"

sound::sound()
{

    file="";
}

//**********************************************************************//

sound::~sound()
{
    Mix_FreeMusic(music);
    music=NULL;
}

//**********************************************************************//

sound::sound(const sound & aSound){

}

//**********************************************************************//

sound::sound(const string & aFile,unsigned int aType,int aChannel,int aloop){
    file=aFile;
    type=aType;
    channel=aChannel;
    loop=aloop;

    switch(type){
        case 0:
            music= Mix_LoadMUS(&file[0u]);
            if( music == NULL ) cout<< "Unable to load the background music ->"<< file<<endl;
        break;

        case 1:
            effect= Mix_LoadWAV(&file[0u]);
            if( effect == NULL) cout<< "Unable to load the effect ->"<< file<<endl;
        break;
    }
}

//**********************************************************************//

void sound::play(){

    switch(type){
        case 0:
            if(Mix_PlayingMusic()==0)
                Mix_PlayMusic(music, -1);
        break;

        case 1:
            if(Mix_Playing(channel)==0)
                Mix_PlayChannel(channel,effect,0);

        break;
    }
}

//**********************************************************************//

void sound::stop(){
    switch(type){
        case 0:
            if(Mix_PlayingMusic()==1)
                Mix_HaltMusic();
        break;

        case 1:
            if(Mix_Playing(channel)==1)
                Mix_HaltChannel(channel);

        break;
    }
}

//**********************************************************************//

void sound::pause(){
    switch(type){
        case 0:
            if(Mix_PausedMusic()==0)
                Mix_PauseMusic();
        break;

        case 1:
            if(Mix_Paused(channel)==0)
                Mix_Pause(channel);

        break;
    }
}

//**********************************************************************//

void sound::resume(){
    switch(type){
        case 0:
            if(Mix_PausedMusic()==1)
                Mix_ResumeMusic();
        break;

        case 1:
            if(Mix_Paused(channel)==1)
                Mix_Resume(channel);

        break;
    }

}

//**********************************************************************//

bool sound::isPlaying(){
    bool result=false;
    switch(type){
        case 0:
            if(Mix_PlayingMusic()==1)
                result=true;
        break;

        case 1:
            if(Mix_Playing(channel)==1)
                result=true;
        break;
    }

    return result;
}

//**********************************************************************//

bool sound::isPause(){
    bool result=false;

    switch(type){
        case 0:
            if(Mix_PausedMusic()==1)
                result=true;
        break;

        case 1:
            if(Mix_Paused(channel)==1)
                result=true;

        break;
    }
    return result;
}

//**********************************************************************//

bool sound::loadSound(const string & aFile,unsigned int aType,int aChannel,int aloop){
    file=aFile;
    type=aType;
    channel=aChannel;
    loop=aloop;

    bool result = true;

    switch(type){
        case 0:
        music= Mix_LoadMUS(&file[0u]);
        if( music == NULL ){
          cout<< "Unable to load the background music ->"<< file<<endl;
          result=false;
        }
        break;

        case 1:
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

string & sound::getFile(){
    return file;
}
