#include "Mundo.h"
#include "Estado.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ventana.h"
#define UPDATE_TICK_TIME (1000/15)
using namespace std;

Mundo::Mundo()
{
    //ctor
}

void Mundo::inicializar(int x)
{
    estado.setEstado(x);
    bucle();
}

void Mundo::bucle()
{
  estado.comprobador();

   while (Ventana::getInstancia()->window.isOpen())
    {
        Ventana::getInstancia()->delta = clockMov.restart().asSeconds();
        //Ventana::getInstancia()->push = clockEn.getElapsedTime();
        // Process events
        sf::Event event;
        while (Ventana::getInstancia()->window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed){
                //Ventana::getInstancia()->window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Q)
                {
                  Ventana::getInstancia()->window.close();
                }
            }
            }


        if(clockInt.getElapsedTime().asMilliseconds()> UPDATE_TICK_TIME){
            Ventana::getInstancia()->lastpos = Ventana::getInstancia()->firstpos;
            //Ventana::getInstancia()->lastposbala = Ventana::getInstancia()->firstposbala;
            estado.controlador();
        }

        Ventana::getInstancia()->percent = std::min(1.f, (float)clockInt.getElapsedTime().asMilliseconds()/UPDATE_TICK_TIME);
        // Clear screen
        //window.clear();
        // Update the window
        Ventana::getInstancia()->window.clear();
        estado.render();
        Ventana::getInstancia()->window.display();
    }

   //return EXIT_SUCCESS;
}



Mundo::~Mundo()
{
    //dtor
}
