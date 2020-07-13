#include "Puerta.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

Puerta::Puerta()
{
    //ctor
}

void Puerta::Crear(){

            if (!texturaPuerta.loadFromFile("resources/puerta.png"))
                {
                    std::cerr << "Error cargando la imagen puerta.png";
                    exit(0);
            }

        sf::Vector2u tamTex = texturaPuerta.getSize();
        puerta.setTexture(texturaPuerta);
        puerta.setOrigin(tamTex.x/2,tamTex.y/2);
        puerta.setTextureRect(sf::IntRect(tamTex.x * 0, tamTex.y * 0, tamTex.x, tamTex.y));
        puerta.setScale(0.80, 0.80);
        puerta.setPosition(sf::Vector2f(485, 480/2));



}

Puerta::~Puerta()
{
    //dtor
}
