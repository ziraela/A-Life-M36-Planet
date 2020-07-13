#include "RectangleShape.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ventana.h"
using namespace std;

RectangleShape::RectangleShape()
{
    //ctor
}

void RectangleShape::Crear(sf::Vector2f posicion, bool val, int tip){



switch (tip){


    case 1:
        {
                if (!texturaRectangle.loadFromFile("resources/rectangle2.jpg"))
                {
                    std::cerr << "Error cargando la imagen rectangle2.jpg";
                    exit(0);
                }
                break;
        }
        case 2:
        {
                if (!texturaRectangle.loadFromFile("resources/rectangle3.png"))
                {
                    std::cerr << "Error cargando la imagen rectangle3.png";
                    exit(0);
                }
        }
                break;
        case 3:
        {
                if (!texturaRectangle.loadFromFile("resources/rectangle.png"))
                {
                    std::cerr << "Error cargando la imagen rectangle.jpg";
                    exit(0);
                }
                break;

        }
}

        sf::Vector2u tamTex = texturaRectangle.getSize();
        tamTex.x = tamTex.x / 4;
        tamTex.y = tamTex.y / 3;

        rectangulo.setTexture(texturaRectangle);
        rectangulo.setOrigin(tamTex.x/2,tamTex.y/2);
        rectangulo.setTextureRect(sf::IntRect(tamTex.x * 0, tamTex.y * 0, tamTex.x, tamTex.y));
        if(tip==1){
            rectangulo.setScale(1.60,1.60);
        }else if(tip==3){
            rectangulo.setScale(0.40,0.40);
        }

        rectangulo.setPosition(posicion);
        valido=val;


}

RectangleShape::~RectangleShape()
{
    //dtor
}
