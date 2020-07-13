#ifndef ENEMIGOS_H
#define ENEMIGOS_H
#include "Personaje.h"
#include <SFML/Graphics.hpp>

class Enemigos
{
    public:
        Enemigos();
        void Cargar(sf::Vector2f position, int tipo);
        void movimiento(sf::Vector2f posPersonaje, int i, bool mayor);
        void choque();
        void colisionMapa(sf::Vector2f posicionRectangulo, sf::FloatRect shapeRectangulo, bool mayor);

        sf::Sprite& getEnemigosSprite(){ return enemigosSprite;};
        sf::Vector2f GetPosition() {return enemigosSprite.getPosition();};

        Personaje& getPersonaje(){return personaje;};

        int& getTipo(){return tipo;};

        virtual ~Enemigos();
    protected:
    private:
        sf::Vector2f position;
        Personaje personaje;
        sf::Sprite enemigosSprite;
        sf::Texture enemigosTexture;
        int tipo;
        sf::Vector2u currentImage1;
        sf::Vector2u imageCount1;
        sf::Vector2u imageCountFirst;

        sf::IntRect uvRect;
        float totalTime = 0.0f;
        float switchTime = 0.15f;
        float speed = 60.0f;
        float speedPajaro = 260.0f;
        bool flip=false;
        bool mayor=false;
        bool choqueo=false;
        bool colisionando=false;

};

#endif // ENEMIGOS_H
