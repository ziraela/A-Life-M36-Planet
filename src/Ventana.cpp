#include "Ventana.h"
#include "Juego.h"
#include <SFML/Graphics.hpp>

Ventana* Ventana::instance = nullptr;

Ventana* Ventana::getInstancia(){
        if(instance == nullptr)
            instance = new Ventana();

        return instance;
}
    //sf::RenderWindow window2(sf::VideoMode(1920, 1056), "Tokyo Zero", sf::Style::Close | sf::Style::Resize);

Ventana::Ventana()
{
     window.create(sf::VideoMode(640, 480), "A life M36 planet", sf::Style::Close | sf::Style::Resize);
     firstpos.x = 0.0f;
     firstpos.y = 0.0f;
     firstposbala.x = personaje.getPersonaje().getPosition().x;
     firstposbala.y = personaje.getPersonaje().getPosition().y;

}

Ventana::~Ventana()
{

    //destroy();
    //dtor
}
