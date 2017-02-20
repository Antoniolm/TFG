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

#include "savedmanager.h"

SavedManager* SavedManager::instance = NULL;

SavedManager::SavedManager()
{
}

//**********************************************************************//

SavedManager::~SavedManager()
{
}

//**********************************************************************//

string SavedManager::load(){
    string currentMap;

    //Open file
    FILE * fp = fopen("./save/save.json", "rb"); // non-Windows use "r"
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document document;
    document.ParseStream(is);
    currentMap=document["currentMap"].GetString();
    fclose(fp);

    return currentMap;
}

//**********************************************************************//

void SavedManager::save(string fileMap){

}
