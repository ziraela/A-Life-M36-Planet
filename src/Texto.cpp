#include "Texto.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ventana.h"
#include <string>

Texto::Texto()
{
    if (!fuenteTexto.loadFromFile("resources/pixelart.ttf"))
    {
        std::cerr << "Error cargando la fuente pixelart.ttf";
        exit(0);
    }

    texto.setFont(fuenteTexto);
    texto.setCharacterSize(20);
}

void Texto::Asignar(sf::Vector2f posicion, sf::String cadena, int number){
    std::string numero=std::to_string(number);
    texto.setString(cadena + numero);
    texto.setOrigin(texto.getGlobalBounds().width/2, 0);
    texto.setPosition(posicion);
}


void Texto::Asignar2(sf::Vector2f posicion, int number, sf::String cadena){
    std::string numero=std::to_string(number);
    texto.setString(numero + cadena);
    texto.setOrigin(texto.getGlobalBounds().width/2, 0);
    texto.setPosition(posicion);
}

void Texto::Asignar3(sf::Vector2f posicion, sf::String cadena){

    texto.setString(cadena);
    texto.setOrigin(texto.getGlobalBounds().width/2, 0);
    texto.setPosition(posicion);
    texto.setCharacterSize(100);
}

void Texto::Asignar4(sf::Vector2f posicion, sf::String cadena){

    texto.setString(cadena);
    texto.setOrigin(texto.getGlobalBounds().width/2, 0);
    texto.setPosition(posicion);
    texto.setCharacterSize(20);
}


Texto::~Texto()
{
    //dtor
}
