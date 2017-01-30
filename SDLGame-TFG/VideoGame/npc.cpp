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

#include "npc.h"

Npc::Npc(){}

//**********************************************************************//

Npc::Npc(vec3f aPosition)
{
    position=vec4f(aPosition.x,aPosition.y,aPosition.z,1.0);
    npcActivate=false;

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    //Matrix for animation
    Matrix4f * matrix=new Matrix4f();
    matrix->identity();
    moveMatrix.push_back(matrix);

    Matrix4f * transNPC=new Matrix4f();
    transNPC->translation(position.x,position.y,position.z);

    Matrix4f * scaleNPC=new Matrix4f();
    scaleNPC->scale(1.5,1.5,1.5);

    NodeSceneGraph * npcNode=new NodeSceneGraph();
    npcNode->add(transNPC);
    npcNode->add(moveMatrix[0]);
    npcNode->add(scaleNPC);
    npcNode->add(materialCollect->getMaterial(mBUTLER));
    npcNode->add(meshCollect->getMesh(BUTLER));
    root->add(npcNode);

    TTF_Font *font=TTF_OpenFont( "font/Xolonium-Regular.ttf", 20);
    currentText=new Text(mDIALOG,font);
    currentText->setPosition(vec3f(position.x,position.y+1.5f,position.z));
    currentTime=SDL_GetTicks();
    initAnimation();

}

//**********************************************************************//

Npc::~Npc()
{
    delete currentText;
}

//**********************************************************************//

void Npc::addDialog(const string state,speakerMessage speaker){
    stateMachine.addState(state,speaker);
}

//**********************************************************************//

void Npc::nextDialog(){
    if(stateMachine.isLastState()){
        npcActivate=false;
        stateMachine.firstState();
    }
    else {
        stateMachine.nextState();
    }
}

//**********************************************************************//

void Npc::currentDialog(){
    currentText->setMessage(stateMachine.getCurrentState());
    currentText->init();
}

//**********************************************************************//

void Npc::visualization(Context & cv){
    root->visualization(cv);

    if(npcActivate && stateMachine.getCurrentSpeaker()==NPC_DIALOG)
        currentText->visualization(cv);
}

//**********************************************************************//

void Npc::updateState(float time,Controller * controller,RootMap * rootMap  ){
    if(time-currentTime>200)
        currentTime=time-50;

    animation.updateState(time-currentTime);
    moveMatrix[0]->product(animation.readMatrix(0).getMatrix());

    currentTime+=time-currentTime;
}

//**********************************************************************//

void Npc::activateNpc(bool value){
    npcActivate=value;
    if(value==false)
        stateMachine.firstState();
}

//**********************************************************************//

bool Npc::getActivate(){
    return npcActivate;
}

//**********************************************************************//

speakerMessage Npc::getSpeaker(){
    return stateMachine.getCurrentSpeaker();
}

//**********************************************************************//

string & Npc::getMessage(){
    return stateMachine.getCurrentState();
}

//**********************************************************************//

vec3f Npc::getPosition(){
    return vec3f(position.x,position.y,position.z);
}

//**********************************************************************//

bool Npc::isInitialState(){
    return stateMachine.isFirstState();
}

//**********************************************************************//
void Npc::initAnimation(){
    LinearMovement * transBody=new LinearMovement(vec3f(0.0,0.2,0));
    LinearMovement * transBodySecond=new LinearMovement(vec3f(0.0,-0.2,0));

    //Movement to the first arm
    MatrixScript * bodyScript=new MatrixScript();

    bodyScript->add(0.5,transBody);
    bodyScript->add(0.5,transBodySecond);

    animation.add(bodyScript);


}
