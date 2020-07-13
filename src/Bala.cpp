#include "Bala.h"
#include "Personaje.h"
#include "Ventana.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

Bala::Bala()
{

        currentImage1.x = 0;
        currentImage1.y = 0;
        imageCount1.x = 4;
        imageCount1.y = 1;

}

void Bala::Crear(sf::Vector2f position, bool camb){
        if (!texBala.loadFromFile("resources/bala.jpg"))
        {
            std::cerr << "Error cargando la imagen bala.png";
            exit(0);
        }


        sf::Vector2u tamTex = texBala.getSize();

        bala.setTexture(texBala);

        bala.setOrigin(tamTex.x/2,tamTex.y/2);

        bala.setTextureRect(sf::IntRect(tamTex.x * 0, tamTex.y * 0, tamTex.x, tamTex.y));

        bala.setScale(0.04f,0.04f);
        bala.setPosition(position);
        cambio=camb;


}

void Bala::movimiento(){

    sf::Vector2f movimiento(0.0f, 0.0f);

    uvRect.width = texBala.getSize().x/ float(imageCount1.x);
    uvRect.height = texBala.getSize().y/ float(imageCount1.y);

    float deltaTime = Ventana::getInstancia()->delta;

    if(cambio==false){
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


    bala.setTextureRect(uvRect);
    Ventana::getInstancia()->firstposbala += movimiento;


}

void Bala::fire(){

    if(cambio){
        bala.move(-1,0);
    }else{
        bala.move(1,0);
    }

    //bala.move(-50,6);
}


Bala::~Bala()
{
    //dtor
}
