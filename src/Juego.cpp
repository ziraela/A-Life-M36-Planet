#include "Juego.h"
#include "Personaje.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Mundo.h"
#include "Ventana.h"
#include "Texto.h"
#include "Bala.h"
using namespace std;
Juego::Juego()
{
    //ctor
}


void Juego::inicializar()
{
    Ventana::getInstancia()->factory.inicializar();
    posicionInicio= (sf::Vector2f(640/2, 480/2));
    if(cambioNivelIzq==true){
            posicionInicio=(sf::Vector2f(640, 480/2));
        cambioNivelIzq=false;
    }else if(cambioNivelDcha==true){
            posicionInicio=(sf::Vector2f(0, 480/2));
        cambioNivelDcha=false;
    }
    else if(entroLaboratorio==true){
        posicionInicio=(sf::Vector2f(0, 480/2));
        entroLaboratorio=false;
        }
    else if(salgoLaboratorio==true){
        posicionInicio=(sf::Vector2f(485, 480/2));
        salgoLaboratorio=false;
    }
    personaje.cargar(posicionInicio);

    if(fact.getNivel()==7){
        puerta= new Puerta;
        puerta->Crear();
        puertaDone=true;
    }

    Rectangulos();
    int colisionBalaCont=0;
    cargar();

}

void Juego::cargar(){
            textoLife= new Texto();
            textoExp= new Texto();
            textoNil= new Texto();
            textoCogerMoneda= new Texto();
            textoModoDios= new Texto();
            textoGameOver= new Texto();
}

