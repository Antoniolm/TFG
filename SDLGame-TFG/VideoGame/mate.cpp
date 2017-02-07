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

#include "mate.h"

Mate::Mate()
{
    position=vec4f(15.5,2.0,-4,1.0);

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    Matrix4f * transMatrix=new Matrix4f();
    transMatrix->translation(position.x,position.y,position.z);

    root=new NodeSceneGraph();
    root->add(transMatrix);
    root->add(materialCollect->getMaterial(mMATE));
    root->add(meshCollect->getMesh(MATEHEAD));
    currentTime=SDL_GetTicks();

}

//**********************************************************************//

Mate::~Mate()
{
    //dtor
}

//**********************************************************************//

void Mate::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void Mate::updateState(float time,ControllerManager * controller,RootMap * rootMap ){
}
