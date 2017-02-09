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

#include "textevent.h"

TextEvent::TextEvent()
{
    //ctor
}

//**********************************************************************//

TextEvent::TextEvent(const Value & eventFeatures){
    speakerMessage speaker;

    for(unsigned i=0;i<eventFeatures.Size();i++){
        minArea=vec3f(eventFeatures[i]["minPosition"][0].GetFloat(),eventFeatures[i]["minPosition"][1].GetFloat(),eventFeatures[i]["minPosition"][2].GetFloat());
        maxArea=vec3f(eventFeatures[i]["maxPosition"][0].GetFloat(),eventFeatures[i]["maxPosition"][1].GetFloat(),eventFeatures[i]["maxPosition"][2].GetFloat());
        timeBWstate=eventFeatures[i]["timeBWstate"].GetFloat();


        const Value & dialogs=eventFeatures[i]["dialog"];

        for(unsigned j=0;j<dialogs.Size();j++){
            if(dialogs[j]["speaker"].GetInt()==1) speaker=HERO_DIALOG;
            else speaker=MATE_DIALOG;
            stateMachine.addState(std::string(dialogs[j]["string"].GetString()),speaker);
        }
    }

    currentTime=SDL_GetTicks();
}

//**********************************************************************//

TextEvent::~TextEvent()
{
    //dtor
}
