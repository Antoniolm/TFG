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

#include "endmapregion.h"

EndMapRegion::EndMapRegion(const Value & regionFeatures){

    minArea=vec3f(regionFeatures["minPosition"][0].GetFloat(),regionFeatures["minPosition"][1].GetFloat(),regionFeatures["minPosition"][2].GetFloat());
    maxArea=vec3f(regionFeatures["maxPosition"][0].GetFloat(),regionFeatures["maxPosition"][1].GetFloat(),regionFeatures["maxPosition"][2].GetFloat());

    activated=false;
}

//**********************************************************************//

EndMapRegion::~EndMapRegion()
{
    //dtor
}

//**********************************************************************//

void EndMapRegion::updateState(GameState & gameState){
    Hero * hero =gameState.rootMap->getHero();
    vec3f position=hero->getPosition();

    if(position>minArea && position<maxArea && !activated)
        activated=true;
}

//**********************************************************************//

bool EndMapRegion::isActivated(){
    return activated;
}
