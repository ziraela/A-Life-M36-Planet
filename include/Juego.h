#ifndef JUEGO_H
#define JUEGO_H
#include "Personaje.h"
#include "Bala.h"
#include "Enemigos.h"
#include "Moneda.h"
#include "Puerta.h"
#include "Texto.h"
#include "LevelFactory.h"
#include "RectangleShape.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;

class Juego
{
    public:
        Juego();
        void inicializar();
        void render();
        void cargar();
        void dibujarHud();
        void Rectangulos();
        void terminado();

        Personaje& getPersonaje(){return personaje;};
        RectangleShape& getRectangle(){return rectangulo;};


        bool& getColisionRect(){return colisionRect;};
        bool& getMuerto(){return muerto;};
        bool& getCasiMuerto(){return casiMuerto;};



        void enemigosColision();
        void balasColision();
        void rectanguloColision();
        void monedasColision();
        void puertaColision();
        void deleteMoneda();
        void deleteBala();



        virtual ~Juego();
    protected:
    private:
        Personaje personaje;
        sf::Vector2f posicionInicio;
        bool cambioNivelIzq=false;
        bool cambioNivelDcha=false;
        sf::Vector2f posicionEnColision;

        Bala* bulleto;
        Bala* bulletActual;
        std::vector <Bala*> bulletVec;

        sf::RectangleShape bullet2;
        bool disparin=false;
        int cont=0;

        Enemigos* enemigo;
        Enemigos* enemigoActual;
        vector <Enemigos*> enemigosNuevos;

        bool colisionEnemigo=false;
        bool colisionBala=false;
        int colisionBalaCont=0;
        int colisionEnemigoCont=0;
        bool aparecido=false;
        int contadorAparecido=0;
        bool existe=true;
        bool parar=false;
        sf::Clock clockEn;
        sf::Clock clockMon;
        bool stop=false;
        bool creado=true;
        bool mayor=false;

        int muertes=0;

        bool valido0=false;
        bool valido1=false;
        bool valido2=false;
        bool valido3=false;

        bool muerto=false;
        bool casiMuerto=false;

        Moneda* moneda;
        Moneda* monedaActual;
        vector <Moneda*> monedas;
        bool monedahecha=false;
        int nil=0;
        int tipoEnMuerto=0;
        int tipoEn=0;
        int nilinfo=0;
        bool monedaCogida=false;


        bool colisionRect=false;

        int exp=200;
        int life=30;

        Texto* textoLife;
        Texto* textoExp;
        Texto* textoNil;
        Texto* textoCogerMoneda;
        Texto* textoModoDios;
        Texto* textoGameOver;


        Puerta* puerta;
        bool puertaDone=false;
        bool laboratorio=false;
        bool entroLaboratorio=false;
        bool salgoLaboratorio=false;

        LevelFactory fact;


        sf::RectangleShape rectangule;
        RectangleShape rectangulo;
        vector<RectangleShape> rectangulos;

        bool modoDios=false;
        sf::Clock clockFin;

};

#endif // EPLAT_H