void Juego::render()
{


    Ventana::getInstancia()->factory.pintarse();
    personaje.getPersonaje().setPosition(Ventana::getInstancia()->lastpos*(1-Ventana::getInstancia()->percent) + Ventana::getInstancia()->firstpos*Ventana::getInstancia()->percent);

    if(personaje.getChocando()){
            personaje.choque(sf::Vector2f(posicionEnColision.x, posicionEnColision.y));

    }

        if(personaje.getPersonaje().getPosition().y>Ventana::getInstancia()->window.getSize().y /2){
            personaje.getPersonaje().setPosition({personaje.getPersonaje().getPosition().x,Ventana::getInstancia()->window.getSize().y /2});
            personaje.setSaltando(false);
        }


    if(fact.getNivel() !=7 && puertaDone==true){
        delete puerta;
        puertaDone=false;
    }


    if(puertaDone==true){
        Ventana::getInstancia()->window.draw(puerta->getPuerta());
    }

    ///BALA///
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && casiMuerto==false){
            disparin=true;
            cont++;
    }else{
        disparin=false;
        cont=0;
    }
    if(disparin==true && cont==8){
        bulleto= new Bala;
        bulleto->Crear(personaje.getPersonaje().getPosition(), personaje.getCambio());
        bulletVec.push_back(bulleto);
        personaje.setDisparando(false);
    }

        for (int i=0; i<bulletVec.size(); i++){
                    if(bulletVec[i]->getBala().getPosition().x < 0 || bulletVec[i]->getBala().getPosition().x > 680){
                        bulletActual= new Bala;
                        bulletActual=bulletVec[i];

                        bulletVec.erase(bulletVec.begin() + i);
                        delete bulletActual;
                    }
        }

        for(int i=0; i<bulletVec.size(); i++){
            Ventana::getInstancia()->window.draw(bulletVec[i]->getBala());
            bulletVec[i]->fire();

        }

    ///ENEMIGOS///
    //float pushTime = Ventana::getInstancia()->push;
        sf::Time elapsed=clockEn.getElapsedTime();


    if(elapsed.asSeconds()>1 && contadorAparecido < 1){
        int v1 = rand() % 640 + 1;

        int posi=260;
        if((fact.getNivel()==12 && v1>250) || (fact.getNivel()==14 && v1>250)){
            posi=230;
        }

        if(fact.getNivel()==6 || fact.getNivel()==5 || fact.getNivel()==7){
            tipoEn=3;
        }else if (fact.getNivel()==3 || fact.getNivel()==4 || fact.getNivel()==8 || fact.getNivel()==9 || fact.getNivel()==10 || fact.getNivel()==11){
            tipoEn=rand()% 2 + 1;
            if(tipoEn==1){
                tipoEn=3;
            }else{
                tipoEn=2;
            }
            //tipoEn = sf::Randomizer::Random(2, 3);
        }else if(fact.getNivel()==2 || fact.getNivel()==1){
            tipoEn=rand()% 3 + 1;
                        //tipoEn = sf::Randomizer::Random(1, 3);

        }else if(fact.getNivel()==12 || fact.getNivel()==13){
            tipoEn=rand()% 4 + 3;
                        //tipoEn = sf::Randomizer::Random(3, 4);

        }else if(fact.getNivel()==14 || fact.getNivel()==15){
            tipoEn=rand() % 5 + 3;
                        //tipoEn = sf::Randomizer::Random(3, 5);
        }
        if(tipoEn==2 || tipoEn==1){
            posi=0;
        }

        if(tipoEn==5){
            posi=90;
        }

        enemigo= new Enemigos;
        enemigo->Cargar(sf::Vector2f(v1, posi), tipoEn);
        enemigosNuevos.push_back(enemigo);
        contadorAparecido++;
        creado=true;

    }
    if(elapsed.asSeconds()>2){
        clockEn.restart().asSeconds();
        contadorAparecido=0;
    }

    if(enemigosNuevos.size()!=0){
        creado=true;
    }else{
        creado=false;
    }


    for(int i=0; i<enemigosNuevos.size(); i++){
        if(enemigosNuevos[i]->getEnemigosSprite().getPosition().x<personaje.getPersonaje().getPosition().x){
                mayor=true;
        }else if(enemigosNuevos[i]->getEnemigosSprite().getPosition().x>personaje.getPersonaje().getPosition().x){
                mayor=false;
        }
            enemigosNuevos[i]->movimiento(personaje.getPersonaje().getPosition(), i, mayor);

            if((enemigosNuevos[i]->getEnemigosSprite().getPosition().y>260 && enemigosNuevos[i]->getTipo()==2) || (enemigosNuevos[i]->getEnemigosSprite().getPosition().y>260 && enemigosNuevos[i]->getTipo()==1)){
                enemigosNuevos[i]->getEnemigosSprite().setPosition(sf::Vector2f({enemigosNuevos[i]->getEnemigosSprite().getPosition().x, 260}));
            }

            Ventana::getInstancia()->window.draw(enemigosNuevos[i]->getEnemigosSprite());
        }

        for (int i=0; i<enemigosNuevos.size(); i++){
                    if(enemigosNuevos[i]->getEnemigosSprite().getPosition().y < 0){
                        enemigoActual= new Enemigos;
                        enemigoActual=enemigosNuevos[i];
                        enemigosNuevos.erase(enemigosNuevos.begin() + i);
                        delete enemigoActual;
                    }
        }

        ///FIN DE ENEMIGOS Y BALAS///


        ///reiniciar level factory///
        if(fact.getNivel()==1 && personaje.getPersonaje().getPosition().x<5){
            personaje.getPersonaje().setPosition({0.f, personaje.getPersonaje().getPosition().y});
        }


        if(personaje.getPersonaje().getPosition().x > 685 && fact.getNivel()!=11){
         Ventana::getInstancia()->factory.cambiarNivel();
         Ventana::getInstancia()->lastpos.x = 0.0f;
         Ventana::getInstancia()->lastpos.y = 0.0f;
         fact.setNivel(fact.getNivel()+1);
         cambioNivelDcha=true;
            for(int i=0; i<enemigosNuevos.size(); i++){
                enemigoActual=new Enemigos;
                enemigoActual=enemigosNuevos[i];
                delete enemigoActual;
                i++;
            }
            enemigosNuevos.erase(enemigosNuevos.begin(), enemigosNuevos.end());
            rectangulos.erase(rectangulos.begin(), rectangulos.end());
            deleteMoneda();
            if(bulletVec.size()!=0){
                    deleteBala();
                }
         this->inicializar();
        }
        else if(personaje.getPersonaje().getPosition().x < 0 && fact.getNivel()!=1 && fact.getNivel()!= 12){
         Ventana::getInstancia()->factory.cambiarNivelIzq();
         Ventana::getInstancia()->lastpos.x = 0.0f;
         Ventana::getInstancia()->lastpos.y = 0.0f;
         fact.setNivel(fact.getNivel()-1);
         cambioNivelIzq=true;
         for(int i=0; i<enemigosNuevos.size(); i++){
                enemigoActual=new Enemigos;
                enemigoActual=enemigosNuevos[i];
                delete enemigoActual;
                i++;
            }
            enemigosNuevos.erase(enemigosNuevos.begin(), enemigosNuevos.end());
            rectangulos.erase(rectangulos.begin(), rectangulos.end());
            deleteMoneda();
            if(bulletVec.size()!=0){
                    deleteBala();
                }
         this->inicializar();
        }

        else if(fact.getNivel()==7 && laboratorio==true){
             Ventana::getInstancia()->factory.cambiarLaboratorio();
             Ventana::getInstancia()->lastpos.x = 0.0f;
             Ventana::getInstancia()->lastpos.y = 0.0f;
             fact.setNivel(fact.getNivel()+5);
             entroLaboratorio=true;
             for(int i=0; i<enemigosNuevos.size(); i++){
                    enemigoActual=new Enemigos;
                    enemigoActual=enemigosNuevos[i];
                    delete enemigoActual;
                    i++;
                }
                enemigosNuevos.erase(enemigosNuevos.begin(), enemigosNuevos.end());
                rectangulos.erase(rectangulos.begin(), rectangulos.end());
                deleteMoneda();

                if(bulletVec.size()!=0){
                    deleteBala();
                }
             this->inicializar();
        }
        else if(fact.getNivel()==12 && personaje.getPersonaje().getPosition().x < 0 && laboratorio==true){
             Ventana::getInstancia()->factory.salirLaboratorio();
             Ventana::getInstancia()->lastpos.x = 0.0f;
             Ventana::getInstancia()->lastpos.y = 0.0f;
             fact.setNivel(fact.getNivel()-5);
             laboratorio=false;
             salgoLaboratorio=true;
             for(int i=0; i<enemigosNuevos.size(); i++){
                    enemigoActual=new Enemigos;
                    enemigoActual=enemigosNuevos[i];
                    delete enemigoActual;
                    i++;
                }
                enemigosNuevos.erase(enemigosNuevos.begin(), enemigosNuevos.end());
                rectangulos.erase(rectangulos.begin(), rectangulos.end());
                deleteMoneda();
                if(bulletVec.size()!=0){
                    deleteBala();
                }
             this->inicializar();
        }

        else if(fact.getNivel()==11 && personaje.getPersonaje().getPosition().x > 685){
        Ventana::getInstancia()->factory.mantenerNivel();
         Ventana::getInstancia()->lastpos.x = 0.0f;
         Ventana::getInstancia()->lastpos.y = 0.0f;
         //fact.setNivel(fact.getNivel()+1);
         //cambioNivelDcha=true;
            for(int i=0; i<enemigosNuevos.size(); i++){
                enemigoActual=new Enemigos;
                enemigoActual=enemigosNuevos[i];
                delete enemigoActual;
                i++;
            }
            enemigosNuevos.erase(enemigosNuevos.begin(), enemigosNuevos.end());
            rectangulos.erase(rectangulos.begin(), rectangulos.end());
            deleteMoneda();
            if(bulletVec.size()!=0){
                    deleteBala();
                }
         this->inicializar();
        }

    Ventana::getInstancia()->window.draw(personaje.getPersonaje());
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
        modoDios=true;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::G) && modoDios==true){
        modoDios=false;
    }
    dibujarHud();

}


