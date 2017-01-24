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

#ifndef ANIMATIONLIST_H
#define ANIMATIONLIST_H

#include <vector>
#include "scriptlmd.h"

using namespace std;

class AnimationList
{
    public:
        /** Default constructor */
        AnimationList();
        /** Default destructor */
        virtual ~AnimationList();

        void add(ScriptLMD * animation);

        void activate(int index);

        void update(float time);

        void resetAnimation(int index);

        int getState();

        ScriptLMD * getAnimation();

    protected:

    private:
        vector<ScriptLMD *> animations;
        int currentAnimation;
};

#endif // ANIMATIONLIST_H
