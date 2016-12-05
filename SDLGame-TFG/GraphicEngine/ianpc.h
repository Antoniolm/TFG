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

#ifndef IANPC_H
#define IANPC_H

#include <vector>
#include <string>

using namespace std;

class IANpc
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        IANpc();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~IANpc();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will add a new state in our avatar
        *    \param state -> the new element of our vector
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void addState(const string & state);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the current dialog of our avatar
        *    \return string
        */
        //////////////////////////////////////////////////////////////////////////
        string & getCurrentState();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the number of state
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        int getNumState();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will clean our IA
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void clean();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    IA will return to the first state
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void firstState();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    IA will go to the next state
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void nextState();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    IA will go to the before state
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void beforeState();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    IA will check if that currentState is the last state.
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isLastState();

    protected:

    private:
        vector<string>  states;
        int currentState;

};

#endif // IANPC_H