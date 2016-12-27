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

#include "coin.h"

Coin::Coin(vec3f aPosition,int aValue){
    value=aValue;
    notTake=true;
    position=vec4f(aPosition.x,aPosition.y,aPosition.z,1.0);

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();


    animationMatrix=new Matrix4f();
    animationMatrix->identity();

    rotation=new AxisRotation(100,0.0,1.0,0.0);

    Matrix4f * transMatrix=new Matrix4f();
    transMatrix->translation(position.x,position.y,position.z);

    root=new NodeSceneGraph();
    root->add(transMatrix);
    root->add(animationMatrix);
    if(value==10)
        root->add(materialCollect->getMaterial(mCOIN10));
    else
        root->add(materialCollect->getMaterial(mCOIN50));
    root->add(meshCollect->getMesh(COIN));
    currentTime=SDL_GetTicks();

    soundTake=new Sound("sounds/coin.wav",1,30,4,0);
}

//**********************************************************************//

Coin::~Coin()
{

}

//**********************************************************************//

void Coin::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void Coin::updateState(float time,const Uint8* currentKeyStates,RootMap * rootMap ){
    vec3f posHero=rootMap->getHero()->getPosition();
    float distance=sqrt(pow(position.x-posHero.x,2.0)+pow(position.y-posHero.y,2.0)+pow(position.z-posHero.z,2.0));
    if(distance<=0.8){
        notTake=false;
        rootMap->getHero()->addCoin(value);
        soundTake->stop();
        soundTake->play();
    }

    //Animation
    animationMatrix->setMatrix(rotation->updateState(time-currentTime).getMatrix());
    currentTime+=time-currentTime;
}

//**********************************************************************//

int Coin::getValue(){
    return value;
}

//**********************************************************************//

bool Coin::isTake(){
    return !notTake;
}
