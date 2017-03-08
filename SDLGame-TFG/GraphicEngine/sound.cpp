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

int Sound::play(float distance){
    int currentChannel=channel;
    switch(type){
        case 0: //Background music
            if(Mix_PlayingMusic()==0){
                Mix_PlayMusic(music, loop);
                Mix_VolumeMusic(volume);
            }
        break;

        case 1: //Effect
            if(channel!=-1){ //if have a channel
                Mix_PlayChannel(channel,effect,loop);
                Mix_Volume(channel,volume);
            }
            else{ //if sound has channel -1 ->take the first free channel
                currentChannel=Mix_PlayChannel(-1,effect,loop);
                Mix_Volume(currentChannel,calculateVolume(distance));
            }

        break;
    }
    return currentChannel;
}

//**********************************************************************//

void Sound::stop(int currentChannel){
    switch(type){
        case 0: //Background music
            if(Mix_PlayingMusic()==1)
                Mix_HaltMusic();
        break;

        case 1: //Effect
            if(channel!=-1 && Mix_Playing(channel)==1){
                Mix_HaltChannel(channel);
            }
            else if(channel==-1 && currentChannel!=-1)
                Mix_HaltChannel(currentChannel);

        break;
    }
}

//**********************************************************************//

void Sound::pause(int currentChannel){
    switch(type){
        case 0: //Background music
            if(Mix_PausedMusic()==0)
                Mix_PauseMusic();
        break;

        case 1: //Effect
            if(channel!=-1 && Mix_Paused(channel)==0){
                Mix_Pause(channel);
            }
            else if(channel==-1 && currentChannel!=-1)
                    Mix_Pause(currentChannel);

        break;
    }
}

//**********************************************************************//

void Sound::resume(int currentChannel){
    switch(type){
        case 0: //Background music
            if(Mix_PausedMusic()==1)
                Mix_ResumeMusic();
        break;

        case 1: //Effect
            if(channel!=-1 && Mix_Paused(channel)==1){
                Mix_Resume(channel);
            }
            else if(channel==-1 && currentChannel!=-1)
                Mix_Resume(currentChannel);

        break;
    }

}

//**********************************************************************//

bool Sound::isPlaying(int currentChannel){
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
            else if(channel==-1 && currentChannel!=-1){
                if(Mix_Playing(currentChannel)==1)
                    result=true;
            }

        break;
    }

    return result;
}

//**********************************************************************//

bool Sound::isPause(int currentChannel){
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
            else if(channel==-1 && currentChannel!=-1){
                if(Mix_Paused(currentChannel)==1)
                    result=true;
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

//**********************************************************************//

void Sound::updateVolume(int currentChannel,float distance){
    if(type==1 && currentChannel!=-1){
        Mix_Volume(currentChannel,calculateVolume(distance));
    }
}


//**********************************************************************//
//                              PRIVATE                                 //
//**********************************************************************//

int Sound::calculateVolume(float distance){
    int currentVolumen;
    float distFactor=0.0;

    if(distance>=10.0) //if is far of 10 is not sound
        currentVolumen=0;
    else if(distance <=3.0) //if is near of 3 is 100% sound
        currentVolumen=volume;
    else{ //if is between 3 and 10 is a x% sound
        distFactor=1.0-((distance-3.0)/7.0);
        currentVolumen=volume*distFactor;
    }

    return currentVolumen;
}
