////////////////////////////////////////
//  Author: Antonio David López Machado
////////////////////////////////////////

#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "context.h"

class Object3D
{
    public:
        Object3D();
        virtual ~Object3D();

    protected:
        float currentTime;
    private:

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void visualization(Context & cv);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void updateState(float time);
};

#endif // OBJECT3D_H
