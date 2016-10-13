////////////////////////////////////////
//  Author: Antonio David López Machado
////////////////////////////////////////

#ifndef MATRIX4FDINAMIC_H
#define MATRIX4FDINAMIC_H


class Matrix4fDinamic
{
    public:
        Matrix4fDinamic();
        Matrix4fDinamic(const Matrix4fDinamic & aMatrix);
        virtual ~Matrix4fDinamic();
        virtual Matrix4f updateState(float time);

    protected:

    private:
};

#endif // MATRIX4FDINAMIC_H
