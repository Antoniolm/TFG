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

#ifndef TEXTEVENT_H
#define TEXTEVENT_H

#include "structdata.h"
#include "SDL.h"
#include "ianpc.h"
#include "rootmap.h"
#include "../lib/rapidjson/document.h"

using namespace rapidjson;

class TextEvent
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /**Json constructor */
        //////////////////////////////////////////////////////////////////////////
        TextEvent(const Value & eventFeatures);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~TextEvent();

        /////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateState(float time,RootMap * rootMap);
    protected:

    private:
        vec3f minArea;
        vec3f maxArea;
        IANpc stateMachine;
        float timeBWstate;
        float currentTime,textDelay;
        bool activated;
};

#endif // TEXTEVENT_H
