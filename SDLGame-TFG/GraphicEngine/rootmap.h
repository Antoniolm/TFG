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
#include "particlesystem.h"
#include "particle.h"
#include "mesh.h"
#include "objectscene.h"
#include "../VideoGame/hero.h"
#include "../VideoGame/npc.h"
#include "../VideoGame/enemy.h"
#include "../VideoGame/coin.h"
#include "../VideoGame/projectilesystem.h"
#include "meshcollection.h"
#include "materialcollection.h"
#include "../lib/rapidjson/document.h"
#include "decorationobject.h"
#include "voxel.h"
#include "voxelgroup.h"
#include "sound.h"

using namespace std;

class Hero;
class Npc;
class Enemy;
class Coin;
class NpcList;
class EnemyList;
class CoinList;
class ParticleSystem;
class ProjectileSystem;
class RootMap : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        RootMap();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters*/
        //////////////////////////////////////////////////////////////////////////
        RootMap(const rapidjson::Document & document,Shader & shader);

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
        void updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will enable the sound of our rootmap.That will use when the game
        *    will be pause.
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void enableSound(bool value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        ObjectScene * collision(const vec3f & indexObj);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will set the hero to our map
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setHero(Hero * theHero);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will return the hero of our game
        *    \return hero *
        */
        //////////////////////////////////////////////////////////////////////////
        Hero * getHero();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will return the enemyList of our map
        *    \return EnemyList *
        */
        //////////////////////////////////////////////////////////////////////////
        EnemyList * getEnemyList();
    protected:

    private:
        vector<int> indexMap[100][100];
        vector<ObjectScene *> objs;
        vector<ObjectScene *> decorationObjs;
        vector<ParticleSystem *> particleSystem;
        vector<ProjectileSystem *> projectileSystem;
        ObjectScene * background;
        NpcList * npcList;
        EnemyList * enemyList;
        CoinList *coinList;
        Sound * backSound;
        Hero * hero;
};

#endif // ROOTMAP_H
