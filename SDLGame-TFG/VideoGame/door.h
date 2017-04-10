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

#ifndef DOOR_H
#define DOOR_H

#include "../GraphicEngine/objectscene.h"
#include "../GraphicEngine/nodescenegraph.h"
#include "../GraphicEngine/matrix4f.h"
#include "../GraphicEngine/matrix4fdynamic.h"
#include "../GraphicEngine/scriptlmd.h"
#include "../GraphicEngine/meshcollection.h"
#include "../GraphicEngine/materialcollection.h"
#include "soulcarrier.h"
#include "../lib/rapidjson/document.h"

using namespace rapidjson;

enum doorDirection{
    dForward,
    dSideWays
};



class SoulCarrier;
class Door : public ObjectScene
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    Constructor
        *    @param doorFeatures -> the value json that contain all the information of our door object
        *    @param soulCarriers -> Vector of soulcarriers
        *    @param ID -> ID of the soulCarrier linked to our door
        */
        //////////////////////////////////////////////////////////////////////////
        Door(const Value & doorFeatures,const vector<SoulCarrier*> & soulCarriers,int ID);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Door();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    @param cv -> the context of our visualization
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void visualization(Context & cv);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    @param gameState -> the current state of our game
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void updateState(GameState & gameState);
    protected:

    private:
        void initAnimation();
        SoulCarrier * sCarrier;
        Matrix4f * rotateDoor,* moveDoor;
        ScriptLMD * animation;
        bool activated;
        int doorType;
        int doorID;
};

#endif // DOOR_H
