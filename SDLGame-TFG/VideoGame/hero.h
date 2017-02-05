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

#ifndef HERO_H
#define HERO_H

#include "avatar.h"
#include "avatarmove.h"
#include "../GraphicEngine/mesh.h"
#include "../GraphicEngine/meshcollection.h"
#include "../GraphicEngine/materialcollection.h"
#include "../GraphicEngine/soundcollection.h"
#include "../GraphicEngine/scriptlmd.h"
#include "../GraphicEngine/context.h"
#include "../GraphicEngine/matrixscript.h"
#include "../GraphicEngine/rootmap.h"
#include "../GraphicEngine/matrix4f.h"
#include "../GraphicEngine/acceleratedmovement.h"
#include "../GraphicEngine/sound.h"
#include "../GraphicEngine/text.h"
#include "../GraphicEngine/animationlist.h"
#include "../GraphicEngine/controller.h"
#include "../lib/rapidjson/document.h"
#include <stdlib.h>


#include <vector>

using namespace std;
class RootMap;
class Text;
class Weapon;
class Projectile;
class Hero: public AvatarMove
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Hero(vec3f aPos);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Hero();

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
        void updateState(float time,ControllerManager * controller,RootMap * rootMap);


        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will enable the sound of our hero.That will use when the game
        *    will be pause.
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void enableSound(bool value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set a new message for our text
        *    \param message -> it is the new message that our text will show
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setDialog(string message,int index);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will activate the text of our hero
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activateDialog(bool value,int index);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will reset animations because the hero isn't in movement
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void noMove();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will return if the hero is hitting or not
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        bool isHit();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the life of our hero
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getLife();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the coins of our hero
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int getCoin();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will add a new coin to our current coins
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void addCoin(int value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Hero will take damage when a enemy use that method(but depend of some conditions)
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void takeDamage(vec3f posAvatar,avatarDirection dirAvatar,float value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Hero will take damage when he is on an objectScene with damage
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void takeDamage(float value);
    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will initialize the animation of our npc
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void initAnimation();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will create a projectile
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void createProjectile();

        vector<Projectile *> projectiles;
        vector<Matrix4f *> moveMatrix;
        vector<Sound *> heroSound;
        AnimationList animations;
        vector<Text *> texts;
        vector<bool> activatedTexts;
        Weapon * currentWeapon,* meleeWeapon,* rangedWeapon;
        float jumpDelay,hitDelay,coinDelay,shieldDelay,swapDelay,shootDelay;
        int currentCoin;
};

#endif // HERO_H


