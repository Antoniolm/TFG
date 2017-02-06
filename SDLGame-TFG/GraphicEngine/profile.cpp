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

#include "profile.h"

Profile::Profile()
{
    totalVisualTime=0;
    totalUpdateTime=0;
    nFrame=0;
    fps=0;
}

//**********************************************************************//

Profile::~Profile()
{
    //dtor
}

//**********************************************************************//

void Profile::addVisualTime(float currentVisualTime){
    totalVisualTime+=currentVisualTime;
}

//**********************************************************************//

void Profile::addUpdateTime(float currentUpdateTime){
    totalUpdateTime+=currentUpdateTime;
}

//**********************************************************************//

void Profile::incrementFrames(){
    nFrame++;
}

//**********************************************************************//

void Profile::showResult(){
    cout<< "Average update time->"<< totalUpdateTime/nFrame<<endl;
    cout<< "Average visualization time->"<< totalVisualTime/nFrame<<endl;
    cout<< "Total time->"<< SDL_GetTicks()<<endl;
}
