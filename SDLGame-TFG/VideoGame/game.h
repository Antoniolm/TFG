#ifndef GAME_H
#define GAME_H

#include "../GraphicEngine/window.h"

class Game
{
    public:
        /**  \brief Game::Game
        *    Constructor primitive
        */
        Game();

        /**  \brief Game::~Game
        *    Destructor primitive
        */
        virtual ~Game();

        /**  \brief Game::loop()
        *    Method will contain the main loop of the videoGame
        *    In that loop will have the detection of keyboard events
        */
        void loop();

    protected:

    private:
        Window *window;
};

#endif // GAME_H
