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

#include "herostate.h"

HeroState::HeroState(){
    MeshCollection * meshCollect =MeshCollection::getInstance();
    MaterialCollection * materialCollect =MaterialCollection::getInstance();

    currentMaterial=materialCollect->getMaterial(mLIFE100);

    position=vec4f(0.0,6.70,11.0,1.0);

    positionState=new Matrix4f();
    positionState->translation(position.x,position.y,position.z);

    Matrix4f * rotationMenu=new Matrix4f();
    rotationMenu->rotation(20,1.0,0.0,0.0);

    ///////////////////////
    //Life Node
    Matrix4f * positionText=new Matrix4f();
    positionText->translation(-0.65,0.0,0.0);

    Matrix4f * scaleMenu=new Matrix4f();
    scaleMenu->scale(0.3,0.4,1.0);

    NodeSceneGraph * nodeLife=new NodeSceneGraph(false,true);
    nodeLife->add(positionText);
    nodeLife->add(scaleMenu);
    nodeLife->add(currentMaterial);
    nodeLife->add(meshCollect->getMesh(TEXT));

    ///////////////////////
    //Coin Node
    Matrix4f * positionCoin=new Matrix4f();
    positionCoin->translation(+0.65,0.0,0.0);

    Matrix4f * scaleCoin=new Matrix4f();
    scaleCoin->scale(0.03,0.3,1.0);

    NodeSceneGraph * nodeCrystal=new NodeSceneGraph(false,true);
    nodeCrystal->add(positionCoin);
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
    vec3f posHero=gameState.rootMap->getHero()->getPosition();
    positionState->translation(posHero.x,posHero.y+7.4,posHero.z+10.6);
}
