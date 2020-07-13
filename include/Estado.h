#ifndef ESTADO_H
#define ESTADO_H
#include <SFML/Graphics.hpp>
#include "Juego.h"
class Estado
{
    public:
        Estado();
        void setEstado(int x);
        void comprobador();
        void controlador();
        void render();

        virtual ~Estado();
    protected:
    private:
        int estado;
        Juego juego;

};

#endif // ESTADO_H
