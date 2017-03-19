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

#include "herostate.h"

HeroState::HeroState(){
    MeshCollection * meshCollect =MeshCollection::getInstance();
    MaterialCollection * materialCollect =MaterialCollection::getInstance();

    currentMaterial=materialCollect->getMaterial(mLIFE100);

    position=vec4f(0.0,6.70,11.0,1.0);

    Matrix4f * positionState=new Matrix4f();
    positionState->translation(position.x,position.y,position.z);

    Matrix4f * rotationMenu=new Matrix4f();
    rotationMenu->rotation(20,1.0,0.0,0.0);

    ///////////////////////
    //Life Node
    Matrix4f * positionText=new Matrix4f();
    positionText->translation(0.725,0.5,0.8);

    Matrix4f * scaleMenu=new Matrix4f();
    scaleMenu->scale(0.35,1.8,0.5);

    NodeSceneGraph * nodeLife=new NodeSceneGraph(false,true);
    nodeLife->add(positionText);
    nodeLife->add(scaleMenu);
    nodeLife->add(currentMaterial);
    nodeLife->add(meshCollect->getMesh(TEXT));

    ///////////////////////
    //Coin Node
    Matrix4f * scaleCoin=new Matrix4f();
    scaleCoin->scale(1.0,4.2,1.0);

    NodeSceneGraph * nodeCrystal=new NodeSceneGraph(false,true);
    nodeCrystal->add(scaleCoin);
    nodeCrystal->add(materialCollect->getMaterial(mCRYSDRAW));
    nodeCrystal->add(meshCollect->getMesh(TEXT));

    root=new NodeSceneGraph(false,true);
    root->add(positionState);
    root->add(rotationMenu);
    root->add(nodeCrystal);
    root->add(nodeLife);
    currentTime=SDL_GetTicks();
}

//**********************************************************************//

HeroState::~HeroState()
{
    delete root;
}

//**********************************************************************//

void HeroState::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void HeroState::updateState(GameState & gameState){

}