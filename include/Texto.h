#ifndef TEXTO_H
#define TEXTO_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Texto
{
    public:
        Texto();
        sf::Text& getTexto(){return texto;};
        void Asignar(sf::Vector2f posicion, sf::String cadena, int pruebilla);
        void Asignar2(sf::Vector2f posicion, int pruebilla, sf::String cadena);
        void Asignar3(sf::Vector2f posicion, sf::String cadena);
        void Asignar4(sf::Vector2f posicion, sf::String cadena);


        virtual ~Texto();
    protected:
    private:
        sf::Font fuenteTexto;
        sf::Text texto;
};

#endif // TEXTO_H
