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

#ifndef OBJECTSCENE_H
#define OBJECTSCENE_H

#include "object3d.h"
#include "matrix4f.h"
#include "structdata.h"

class ObjectScene : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        ObjectScene();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        ObjectScene(Object3D * aObject3,float aDamage=0.0);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~ObjectScene();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        /////////////////////////////////////////////////////////////////////////
        void visualization(Context & vis);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateState(float time,Controller * controller,RootMap * rootMap );

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will obtain the boundingBox of the object.
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getPosition();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will obtain the boundingBox of the object.
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        BoundingBox getBoundingBox();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the damage that the object do to an avatar
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        virtual float getDamage();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will obtain the position of our objectScene
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void obtainPosition(Context vis);
    protected:
        vec4f position;
        Object3D * object;
        Matrix4f matrix;
        float damage;
    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will generate the next boundingBox of the object.
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void generateBoundingbox();

};

#endif // OBJECTSCENE_H
