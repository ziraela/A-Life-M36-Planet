#include "Personaje.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Mundo.h"
#include "Ventana.h"
#include "Bala.h"

using namespace std;

Personaje::Personaje()
{
    imagenActual.x = 0;
    imagenActual.y = 0;
    contadorImagen.x = 4;
    contadorImagen.y = 3;

    imagenActual2.x = 0;
    imagenActual2.y = 0;
    contadorImagen2.x = 4;
    contadorImagen2.y = 3;

    imagenActual3.x = 0;
    imagenActual3.y = 0;
    contadorImagen3.x = 4;
    contadorImagen3.y = 3;

}

void Personaje::cargar(sf::Vector2f position)
{

        if (!texturaPersonaje.loadFromFile("resources/spritesheet.png"))
        {
            std::cerr << "Error cargando la imagen spritesheet.png";
            exit(0);
        }


        sf::Vector2u tamTex = texturaPersonaje.getSize();
        tamTex.x = tamTex.x / 4;
        tamTex.y = tamTex.y / 3;

        personaje.setTexture(texturaPersonaje);
        personaje.setOrigin(tamTex.x/2,tamTex.y/2);
        personaje.setTextureRect(sf::IntRect(tamTex.x * 0, tamTex.y * 0, tamTex.x, tamTex.y));
        personaje.setScale(1.40,1.40);

        personaje.setPosition(position);

        Ventana::getInstancia()->firstpos = personaje.getPosition();
}

void Personaje::moverse(){

sf::Vector2f movimiento(0.0f, 0.0f);

    uvRect.width = texturaPersonaje.getSize().x / float(contadorImagen.x);
    uvRect.height = texturaPersonaje.getSize().y / float(contadorImagen.y);

    float deltaTime = Ventana::getInstancia()->delta;



    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
        movimiento.x += vel * deltaTime; //se mueve a la izquierda
        columna = 0;
        cambio = false; //que se de la vuelta

    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
        movimiento.x -= vel * deltaTime;
        columna = 0;
        cambio = true;

    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            columna = 2;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                cambio = true;
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                cambio = false;
            }
    }else{
        columna = 0;
    }


    if(columnaActual != columna){
        imagenActual.x = 0;
        columnaActual = columna;
    }


    imagenActual.y = columna;
    if(movimiento.x != 0){
        totalTime += deltaTime;
        if(totalTime >= switchTime){
                totalTime -= switchTime;
                imagenActual.x++;
                if(imagenActual.x >= contadorImagen.x){
                    imagenActual.x = 0;
                }
        }
    }else{
        imagenActual.x = 0;
    }



    uvRect.top = imagenActual.y * uvRect.height;
    if(cambio == true){
        uvRect.left = (imagenActual.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);

    }else{
        uvRect.left = imagenActual.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }

    personaje.setTextureRect(uvRect);
    Ventana::getInstancia()->firstpos += movimiento;
}

void Personaje::jump(){

    sf::Vector2f movimiento(0.0f, 0.0f); //se cambia segun s pulsas dcha izq etz, se va actualizando
    float deltaTime = Ventana::getInstancia()->delta;


    if(!saltando){
        velocidadPersonaje.x = 0;
        velocidadPersonaje.y = 0;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !saltando){
        velocidadPersonaje.y=-velSalto;
        saltando=true;
        imagenActual2.x = 0;
    }
    if(saltando){
        velocidadPersonaje.y+=(gravedad*deltaTime);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            velocidadPersonaje.x -= velSaltoHor * deltaTime;
            cambio = true;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            velocidadPersonaje.x += velSaltoHor * deltaTime;
            cambio = false;
        }
    }

    imagenActual2.y = 0;
    totalTime2 += deltaTime;

    if(totalTime2 >= switchTime){
        totalTime2 -= switchTime;
        imagenActual2.x++;
        if(imagenActual2.x >= contadorImagen2.x-2){
            imagenActual2.x = 1;
        }
    }

    uvRect.top = imagenActual2.y * uvRect.height;
    if(cambio == false){
        uvRect.left = imagenActual2.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }else{
        uvRect.left = (imagenActual2.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }

    personaje.setTextureRect(uvRect);

    movimiento=velocidadPersonaje*deltaTime;
    Ventana::getInstancia()->firstpos += movimiento;

}

void Personaje::disparo(){

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            disparando = true;
    }else{
        disparando=false;
    }

}

void Personaje::choque(sf::Vector2f posEnemigo){


    sf::Vector2f movimiento(0.0f, 0.0f); //se cambia segun s pulsas dcha izq etz, se va actualizando
    float deltaTime = Ventana::getInstancia()->delta;

        if(posEnemigo.x < personaje.getPosition().x){
                velocidadChoque.x=35000;
        }else if(posEnemigo.x > personaje.getPosition().x) {
                velocidadChoque.x=-35000;
        }
    imagenActual3.y = 2;
    totalTime3 += deltaTime;

    if(totalTime3 >= switchTime){
        totalTime3 -= switchTime;
        imagenActual3.x++;
        if(imagenActual3.x >= contadorImagen3.x-2){
            imagenActual3.x = 1;
        }
    }

    uvRect.top = imagenActual3.y * uvRect.height;
    if(cambio == false){
        uvRect.left = imagenActual3.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }else{
        uvRect.left = (imagenActual3.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }

    personaje.setTextureRect(uvRect);
    movimiento=velocidadChoque*deltaTime;
    Ventana::getInstancia()->firstpos += movimiento;
    chocando=false;


}

void Personaje::colisionMapa(sf::Vector2f posicionRectangulo, sf::FloatRect shapeRectangulo){

sf::Vector2f movimiento(0.0f, 0.0f);
    float deltaTime = Ventana::getInstancia()->delta;

        if(personaje.getPosition().x<posicionRectangulo.x){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                velocidadPer.x -= vel * deltaTime;
                cambio = true;
                colisionando=false;
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    velocidadPer.x = 0;
                    cambio = false;
                    colisionando=true;
            }
        }else{
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                velocidadPer.x = 0;
                cambio = true;
                colisionando=true;
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                velocidadPer.x += vel * deltaTime;
                cambio = false;
                colisionando=false;
            }
        }

        if(personaje.getPosition().y<237){
            personaje.setPosition({personaje.getPosition().x, 106});
            saltando=false;
            colisionando=false;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                velocidadPer.x -= vel * deltaTime;
                cambio = true;
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                velocidadPer.x += vel * deltaTime;
                cambio = false;
            }
        }else{
            colisionando=true;
        }

    uvRect.top = imagenActual2.y * uvRect.height;
    if(cambio == false){
        uvRect.left = imagenActual2.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }else{
        uvRect.left = (imagenActual2.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }

    personaje.setTextureRect(uvRect);

    movimiento=velocidadPer*deltaTime;
    Ventana::getInstancia()->firstpos += movimiento;

}

Personaje::~Personaje()
{
    //dtor
}
