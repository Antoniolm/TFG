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

#ifndef OPTIONMANAGER_H
#define OPTIONMANAGER_H

#include "../lib/rapidjson/document.h"
#include "../lib/rapidjson/stringbuffer.h"
#include "../lib/rapidjson/filereadstream.h"
#include <string>
#include <fstream>
#include <sstream>


class OptionManager
{
    public:


        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~OptionManager();

         //////////////////////////////////////////////////////////////////////////
        /**
        *    It will load the current save
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void load();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will save the currentMap in the user save
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void save(pair<int,int>aResolution,bool wind,int aVolume);

        static OptionManager * getInstance(){
            if(instance == NULL)
                instance = new OptionManager();

            return instance;
        }

    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        OptionManager();

        static OptionManager* instance;
        pair<int,int> resolution;
        bool window;
        int volume;
};

#endif // OPTIONMANAGER_H
