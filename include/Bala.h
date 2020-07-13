#ifndef BALA_H
#define BALA_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Personaje.h"


class Bala
{
    public:
        Bala();
        void cargar();
        void movimiento();
        void Crear(sf::Vector2f position, bool cambio);
        void fire();
        sf::Sprite& getBala(){ return bala;};
        sf::RectangleShape& getBullet() {return bullet;};


        virtual ~Bala();
    protected:
    private:
        bool disparando = false;
        sf::Sprite bala;
        sf::RectangleShape bullet;

        sf::Texture texBala;
        bool flip=false;
        bool cambio=false;
        float speed = 450.0f;
        float totalTime = 0.0f;
        float switchTime = 0.2;
        sf::IntRect uvRect;
        sf::Vector2u currentImage1;
        sf::Vector2u imageCount1;
};

#endif // BALA_H
