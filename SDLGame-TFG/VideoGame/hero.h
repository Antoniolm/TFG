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
#include "../GraphicEngine/mesh.h"
#include "../GraphicEngine/meshmaterial.h"
#include "../GraphicEngine/scriptlmd.h"
#include "../GraphicEngine/context.h"
#include "../GraphicEngine/matrixscript.h"
#include <vector>

using namespace std;

class Hero: public Avatar
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Hero();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Hero();

        virtual void visualization(Context & cv);

        void moveBody(vec3f aMove,avatarDirection aDir);

    protected:

    private:
        vector<Matrix4f *> moveMatrix;
        float currentTime;
        ScriptLMD animation;
        Matrix4f * moveHero;
        avatarDirection direction;
};

#endif // HERO_H


