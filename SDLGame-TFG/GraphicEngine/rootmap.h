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

#ifndef ROOTMAP_H
#define ROOTMAP_H

#include "object3d.h"
#include "nodescenegraph.h"
#include <list>
#include <vector>
#include <map>
#include "directionallight.h"
#include "pointlight.h"
#include "matrix/matrix4f.h"
#include "matrix/matrix4fdynamic.h"
#include "matrix/linearmovement.h"
#include "matrix/axisrotation.h"
#include "matrix/matrixstatic.h"
#include "matrix/oscillaterotation.h"
#include "particlesystem.h"
#include "particle.h"
#include "mesh.h"
#include "objectscene.h"
#include "../VideoGame/hero.h"
#include "../VideoGame/mate.h"
#include "../VideoGame/npc.h"
#include "../VideoGame/enemy.h"
#include "../VideoGame/projectilesystem.h"
#include "../VideoGame/soul.h"
#include "../VideoGame/soulcarrier.h"
#include "../VideoGame/door.h"
#include "collection/meshcollection.h"
#include "collection/materialcollection.h"
#include "../lib/rapidjson/document.h"
#include "../lib/rapidjson/stringbuffer.h"
#include "../lib/rapidjson/filereadstream.h"
#include "decorationobject.h"
#include "voxel.h"
#include "voxelgroup.h"
#include "sound.h"
#include "music.h"
#include "controller/controller.h"
#include "controller/keyboardcontroller.h"
#include "textregion.h"
#include "endmapregion.h"
#include "notification.h"
#include "loaderthread.h"
#include "menu/moviescreen.h"
#include "../VideoGame/spiketrap.h"

using namespace std;

class Hero;
class Mate;
class Npc;
class Enemy;
class EnemyList;
class ItemList;
class ParticleSystem;
class ProjectileSystem;
class Soul;
class SoulCarrier;
class Door;
class ObjectGroup;
class TextRegion;
class EndMapRegion;
class Notification;
class SpikeTrap;
class LoaderThread;
class MovieScreen;
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
        RootMap(string fileMap,bool flagThread=false);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~RootMap();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will initialize our rootMap
        *    \return void
        */
        /////////////////////////////////////////////////////////////////////////
        void initialize(string fileMap);

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
        void updateState(GameState & gameState);

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
        *    The method will check if the position (indexObj) is collision with
        *    a objectScene
        *    \return ObjectScene *
        */
        //////////////////////////////////////////////////////////////////////////
        ObjectScene * collision(const vec3f & indexObj);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will check if between the position first and position seoncd there is collision with
        *    a objectScene
        *    \return ObjectScene *
        */
        //////////////////////////////////////////////////////////////////////////
        ObjectScene * collision(const vec3f & posFirst, const vec3f & posSecond);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will remove the collision of an object
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void removeCollision(vec2f voxelPosition,int objID);

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
        *    The method will return the mate of our game
        *    \return hero *
        */
        //////////////////////////////////////////////////////////////////////////
        Mate * getMate();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will return the enemyList of our map
        *    \return EnemyList *
        */
        //////////////////////////////////////////////////////////////////////////
        EnemyList * getEnemyList();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will activate the light of our map
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activatedLight(GLuint shaderID);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will activate the objectGroups of our map
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activatedObjectGroup();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will notify is a rootmap is been loading now.
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isLoading();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will notify is our map has been finished
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isFinished();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the file of next map
        *    \return string
        */
        //////////////////////////////////////////////////////////////////////////
        string getNextMap();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the movie of next map
        *    \return MovieScreen
        */
        //////////////////////////////////////////////////////////////////////////
        MovieScreen * getMovie();

    protected:

    private:
        void deleteObject3d(Object3D * obj);
        vector<int> indexMap[500][500];
        vector<ObjectScene *> objs;
        vector<ObjectGroup *> objectGroup;
        vector<ObjectScene *> decorationObjs;
        vector<Npc *> npcList;
        vector<ParticleSystem *> particleSystem;
        vector<ProjectileSystem *> projectileSystem;
        vector<TextRegion *> regions;
        vector<SpikeTrap *> spikes;
        vector<Soul *> souls;
        vector<SoulCarrier *> soulCarriers;
        vector<Door *> doors;
        vector<Light *> lights;
        EndMapRegion * endMapRegion;
        Notification * title;
        ObjectScene * background;
        EnemyList * enemyList;
        ItemList *itemList;
        Sound * backSound;
        Hero * hero;
        Mate * mate;
        MovieScreen * movie;
        string nextMapFile;
        LoaderThread * loader;
        bool loading;
};

#endif // ROOTMAP_H
