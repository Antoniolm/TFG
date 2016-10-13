////////////////////////////////////////
//  Author: Antonio David López Machado
////////////////////////////////////////

#ifndef GAME_H
#define GAME_H

#include "../GraphicEngine/window.h"

class Game
{
    public:


        /** Default destructor */
        Game();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Destructor primitive
        */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Game();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Method will contain the main loop of the videoGame
        *    In that loop will have the detection of keyboard events
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void loop();

    protected:

    private:
        Window *window;
};

#endif // GAME_H
