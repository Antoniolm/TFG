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

#ifndef WEAPON_H
#define WEAPON_H

#include "../GraphicEngine/object3d.h"
#include "../GraphicEngine/nodescenegraph.h"
#include "../GraphicEngine/material.h"
#include "../GraphicEngine/matrix4f.h"
#include "../GraphicEngine/matrix4fdynamic.h"
#include "../GraphicEngine/meshcollection.h"
#include "../GraphicEngine/soundcollection.h"
#include "../GraphicEngine/axisrotation.h"
#include "../GraphicEngine/sound.h"

enum WeaponType{
    RANGED,
    MELEE
};

class Weapon : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Weapon(vec3f aPos,WeaponType atype,float aDamage,MeshIndex mesh,MaterialIndex material);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Weapon();

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
        *    @param gameState -> the current state of our game
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateState(float time,ControllerManager * controller,RootMap * rootMap);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set the damage of our weapon
        *    @param value -> the new value of our damage
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        void setDamage(float value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the damage of our weapon
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getDamage();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the type of our weapon
        *    \return WeaponType
        */
        //////////////////////////////////////////////////////////////////////////
        WeaponType getType();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set our weapon like another weapon
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setWeapon(const Weapon & weapon);

    protected:

    private:
        float damage;
        NodeSceneGraph * root;
        WeaponType type;
};

#endif // WEAPON_H
