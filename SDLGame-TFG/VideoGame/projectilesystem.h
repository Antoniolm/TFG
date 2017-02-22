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

#ifndef PROJECTILESYSTEM_H
#define PROJECTILESYSTEM_H

#include "projectile.h"
#include "../GraphicEngine/nodescenegraph.h"
#include <string>
#include "../GraphicEngine/nodescenegraph.h"
#include "../GraphicEngine/rootmap.h"
#include <list>
#include "../lib/rapidjson/document.h"


class Projectile;
class ProjectileSystem : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        ProjectileSystem(vec3f aRadio,vec3f aPos,vec3f aVeloc,int aDir,float aDelay,string aMesh,string aMaterial);

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with json*/
        //////////////////////////////////////////////////////////////////////////
        ProjectileSystem(const rapidjson::Value & projectileSys);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~ProjectileSystem();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void visualization(Context & cv);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateState(GameState & gameState);

    protected:

    private:
        list<Projectile *> projectiles;
        vec3f radioActivity,position,velocity;
        avatarDirection direction;
        float projectileDelay; //time delay
        float timeBWprojectile;//time between one projectile and another
        string mesh,material;
};

#endif // PROJECTILESYSTEM_H
