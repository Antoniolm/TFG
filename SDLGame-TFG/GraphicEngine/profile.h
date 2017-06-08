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

#ifndef PROFILE_H
#define PROFILE_H

#include <iostream>
#include "SDL2/SDL.h"

using namespace std;

class Profile
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Profile();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will add a new time in our visualization time
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void addVisualTime(float currentVisualTime);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will add a new time in our update time
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void addUpdateTime(float currentUpdateTime);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will increment the number of frames
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void incrementFrames();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will print our current information(times, fps etc)
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void showResult();

        static Profile * getInstance(){
            if(instance == NULL)
                instance = new Profile();

            return instance;
        }
    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Profile();

        int nFrame;              // Number of frames
        float initialTime;       // Initial time of the application
        float totalVisualTime;   // Time used in the visualization of object
        float totalUpdateTime;   // Time used in the update of object
        float fps;               // Frame per second

        static Profile* instance;// Instance of the profile
};

#endif // PROFILE_H
