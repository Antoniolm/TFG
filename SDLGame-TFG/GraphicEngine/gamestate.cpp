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

#include "gamestate.h"

GameState::GameState()
{
    rootMap=0;
}

GameState::~GameState(){
    cout<< "test1"<< endl;
    delete controller;
    cout<< "test2"<< endl;
    delete rootMap;
    cout<< "test3"<< endl;
    delete pauseMenu;
    cout<< "test4"<< endl;
    delete mainMenu;
    cout<< "test5"<< endl;
    delete deadMenu;
    cout<< "test6"<< endl;
    delete loadScreen;
    cout<< "test7"<< endl;
    delete movie;
    cout<< "test8"<< endl;
    delete optionMenu;
    cout<< "test9"<< endl;
    delete camera;
    cout<< "test10"<< endl;
}
