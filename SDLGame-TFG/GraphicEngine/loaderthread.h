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

#ifndef LOADERTHREAD_H
#define LOADERTHREAD_H

#include <thread>
#include "rootmap.h"
#include "shader.h"
#include "../lib/rapidjson/document.h"

using namespace rapidjson;

class LoaderThread
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        LoaderThread(RootMap * aRootMap,Document & aDocument,Shader & aShader);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~LoaderThread();

        void run();

        void initialize(RootMap * aRootMap,Document & aDocument,Shader & aShader);

    protected:

    private:
        std::thread loader;
        RootMap * rootMap;
        Document * document;
        Shader * shader;
};

#endif // LOADERTHREAD_H
