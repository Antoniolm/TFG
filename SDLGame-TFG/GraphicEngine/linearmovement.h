////////////////////////////////////////
//  Author: Antonio David López Machado
////////////////////////////////////////


#ifndef LINEARMOVEMENT_H
#define LINEARMOVEMENT_H


class LinearMovement : public Matrix4fDinamic {

    public:
        /** Default constructor */
        LinearMovement();
        /** Default destructor */
        virtual ~LinearMovement();
        virtual Matrix4f updateState(float time);
    protected:

    private:
        //vec3f velocity
};

#endif // LINEARMOVEMENT_H