void Juego::Rectangulos(){

        RectangleShape r1, r2, r3, r4;
        rectangulos.push_back(r1);
        rectangulos.push_back(r2);
        rectangulos.push_back(r3);
        rectangulos.push_back(r4);

        if(fact.getNivel()==12){
            valido0=true;
            valido1=false;
            valido2=false;
            valido3=false;

        }else if(fact.getNivel()==14){
            valido0=false;
            valido1=true;
            valido2=false;
            valido3=false;

        }else if(fact.getNivel()==13){
            valido0=false;
            valido1=false;
            valido2=true;
            valido3=false;

        }else if(fact.getNivel()==15){
            valido0=false;
            valido1=false;
            valido2=false;
            valido3=true;

        }else{
            valido0=false;
            valido1=false;
            valido2=false;
            valido3=false;
        }
        rectangulos[0].Crear(sf::Vector2f({450, 260}), valido0, 1);
        rectangulos[1].Crear(sf::Vector2f({620, 260}), valido1, 1);
        rectangulos[2].Crear(sf::Vector2f({210, 250}), valido3, 3);
        rectangulos[3].Crear(sf::Vector2f({200, 260}), valido2, 2);
}


void Juego::dibujarHud(){

    textoLife->Asignar(sf::Vector2f(640/4, 480/1.5), "LIFE", life);
    textoExp->Asignar(sf::Vector2f(640/4, 480/1.4), "EXP", exp);
    textoNil->Asignar(sf::Vector2f(640/4, 480/1.3), "NIL", nil);
    textoCogerMoneda->Asignar2(sf::Vector2f(640/1.5, 480/1.5), nilinfo, " N");



    if(modoDios==true){
        textoModoDios->Asignar4(sf::Vector2f(640/1.5, 480/1.3), "MODO DIOS ACTIVADO,\n LOS ENEMIGOS NO RESTARAN\n VIDA ");
        Ventana::getInstancia()->window.draw(textoModoDios->getTexto());
    }

    sf::Time elapsedMoneda=clockMon.getElapsedTime();
    sf::Time elapsedFin=clockFin.getElapsedTime();

    Ventana::getInstancia()->window.draw(textoLife->getTexto());
    Ventana::getInstancia()->window.draw(textoExp->getTexto());
    Ventana::getInstancia()->window.draw(textoNil->getTexto());

    if(life<1){
        if(life < 0){
            life=0;
        }
        textoGameOver->Asignar3(sf::Vector2f(640/2, 160), "GAME\n OVER");
        Ventana::getInstancia()->window.draw(textoGameOver->getTexto());
        casiMuerto=true;
        if(elapsedFin.asSeconds() > 7){
        }

    }





    if(elapsedMoneda.asSeconds()<3 && monedaCogida==true){
            Ventana::getInstancia()->window.draw(textoCogerMoneda->getTexto());
            monedaCogida==false;
        }

if(monedahecha==true){

    for(int i=0; i<monedas.size(); i++){
            Ventana::getInstancia()->window.draw(monedas[i]->getMoneda());
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        monedasColision();
    }
}

}

