#ifndef MATRIX4F_H
#define MATRIX4F_H

#include <SDL_opengl.h>

class Matrix4f
{
    public:
        Matrix4f();
        virtual ~Matrix4f();
        void Translation(double x,double y,double z);
        void Scale(double x,double y,double z);
        void rotation();

    protected:

    private:
        GLdouble * matrix;
};

#endif // MATRIX4F_H
