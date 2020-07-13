#include "Moneda.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Moneda::Moneda()
{
    //ctor
}

void Moneda::Cargar(sf::Vector2f posiEnemiga){

        if (!monedaTexture.loadFromFile("resources/moneda.png"))
                {
                    std::cerr << "Error cargando la imagen moneda.png";
                    exit(0);
                }



        sf::Vector2u tamTex = monedaTexture.getSize();
        moneda.setTexture(monedaTexture);


        moneda.setOrigin(tamTex.x/2,tamTex.y/2);

        moneda.setTextureRect(sf::IntRect(tamTex.x * 0, tamTex.y * 0, tamTex.x, tamTex.y));

        moneda.setScale(0.09f,0.09f);
        moneda.setPosition(posiEnemiga);

}

Moneda::~Moneda()
{
    //dtor
}
