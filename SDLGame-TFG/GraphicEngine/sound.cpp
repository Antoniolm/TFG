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

sound::sound(const string & aFile,unsigned int aType){
    file=aFile;
    type=aType;

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
    if(type==0 && Mix_PlayingMusic()==0)
        Mix_PlayMusic(music, -1);

    else if(type==1)
        Mix_PlayChannel(0,effect,0);
}

//**********************************************************************//

void sound::stop(){
    if(type==0 && Mix_PlayingMusic()==1){
        Mix_HaltMusic();
    }
    else if(type==1){
        Mix_HaltChannel(0);
    }
}

//**********************************************************************//

void sound::pause(){
    if(type==0 && Mix_PausedMusic()==0)
        Mix_PauseMusic();
    else if(type==1){
        Mix_Pause(0);
    }
}

//**********************************************************************//

void sound::resume(){
    if(type==0 && Mix_PausedMusic()==1)
        Mix_ResumeMusic();
    else if(type==1){
        Mix_Resume(0);
    }
}

//**********************************************************************//

bool sound::isPlaying(){
    return true;
}

//**********************************************************************//

bool sound::isPause(){
    return true;
}

//**********************************************************************//

bool sound::loadSound(const string & aFile,unsigned int aType){
    file=aFile;
    type=aType;

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
