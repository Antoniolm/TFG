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

#ifndef MELEEENEMY_H
#define MELEEENEMY_H

#include "enemy.h"
#include "objectscene.h"
#include "../lib/rapidjson/document.h"
#include "nodescenegraph.h"
#include "object3d.h"
#include "matrix4f.h"
#include "materialcollection.h"
#include "meshcollection.h"

class MeleeEnemy : public Enemy
{
    public:
        /** Default constructor */
        MeleeEnemy(float aLife,vec3f aPosition,vec3f aRadioActivity);
        /** Default destructor */
        virtual ~MeleeEnemy();

    protected:

    private:
};

#endif // MELEEENEMY_H
