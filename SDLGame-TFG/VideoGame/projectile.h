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

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "avatar.h"
#include "avatarmove.h"
#include "../GraphicEngine/mesh.h"
#include "../GraphicEngine/material.h"
#include "../GraphicEngine/meshcollection.h"
#include "../GraphicEngine/materialcollection.h"
#include "../GraphicEngine/soundcollection.h"
#include "../GraphicEngine/scriptlmd.h"
#include "../GraphicEngine/context.h"
#include "../GraphicEngine/matrixscript.h"
#include "../GraphicEngine/rootmap.h"
#include "../GraphicEngine/matrix4f.h"
#include "../GraphicEngine/objectscene.h"
#include "../GraphicEngine/sound.h"
#include "../GraphicEngine/text.h"
#include "enemy.h"
#include "enemylist.h"

#include <vector>


using namespace std;
class RootMap;
class Mesh;
class Material;
class Projectile : public AvatarMove
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Projectile(vec3f aPosition,vec3f aVelocity,avatarDirection aDir,float aDamage,string mesh,string material);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Projectile();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our scene
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
        void updateState(float time,Controller * controller,RootMap * rootMap );

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return if the projectile is live or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isLive();
    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will calculate the head of our projectile because this is needed this position
        *    to check the hits
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void calculateHead();

        Sound * soundHit;
        vec3f velocity,projectileHead;
        bool live;
        float damage;
        Matrix4f * animationMatrix;
        AxisRotation * rotation;

};

#endif // PROJECTILE_H
