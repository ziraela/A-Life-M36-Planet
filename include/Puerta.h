#ifndef PUERTA_H
#define PUERTA_H
#include <SFML/Graphics.hpp>
#include <iostream>


class Puerta
{
    public:
        Puerta();
        void Crear();

        sf::Sprite& getPuerta(){ return puerta;};
        virtual ~Puerta();
    protected:
    private:
        sf::Sprite puerta;
        sf::Texture texturaPuerta;
};

#endif // PUERTA_H
