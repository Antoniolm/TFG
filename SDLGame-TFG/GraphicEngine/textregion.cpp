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

#include "textregion.h"

TextRegion::TextRegion(const Value & eventFeatures){
    speakerMessage speaker;

    minArea=vec3f(eventFeatures["minPosition"][0].GetFloat(),eventFeatures["minPosition"][1].GetFloat(),eventFeatures["minPosition"][2].GetFloat());
    maxArea=vec3f(eventFeatures["maxPosition"][0].GetFloat(),eventFeatures["maxPosition"][1].GetFloat(),eventFeatures["maxPosition"][2].GetFloat());
    timeBWstate=eventFeatures["timeBWstate"].GetFloat();


    const Value & dialogs=eventFeatures["dialog"];

    for(unsigned j=0;j<dialogs.Size();j++){
        if(dialogs[j]["speaker"].GetInt()==1) speaker=HERO_DIALOG;
        else speaker=MATE_DIALOG;
        stateMachine.addState(std::string(dialogs[j]["string"].GetString()),speaker);
    }

    activated=false;
    currentTime=SDL_GetTicks();
    textDelay=currentTime;
}

//**********************************************************************//

TextRegion::~TextRegion()
{
    //dtor
}

//**********************************************************************//

void TextRegion::updateState(GameState & gameState){
    RootMap * rootMap=gameState.rootMap;
    float time=gameState.time;

    Hero * hero =rootMap->getHero();
    Mate * mate =rootMap->getMate();
    vec3f position=hero->getPosition();

    if(time-currentTime>200)
        currentTime=time-50;

    if(position>minArea && position<maxArea && !activated)
        activated=true;

    if(activated){

        if(textDelay<(time-timeBWstate)){ //If the time for the current text is finished
            mate->activateDialog(false);
            hero->activateDialog(false,0);

            if(stateMachine.isLastState()) //if the talk is over
                activated=false;
            else{ //if not our speakers obtains his new dialog

                if(stateMachine.getCurrentSpeaker()==HERO_DIALOG){ //Speaker -> hero
                    hero->setDialog(stateMachine.getCurrentState(),0);
                    hero->activateDialog(true,0);
                }
                else{ //Speaker -> Mate
                    mate->setDialog(stateMachine.getCurrentState());
                    mate->activateDialog(true);
                }
                stateMachine.nextState();
            }
            textDelay=time;

        }

    }

    currentTime+=time-currentTime;
}