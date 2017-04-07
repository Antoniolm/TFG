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
#include "item.h"

Item::Item(vec3f aPosition,int aValue,ItemIndex aType){
    value=aValue;
    notTake=true;
    type=aType;
    position=vec4f(aPosition.x,aPosition.y,aPosition.z,1.0);

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();
    SoundCollection * soundCollect = SoundCollection::getInstance();

    animationMatrix=new Matrix4f();
    animationMatrix->identity();

    rotation=new AxisRotation(100,0.0,1.0,0.0);

    Matrix4f * transMatrix=new Matrix4f();
    transMatrix->translation(position.x,position.y,position.z);

    //Check type
    MaterialIndex materialType;
    MeshIndex meshType;

    switch(type){
        case iCOIN:
            materialType=mCRYSTAL;
            meshType=COIN;
        break;
        case iPOTION:
            materialType=mPOTION;
            meshType=POTION;
        break;
    }


    root=new NodeSceneGraph();
    root->add(transMatrix);
    root->add(animationMatrix);
    root->add(materialCollect->getMaterial(materialType));
    root->add(meshCollect->getMesh(meshType));
    currentTime=SDL_GetTicks();

    soundTake=soundCollect->getSound(sCoin);
}

//**********************************************************************//

Item::~Item(){
    delete root;
    delete rotation;
}

//**********************************************************************//

void Item::visualization(Context & cv){
    if(position.x>cv.minVisualPosition.x && position.x<cv.maxVisualPosition.x
       && position.y>cv.minVisualPosition.y && position.y<cv.maxVisualPosition.y)
        root->visualization(cv);
}

//**********************************************************************//

void Item::updateState(GameState & gameState){
    float time=gameState.time;
    Hero * hero=gameState.rootMap->getHero();
    vec3f posHero=hero->getPosition();
    float distance=sqrt(pow(position.x-posHero.x,2.0)+pow(position.y-posHero.y,2.0)+pow(position.z-posHero.z,2.0));

    if(distance<=0.4){
        notTake=false;

        //check his type
        switch(type){
        case iCOIN:
            hero->addCoin(value);
            soundTake->play();
        break;
        case iPOTION:
            if(hero->getLife()!=hero->getMaxLite()){
                hero->addLife(value);
                soundTake->play();
            }
            else
                notTake=true;
        break;
        }
    }

    //Animation
    animationMatrix->setMatrix(rotation->updateState(time-currentTime).getMatrix());
    currentTime+=time-currentTime;
}
//**********************************************************************//

void Item::setValue(int aValue){
    value=aValue;
}

//**********************************************************************//

int Item::getValue(){
    return value;
}

//**********************************************************************//

bool Item::isTake(){
    return !notTake;
}
