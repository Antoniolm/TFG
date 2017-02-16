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
#include <string>

class LoaderThread
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        LoaderThread(RootMap * aRootMap,string aFileMap,Shader & aShader,int prueba);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~LoaderThread();

        void run();

        void initialize(LoaderThread * loader,int prueba);

    protected:

    private:
        std::thread loader;
        RootMap * rootMap;
        string fileMap;
        Shader * shader;
        int prueb;
};

#endif // LOADERTHREAD_H
