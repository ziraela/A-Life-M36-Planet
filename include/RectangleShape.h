#ifndef RECTANGLESHAPE_H
#define RECTANGLESHAPE_H
#include <SFML/Graphics.hpp>
#include <iostream>

class RectangleShape
{
    public:
        RectangleShape();
        void Crear(sf::Vector2f posicion, bool valido, int tipo);

        sf::Sprite& getRectangle(){ return rectangulo;};

        bool& getValido(){return valido;};

        virtual ~RectangleShape();
    protected:
    private:
        sf::Sprite rectangulo;
        sf::Texture texturaRectangle;
        bool valido=false;
        int tipo;
};

#endif // RECTANGLESHAPE_H
