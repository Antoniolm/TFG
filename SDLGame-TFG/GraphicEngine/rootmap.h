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

#ifndef ROOTMAP_H
#define ROOTMAP_H

#include "object3d.h"
#include "nodescenegraph.h"
#include <list>
#include <vector>
#include <map>
#include "matrix4f.h"
#include "matrix4fdynamic.h"
#include "linearmovement.h"
#include "axisrotation.h"
#include "matrixstatic.h"
#include "oscillaterotation.h"
#include "mesh.h"
#include "objectscene.h"
#include "../VideoGame/hero.h"
#include "../VideoGame/npc.h"
#include "sound.h"

using namespace std;

class Hero;
class Npc;
class RootMap : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        RootMap();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~RootMap();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        /////////////////////////////////////////////////////////////////////////
        void visualization(Context & vis);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateState(float time,const Uint8* currentKeyStates );

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        ObjectScene * collision(const vec3f & indexObj);


        vec3f obtainDistance(vec3f npcPosition,vec3f heroPosition);

        void setHero(Hero * theHero);
    protected:

    private:
        vector<int> indexMap[30][30];
        vector<ObjectScene *> objs;
        vector<ObjectScene *> decorationObjs;
        Sound * backSound;
        Hero * hero;
        vector<Npc* > npcs;
        float dialogTime;
};

#endif // ROOTMAP_H
