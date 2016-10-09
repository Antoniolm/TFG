#ifndef GAME_H
#define GAME_H

#include "GraphicEngine/window.h"

class Game
{
    public:
        Game();
        virtual ~Game();
        void loop();

    protected:

    private:
        Window *window;
};

#endif // GAME_H
