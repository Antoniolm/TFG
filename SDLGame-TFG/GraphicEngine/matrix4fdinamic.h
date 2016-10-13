////////////////////////////////////////
//  Author: Antonio David López Machado
////////////////////////////////////////

#ifndef MATRIX4FDINAMIC_H
#define MATRIX4FDINAMIC_H

#include "matrix4f.h"

class Matrix4fDinamic
{
    public:
        Matrix4fDinamic();
        Matrix4fDinamic(const Matrix4fDinamic & aMatrix);
        virtual ~Matrix4fDinamic();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the Matrix4xf. That change need the
        *    current time in our application
        *    \return the new state of the matrix4f
        */
        //////////////////////////////////////////////////////////////////////////
        virtual Matrix4f updateState(float time);

    protected:
        Matrix4f currentMatrix;
    private:

};

#endif // MATRIX4FDINAMIC_H
