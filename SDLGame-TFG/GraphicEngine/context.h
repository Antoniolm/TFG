////////////////////////////////////////
//  Author: Antonio David López Machado
////////////////////////////////////////

#ifndef CONTEXT_H
#define CONTEXT_H


class Context
{
    public:
        /** Default constructor */
        Context();
        /** Default destructor */
        virtual ~Context();

        unsigned visualization_mode;
        unsigned camera_mode;

    protected:

    private:
};

#endif // CONTEXT_H
