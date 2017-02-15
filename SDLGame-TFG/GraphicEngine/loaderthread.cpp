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

#include "loaderthread.h"
LoaderThread::LoaderThread(RootMap * aRootMap,Document & aDocument,Shader & aShader)
{
    rootMap=aRootMap;
    document=&aDocument;
    shader=&aShader;
}

//**********************************************************************//

LoaderThread::~LoaderThread()
{
    loader.detach();
}

//**********************************************************************//

void LoaderThread::initialize(RootMap * aRootMap,Document & aDocument,Shader & aShader){
    //cout<<"el valor es"<<aDocument["heroPosition"][0].GetFloat()<<endl;
    rootMap->initialize(aDocument,aShader);
}

//**********************************************************************//
void LoaderThread::run(){
    loader=std::thread([this] { this->initialize(rootMap,(*document),(*shader)); });
}
