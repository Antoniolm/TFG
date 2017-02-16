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

#include "loaderthread.h"

RootMap* LoaderThread::rootMap=0;
string LoaderThread::fileMap="";

LoaderThread::LoaderThread(RootMap * aRootMap,string aFileMap)
{
    LoaderThread::rootMap=aRootMap;
    LoaderThread::fileMap=aFileMap;
}

//**********************************************************************//

LoaderThread::~LoaderThread()
{
    loader.detach();
}

//**********************************************************************//

void LoaderThread::initialize(){
    LoaderThread::rootMap->initialize(LoaderThread::fileMap);
}

//**********************************************************************//
void LoaderThread::run(){
    loader=std::thread([this] { this->initialize(); });
}
