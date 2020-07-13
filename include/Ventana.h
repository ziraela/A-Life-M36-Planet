#ifndef VENTANA_H
#define VENTANA_H
#include "Mundo.h"
#include "LevelFactory.h"
#include <SFML/Graphics.hpp>

class Ventana
{
    public:
        static Ventana* getInstancia();
        float delta = 0.0f;
        sf::Time push;
        float percent=0.0f;
        Mundo mundo;
        sf::RenderWindow window;
        sf::Vector2f firstpos;
        sf::Vector2f lastpos;
        sf::Vector2f firstposbala;
        sf::Vector2f lastposbala;
        sf::Vector2f firstposenemigo;
        sf::Vector2f lastposenemigo;
        LevelFactory factory;
        bool terminar=false;

        Personaje& getPersonaje(){return personaje;};
        vector <Enemigos>& getEnemigosVector(){return enemigosNuevos;};


    protected:
    private:
        static Ventana* instance;
        Ventana();
        std::vector <Enemigos> enemigosNuevos;
        Personaje personaje;
        Enemigos enemigo;


        virtual ~Ventana();
};

#endif // WINDOW_H
