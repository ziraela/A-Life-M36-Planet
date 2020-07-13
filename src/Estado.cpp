#include "Estado.h"
#include <iostream>
#include <string>
#include "Juego.h"

Estado::Estado()
{

}

void Estado::setEstado(int x){
    estado = x;
}

void Estado::comprobador(){
    switch (estado){
        case 1:

            break;
        case 2:
            juego.inicializar();
            break;

    }
}

void Estado::controlador(){
    switch (estado){
        case 1:

            break;
        case 2:
            if(!juego.getCasiMuerto()){
                juego.getPersonaje().jump();
                if(!juego.getPersonaje().getSaltando() && !juego.getPersonaje().getChocando() && !juego.getPersonaje().getColisionando()){
                    juego.getPersonaje().moverse();
                }
            }
                juego.getPersonaje().disparo();
                juego.enemigosColision();
                juego.balasColision();
                juego.rectanguloColision();
                juego.puertaColision();

            break;
    }
}


void Estado::render(){

    switch (estado){
        case 1:

            break;
        case 2:
            juego.render();
            break;

    }

}

Estado::~Estado()
{
    //dtor
}