void Juego::deleteMoneda(){

        for(int i=0; i<monedas.size(); i++){
                    monedaActual=new Moneda;
                    monedaActual=monedas[i];
                    delete monedaActual;
                    i++;
                }
                monedas.erase(monedas.begin(), monedas.end());
}

void Juego::deleteBala(){

    for (int i=0; i<bulletVec.size(); i++){
                    bulletActual=new Bala;
                    bulletActual=bulletVec[i];
                    delete bulletActual;
                    i++;
                }
                bulletVec.erase(bulletVec.begin(), bulletVec.end());
}

void Juego::rectanguloColision(){

    for(int i=0; i<rectangulos.size(); i++){
            if(rectangulos[i].getValido()){
                sf::FloatRect shapeRectangulo = rectangulos[i].getRectangle().getGlobalBounds();
                sf::Vector2f posicionRectangule=rectangulos[i].getRectangle().getPosition();
                sf::FloatRect shapePersonaje = personaje.getPersonaje().getGlobalBounds();
                if(personaje.getPersonaje().getPosition().x > posicionRectangule.x-shapeRectangulo.width/2 &&
                        personaje.getPersonaje().getPosition().x < posicionRectangule.x+shapeRectangulo.width/2 &&
                        personaje.getPersonaje().getPosition().y+shapePersonaje.height > posicionRectangule.y+shapeRectangulo.height/2 &&
                        personaje.getPersonaje().getPosition().y-shapePersonaje.height < posicionRectangule.y-shapeRectangulo.height/2){
                             colisionRect=true;
                             personaje.colisionMapa(posicionRectangule, shapeRectangulo);
                }else{
                   colisionRect=false;
                   personaje.setSaltando(true);
                   //personaje.getPersonaje().setPosition({personaje.getPersonaje().getPosition().x, 480/2});
                }


                if(creado==true){

                     for(int j=0; j<enemigosNuevos.size(); j++){

                    sf::FloatRect shapeEnemigo =enemigosNuevos[j]->getEnemigosSprite().getGlobalBounds();
                    sf::Vector2f posicionEnemigo=enemigosNuevos[j]->getEnemigosSprite().getPosition();

                        if(posicionEnemigo.x > posicionRectangule.x-shapeRectangulo.width/2 &&
                        posicionEnemigo.x < posicionRectangule.x+shapeRectangulo.width/2 &&
                        posicionEnemigo.y+shapeEnemigo.height > posicionRectangule.y-50+shapeRectangulo.height/2 &&
                        posicionEnemigo.y-shapeEnemigo.height < posicionRectangule.y+50-shapeRectangulo.height/2
                        ){
                             //colisionRect=true;
                             enemigosNuevos[j]->colisionMapa(posicionRectangule, shapeRectangulo, mayor);
                        }else{
                            if(enemigosNuevos[j]->getEnemigosSprite().getPosition().y<240 && enemigosNuevos[j]->getTipo()!= 5){
                                enemigosNuevos[j]->getEnemigosSprite().setPosition({enemigosNuevos[j]->getEnemigosSprite().getPosition().x, 255});
                            }
                            //colisionRect=false;
                            //personaje.setSaltando(true);
                   //personaje.getPersonaje().setPosition({personaje.getPersonaje().getPosition().x, 480/2});
                        }
                    }

                }


            }
        }







}



