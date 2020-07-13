#ifndef MONEDA_H
#define MONEDA_H
#include <SFML/Graphics.hpp>
#include <iostream>


class Moneda
{
    public:
        Moneda();
        void Cargar(sf::Vector2f posicion);

        sf::Sprite& getMoneda(){ return moneda;};
        int& getTipoEnemigo(){return tipoEnemigo;};
        void setTipoEnemigo(int x){tipoEnemigo=x;};


        virtual ~Moneda();
    protected:
    private:
    sf::Sprite moneda;
    sf::Texture monedaTexture;
    int tipoEnemigo;
};

#endif // MONEDA_H
