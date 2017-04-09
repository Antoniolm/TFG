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

#ifndef ENEMY_H
#define ENEMY_H


#include "avatar.h"
#include "avatarmove.h"
#include "../GraphicEngine/mesh.h"
#include "../GraphicEngine/meshcollection.h"
#include "../GraphicEngine/scriptlmd.h"
#include "../GraphicEngine/animationlist.h"
#include "../GraphicEngine/context.h"
#include "../GraphicEngine/matrixscript.h"
#include "../GraphicEngine/rootmap.h"
#include "../GraphicEngine/matrix4f.h"
#include "../GraphicEngine/acceleratedmovement.h"
#include "../GraphicEngine/sound.h"
#include "../GraphicEngine/text.h"
#include <stdlib.h>

#include <vector>

using namespace std;
class RootMap;
class Text;
class IAEnemy;
class Weapon;
class Enemy: public AvatarMove
{
    public:
        Enemy();
        //////////////////////////////////////////////////////////////////////////
        /** Constructor
        *    @param aLife -> the life that our enemy object will have
        *    @param aPosition -> the initial position of our enemy
        *    @param aRadioActivity -> the radio activity of our enemy
        */
        //////////////////////////////////////////////////////////////////////////
        Enemy(float aLife,vec3f aPosition,vec3f aRadioActivity);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Enemy();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    @param vis -> the context of our visualization
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void visualization(Context & cv);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    @param gameState -> the current state of our game
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateState(GameState & gameState);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will activated our enemy
        *    @param value -> The value said if the enemy is activated or not
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activatedEnemy(bool value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return if the enemy is activate or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isActivate();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will set radioActivity of our enemy
        *    @param radio -> The new radio value of our enemy
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setRadioActivity(vec3f radio);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get radioActivity of our enemy
        *    \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getRadioActivity();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the life of our hero
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getLife();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Enemy will take damage when the hero use that method(but depend of some conditions)
        *    @param posAvatar -> the position of our avatar
        *    @param dirAvatar -> the direction of our avatar
        *    @param posHero -> the position of our hero
        *    @param value -> the value of the damage
        *    @param enemies -> the vector of enemies to know if can do the impact movement
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void takeDamage(vec3f posAvatar,avatarDirection dirAvatar,vec3f posHero,float value,const vector<Enemy *> & enemies);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Enemy will take damage when he is on an objectScene with damage
        *    @param value -> the value of the damage
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void takeDamage(float value);

    protected:
        vector<Matrix4f *> moveMatrix;
        vector<Sound *> enemySound;
        pair<avatarDirection,vec3f> currentMove;
        AnimationList animations;
        Weapon * weapon;
        vec3f radioActivity;
        IAEnemy * IA;
        bool enemyActivate;
        bool activatedDialog;
        Text * currentText;
        float jumpDelay,hitDelay,IADelay;
    private:

};

#endif // ENEMY_H
