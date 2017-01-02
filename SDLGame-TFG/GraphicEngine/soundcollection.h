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

#ifndef SOUNDCOLLECTION_H
#define SOUNDCOLLECTION_H

#include "sound.h"
#include <vector>
#include <map>
#include <string>

enum soundElement{
    sCoin //0
};

class SoundCollection
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~SoundCollection();

        static SoundCollection * getInstance(){
            if(instance == NULL)
                instance = new SoundCollection();

            return instance;
        }

        Sound * getSound(soundElement element);
        Sound * getSound(string element);
    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        SoundCollection();

        static SoundCollection* instance;
        vector<Sound *> collection;
        map<string,soundElement> enumMap;
};

#endif // SOUNDCOLLECTION_H