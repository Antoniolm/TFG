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

Npc::Npc()
{
    npcActivate=false;
    Mesh * cubeObject=new Mesh("geometries/cube.obj");
    cubeObject->init();

    Matrix4f * transOneCube=new Matrix4f();
    transOneCube->translation(3.5f,1.5f,-3.5f);

    Matrix4f * scaleCube=new Matrix4f();
    scaleCube->scale(0.5,1,0.5);

    Material * material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/wood.png");

    NodeSceneGraph * cubeNode=new NodeSceneGraph();
    cubeNode->add(transOneCube);
    cubeNode->add(scaleCube);
    cubeNode->add(material);
    cubeNode->add(cubeObject);
    root->add(cubeNode);

    TTF_Font *font=TTF_OpenFont( "font/lazy.ttf", 40);
    currentText=new Text("Oju","now",100,100,vec3f(0.0,2.0,0.0),font);
    currentText->init();
}

//**********************************************************************//

Npc::~Npc()
{
    //dtor
}

//**********************************************************************//

void Npc::addDialog(const string state){
    stateMachine.addState(state);
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
    currentText->setMessage(stateMachine.getCurrentState());
    currentText->init();
}

//**********************************************************************//

void Npc::currentDialog(){
    currentText->setMessage(stateMachine.getCurrentState());
    currentText->init();
}

//**********************************************************************//

void Npc::visualization(Context & cv){
    root->visualization(cv);

    if(npcActivate)
        currentText->visualization(cv);
}

//**********************************************************************//

void Npc::updateState(float time){

}

//**********************************************************************//

void Npc::activateNpc(bool value){
    npcActivate=value;
}

//**********************************************************************//

bool Npc::getActivate(){
    return npcActivate;
}
