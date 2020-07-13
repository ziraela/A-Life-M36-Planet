#ifndef LEVELFACTORY_H
#define LEVELFACTORY_H
#include <string>
#include "TileMap.h"
class LevelFactory
{
    public:
        void cambiarNivel(){ nivel += 1; };
        void cambiarNivelIzq(){ nivel -= 1; };
        void cambiarLaboratorio(){ nivel = 12; };
        void salirLaboratorio(){ nivel = 7; };
        void mantenerNivel(){ nivel = 11; };
        void inicializar();
        void pintarse();
        int& getNivel(){return nivel;};
        void setNivel(int x){nivel=x;};


        LevelFactory();
        virtual ~LevelFactory();
    protected:
    private:
        int nivel;
        std::string cadena;
        std::string imagen;
        std::string fondo;
        TileMap map;
        TileMap map2;
};

#endif // LEVELFACTORY_H
