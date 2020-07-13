#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <SFML/Graphics.hpp>
#include "Bala.h"

class Personaje
{
    public:
        Personaje();
        void cargar(sf::Vector2f position);
        void moverse();
        void actualizar();
        void jump();
        void disparo();
        void choque(sf::Vector2f posEnemigo);
        void colisionMapa(sf::Vector2f posicionRectangulo, sf::FloatRect shapeRectangulo);

        sf::Sprite& getPersonaje(){ return personaje;};


        bool& getDisparando(){return disparando;};
        void setDisparando(bool x){disparando=x;};

        bool& getSaltando(){return saltando;};
        void setSaltando(bool x){saltando=x;};

        bool& getCambio(){return cambio;};
        void setCambio(bool x){cambio=x;};

        bool& getChocando(){return chocando;};
        void setChocando(bool x){chocando=x;};

        bool& getColisionando(){return colisionando;};
        void setColisionando(bool x){colisionando=x;};

        virtual ~Personaje();
    protected:
    private:
        bool pulsado=false;
        sf::Sprite personaje;
        sf::Texture texturaPersonaje;
        bool cambio = false;
        bool disparando=false;
        float vel = 300.0f;
        sf::IntRect uvRect;
        sf::Vector2u imagenActual;
        sf::Vector2u contadorImagen;
        sf::Vector2u imagenActual2;
        sf::Vector2u contadorImagen2;
        sf::Vector2f velocidadPersonaje;
        sf::Vector2f velocidadPer;

        int columna = 0;
        int columnaActual = 0;

        float totalTime = 0.0f;
        float totalTime2 = 0.0f;
        float switchTime = 0.15f;
        float velSaltoHor = 500.0f;
        float velSalto = 325.0f;
        float gravedad = 800.0f;
        bool saltando = false;
        bool disparin=false;
        bool colisionando=false;

        sf::Vector2u imagenActual3;
        sf::Vector2u contadorImagen3;
        sf::Vector2f velocidadChoque;
        float velChoque = 900.0f;
        float velChoqueHor = 800.0f;
        bool chocando=false;
        float totalTime3 = 0.0f;

        sf::Vector2f position;


};

#endif // JUGADORP_H