void Juego::enemigosColision(){

        for(int i=0; i<enemigosNuevos.size(); i++){
            sf::FloatRect shapeEnemigo =enemigosNuevos[i]->getEnemigosSprite().getGlobalBounds();
            sf::Vector2f posicionEnemigo=enemigosNuevos[i]->getEnemigosSprite().getPosition();
            sf::FloatRect shapePersonaje = personaje.getPersonaje().getGlobalBounds();
            if(personaje.getPersonaje().getPosition().x > posicionEnemigo.x-shapeEnemigo.width/2 &&
                    personaje.getPersonaje().getPosition().x < posicionEnemigo.x+shapeEnemigo.width/2 &&
                    personaje.getPersonaje().getPosition().y+shapePersonaje.height/2 > posicionEnemigo.y-25+shapeEnemigo.height/2 &&
                    personaje.getPersonaje().getPosition().y-shapePersonaje.height/2 < posicionEnemigo.y+25-shapeEnemigo.height/2){
                        colisionEnemigo = true;
                        colisionEnemigoCont++;
                        personaje.setChocando(true);
                        if(enemigosNuevos[i]->getTipo()==2 || enemigosNuevos[i]->getTipo()==1){
                            enemigosNuevos[i]->choque();
                        }

                        posicionEnColision.x=posicionEnemigo.x;
                        posicionEnColision.y=posicionEnemigo.y;
                        if(modoDios==false){
                            if(enemigosNuevos[i]->getTipo()==3 || enemigosNuevos[i]->getTipo()==2){
                                life=life-1;
                            }else if(enemigosNuevos[i]->getTipo()==1){
                                life=life-4;
                            }else{
                                life=life-2;
                            }
                        }

            }else{
                colisionEnemigo = false;

            }
        }

}

