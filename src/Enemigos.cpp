#include "Enemigos.h"
#include "Personaje.h"
#include "Ventana.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

Enemigos::Enemigos()
{
    //ctor
    currentImage1.x = 0;
    currentImage1.y = 0;
    imageCount1.x = 2;
    imageCount1.y = 1;

}


void Enemigos::Cargar(sf::Vector2f posicion, int tipoEnemigo){

    switch (tipoEnemigo){

        case 1:
        {
                if (!enemigosTexture.loadFromFile("resources/enemigos4.png"))
                {
                    std::cerr << "Error cargando la imagen enemigos4.png";
                    exit(0);
                }
                break;
        }
        case 2:
        {
            if (!enemigosTexture.loadFromFile("resources/enemigos3.png"))
                {
                    std::cerr << "Error cargando la imagen enemigos3.png";
                    exit(0);
                }
        }
                break;
        case 3:
        {
                if (!enemigosTexture.loadFromFile("resources/enemigos1.png"))
                {
                    std::cerr << "Error cargando la imagen enemigos1.png";
                    exit(0);
                }
        }
                break;
        case 4:
        {
                if (!enemigosTexture.loadFromFile("resources/enemigos2.png"))
                {
                    std::cerr << "Error cargando la imagen enemigos2.png";
                    exit(0);
                }
        }
                break;
        case 5:
        {
                if (!enemigosTexture.loadFromFile("resources/enemigos5.png"))
                {
                    std::cerr << "Error cargando la imagen enemigos5.png";
                    exit(0);
                }
        }
                break;

    }
            sf::Vector2u tamTextura = enemigosTexture.getSize();

            if(tipoEnemigo==3 || tipoEnemigo==4){
                tamTextura.x = tamTextura.x / 2;
                tamTextura.y = tamTextura.y / 1;

            }else if(tipoEnemigo==5){
                tamTextura.x = tamTextura.x / 3;
                tamTextura.y = tamTextura.y / 1;
            }else{
                tamTextura.x = tamTextura.x / 4;
                tamTextura.y = tamTextura.y / 1;
            }

            enemigosSprite.setTexture(enemigosTexture);
            enemigosSprite.setOrigin(tamTextura.x/2,tamTextura.y/2);
            enemigosSprite.setTextureRect(sf::IntRect(tamTextura.x * 0, tamTextura.y * 0, tamTextura.x, tamTextura.y));
            enemigosSprite.setScale(1.2,1.2);
            enemigosSprite.setPosition(posicion);
            tipo = tipoEnemigo;

}

void Enemigos::movimiento(sf::Vector2f posPersonaje, int i, bool mayor){

    sf::Vector2f movimiento(0.0f, 0.0f);

     if(tipo == 1 || tipo == 2){
            imageCount1.x = 4;
            imageCount1.y = 1;
     }else if(tipo==5){
            imageCount1.x = 3;
            imageCount1.y = 1;
        }

    uvRect.width = enemigosTexture.getSize().x / float(imageCount1.x);
    uvRect.height = enemigosTexture.getSize().y / float(imageCount1.y);

    float deltaTime = Ventana::getInstancia()->delta;


    if(choqueo==false){
        if(tipo==2 || tipo==1){
            movimiento.y+=(400.f*deltaTime);
        }
    }else{
        if(tipo==2 || tipo==1){
            movimiento.y-=(400.f*deltaTime);
        }
    }
        if(mayor==true){
            if(tipo==1){
                movimiento.x+=speedPajaro*deltaTime;
            }else{
                movimiento.x+=speed*deltaTime;
            }

            flip=true;
        }else{
            if(tipo==1){
                movimiento.x-=speedPajaro*deltaTime;
            }else{
                movimiento.x-=speed*deltaTime;
            }
            flip=false;
        }

    if(movimiento.x != 0){
        totalTime += deltaTime;
        if(totalTime >= switchTime){
            totalTime -= switchTime;
            currentImage1.x++;

            if(currentImage1.x >= imageCount1.x){
                currentImage1.x = 0;
            }
        }
    }


    uvRect.top = currentImage1.y * uvRect.height;
    if(flip == false){
        uvRect.left = currentImage1.x * uvRect.width;
        uvRect.width = abs(uvRect.width);

    }else{
        uvRect.left = (currentImage1.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }

    enemigosSprite.setTextureRect(uvRect);
    enemigosSprite.move(movimiento);

}

void Enemigos::choque(){
        choqueo=true;
    sf::Vector2f movimiento(0.0f, 0.0f);

            imageCount1.x = 4;
            imageCount1.y = 1;


    uvRect.width = enemigosTexture.getSize().x / float(imageCount1.x);
    uvRect.height = enemigosTexture.getSize().y / float(imageCount1.y);

    float deltaTime = Ventana::getInstancia()->delta;


    if(tipo==2){
        movimiento.y-=(400.f*deltaTime);
    }
        if(mayor==true){
            movimiento.x+=speed*deltaTime;
            flip=true;
        }else{
            movimiento.x-=speed*deltaTime;
            flip=false;
        }

    if(movimiento.x != 0){
        totalTime += deltaTime;
        if(totalTime >= switchTime){
            totalTime -= switchTime;
            currentImage1.x++;
            if(currentImage1.x >= imageCount1.x){
                currentImage1.x = 0;
            }
        }
    }


    uvRect.top = currentImage1.y * uvRect.height;
    if(flip == false){
        uvRect.left = currentImage1.x * uvRect.width;
        uvRect.width = abs(uvRect.width);

    }else{
        uvRect.left = (currentImage1.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }

    enemigosSprite.setTextureRect(uvRect);
    enemigosSprite.move(movimiento);

}

void Enemigos::colisionMapa(sf::Vector2f posicionRectangulo, sf::FloatRect shapeRectangulo, bool mayor){

sf::Vector2f movimiento(0.0f, 0.0f);
    float deltaTime = Ventana::getInstancia()->delta;

        if(enemigosSprite.getPosition().x<posicionRectangulo.x){
             if(mayor==true){
                movimiento.x-=speed*deltaTime;
                flip=true;
                colisionando=false;
             }else{
                movimiento.x = 0;
                flip = false;
                colisionando=true;
             }

        }else{
            if(mayor==true){
                movimiento.x = 0;
                flip=true;
                colisionando=false;
             }else{
                movimiento.x-=speed*deltaTime;
                flip = false;
                colisionando=true;
             }
        }

    if(movimiento.x != 0){
        totalTime += deltaTime;
        if(totalTime >= switchTime){
            totalTime -= switchTime;
            currentImage1.x++;
            if(currentImage1.x >= imageCount1.x){
                currentImage1.x = 0;
            }
        }
    }


    uvRect.top = currentImage1.y * uvRect.height;
    if(flip == false){
        uvRect.left = currentImage1.x * uvRect.width;
        uvRect.width = abs(uvRect.width);

    }else{
        uvRect.left = (currentImage1.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }

    enemigosSprite.setTextureRect(uvRect);
    enemigosSprite.move(movimiento);
}


Enemigos::~Enemigos()
{
    //dtor
}
