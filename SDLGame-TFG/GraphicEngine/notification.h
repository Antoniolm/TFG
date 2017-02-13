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

#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "object3d.h"
#include "context.h"
#include "nodescenegraph.h"
#include "meshcollection.h"
#include "materialcollection.h"
#include "../lib/rapidjson/document.h"

using namespace rapidjson;

class Notification : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Notification(vec3f aPosition,vec3f aScale,float aVisibleTime,MaterialIndex material);

        //////////////////////////////////////////////////////////////////////////
        /** Json constructor */
        //////////////////////////////////////////////////////////////////////////
        Notification(const Value & notificationFeatures);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Notification();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void visualization(Context & vis);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateState(float time,ControllerManager * controller,RootMap * rootMap );

    protected:

    private:
        NodeSceneGraph * root;
        Matrix4f * transNoti;
        float visibleTime; //Time that our notification will be activated
        float initialTime;
        bool activatedNoti;

};

#endif // NOTIFICATION_H