void Juego::monedasColision(){

  for(int i=0; i<monedas.size(); i++){
            sf::FloatRect shapeMondeda =monedas[i]->getMoneda().getGlobalBounds();
            sf::Vector2f posicionMoneda=monedas[i]->getMoneda().getPosition();
            sf::FloatRect shapePersonaje = personaje.getPersonaje().getGlobalBounds();

            if(personaje.getPersonaje().getPosition().x > posicionMoneda.x-shapeMondeda.width/2 &&
                    personaje.getPersonaje().getPosition().x < posicionMoneda.x+shapeMondeda.width/2 &&
                    personaje.getPersonaje().getPosition().y+shapePersonaje.height/2 > posicionMoneda.y+shapeMondeda.height/2 &&
                    personaje.getPersonaje().getPosition().y-shapePersonaje.height/2 < posicionMoneda.y-shapeMondeda.height/2){
                    monedaActual= new Moneda;
                    monedaActual=monedas[i];
                    tipoEnMuerto=monedaActual->getTipoEnemigo();
                    monedas.erase(monedas.begin() + i);
                    delete monedaActual;

                    int ran=10;
                    if(tipoEnMuerto==3 || tipoEnMuerto==4){
                        ran=rand() % 6 + 1;
                    }else if(tipoEnMuerto==2){
                        int ran=rand() % 20 + 6;
                    }else if(tipoEnMuerto==1){
                        int ran=rand() % 29 + 16;
                    }else{
                        int ran=30;
                    }

                    nilinfo=ran;
                    nil=nil+ran;
                    clockMon.restart().asSeconds();
                    monedaCogida=true;


            }else{
                //colisionEnemigo = false;

            }
        }

}

void Juego::puertaColision(){

    if(puertaDone==true){
        sf::FloatRect shapePuerta =puerta->getPuerta().getGlobalBounds();
                sf::Vector2f posicionPuerta=puerta->getPuerta().getPosition();
                sf::FloatRect shapePersonaje = personaje.getPersonaje().getGlobalBounds();

                if(personaje.getPersonaje().getPosition().x > posicionPuerta.x-shapePuerta.width/2 &&
                        personaje.getPersonaje().getPosition().x < posicionPuerta.x+shapePuerta.width/2 &&
                        personaje.getPersonaje().getPosition().y+shapePersonaje.height/2 > posicionPuerta.y+shapePuerta.height/2 &&
                        personaje.getPersonaje().getPosition().y-shapePersonaje.height/2 < posicionPuerta.y-shapePuerta.height/2){
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                                laboratorio=true;
                            }
                }else{

                }

    }


}

void Juego::balasColision(){

            ///LLAMO DESDE BALA///

        if(bulletVec.size()>0){
            for(int j=0; j<bulletVec.size(); j++){
                sf::FloatRect shapeBala =bulletVec[j]->getBala().getGlobalBounds();
                sf::Vector2f posicionBala=bulletVec[j]->getBala().getPosition();

                    for (int i=0; i<enemigosNuevos.size(); i++){

                        sf::FloatRect shapeEnemigo = enemigosNuevos[i]->getEnemigosSprite().getGlobalBounds();

                            if(posicionBala.x > enemigosNuevos[i]->getEnemigosSprite().getPosition().x-shapeEnemigo.width/2 &&
                                posicionBala.x < enemigosNuevos[i]->getEnemigosSprite().getPosition().x+shapeEnemigo.width/2 &&
                                posicionBala.y+shapeBala.height/2 < enemigosNuevos[i]->getEnemigosSprite().getPosition().y+50+shapeEnemigo.height/2 &&
                                posicionBala.y-shapeBala.height/2 > enemigosNuevos[i]->getEnemigosSprite().getPosition().y-50-shapeEnemigo.height/2){

                                    ///ELIMINACION DE BALA///
                                    colisionBala = true;
                                    colisionBalaCont ++;
                                    bulletActual= new Bala;
                                    bulletActual=bulletVec[j];

                                    bulletVec.erase(bulletVec.begin() + j);
                                    delete bulletActual;
                                if(colisionBalaCont==3){

                                    sf::Vector2f posicionNueva = enemigosNuevos[i]->getEnemigosSprite().getPosition();
                                    enemigoActual=new Enemigos;
                                    enemigoActual=enemigosNuevos[i];
                                    tipoEn=enemigoActual->getTipo();

                                    enemigosNuevos.erase(enemigosNuevos.begin() + i);
                                    delete enemigoActual;
                                    exp=exp-2;
                                    colisionBalaCont=0;

                                    int monedaRan=rand() % 3 + 1;

                                    if(monedaRan==2){
                                        moneda=new Moneda;
                                        moneda->Cargar(posicionNueva);
                                        moneda->setTipoEnemigo(tipoEn);
                                        monedahecha=true;
                                        monedas.push_back(moneda);
                                    }
                                }

                            }else{
                                colisionBala = false;
                            }
                    }
            }
        }

}


Juego::~Juego()
{
    //dtor
    //delete bulleto;
}
