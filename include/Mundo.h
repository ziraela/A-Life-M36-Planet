#ifndef MUNDO_H
#define MUNDO_H
#include "Estado.h"


class Mundo
{
    public:
        Mundo();
        void inicializar(int x);
        void  bucle();
        virtual ~Mundo();
    protected:
    private:
        Estado estado;
        sf::Clock clockMov;
        sf::Clock clockInt;

};

#endif // MUNDO_H
