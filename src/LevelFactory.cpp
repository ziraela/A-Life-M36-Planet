#include "LevelFactory.h"
#include <iostream>
#include <cstring>
#include "TileMap.h"
#include "Ventana.h"
#include "tinyxml2.h"

LevelFactory::LevelFactory()
{
    nivel = 6;
}

void LevelFactory::inicializar(){

    switch (nivel){
        case 1:
            cadena = "mapas/tilemaps/5izq.xml";
            imagen = "mapas/tilesheet.png";
            break;
        case 2:
            cadena = "mapas/tilemaps/4izq.xml";
            imagen = "mapas/tilesheet.png";
            break;
        case 3:
            cadena = "mapas/tilemaps/3izq.xml";
            imagen = "mapas/tilesheet.png";
            break;
        case 4:
            cadena = "mapas/tilemaps/2izq.xml";
            imagen = "mapas/tilesheet.png";
            break;
        case 5:
            cadena = "mapas/tilemaps/1izq.xml";
            imagen = "mapas/tilesheet.png";
            break;
        case 6:
            cadena = "mapas/tilemaps/centro.xml";
            imagen = "mapas/tilesheet.png";
            break;
        case 7:
            cadena = "mapas/tilemaps/1dcha.xml";
            imagen = "mapas/tilesheet.png";
            break;
        case 8:
            cadena = "mapas/tilemaps/1add.xml";
            imagen = "mapas/tilesheet.png";
            break;
        case 9:
            cadena = "mapas/tilemaps/2add.xml";
            imagen = "mapas/tilesheet.png";
            break;
        case 10:
            cadena = "mapas/tilemaps/3add.xml";
            imagen = "mapas/tilesheet.png";
            break;
        case 11:
            cadena = "mapas/tilemaps/4add.xml";
            imagen = "mapas/tilesheet.png";
            break;
        case 12:
            cadena = "mapas/tilemaps/2dcha.xml";
            imagen = "mapas/tilesheet.png";
            break;
        case 13:
            cadena = "mapas/tilemaps/3dcha.xml";
            imagen = "mapas/tilesheet.png";
            break;
        case 14:
            cadena = "mapas/tilemaps/4dcha.xml";
            imagen = "mapas/tilesheet.png";
            break;
        case 15:
            cadena = "mapas/tilemaps/5dcha.xml";
            imagen = "mapas/tilesheet.png";
            break;
    }

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError result = doc.LoadFile( cadena.c_str() );

    if (result != tinyxml2::XML_SUCCESS) {
        std::cerr << "Error cargando la imagen";
        exit(0);
        }

    tinyxml2::XMLElement *element = doc.FirstChildElement("map");
    std::string gid;
    std::string gid2;
    int width = std::stoi(element->Attribute("width"));
    int height = std::stoi(element->Attribute("height"));
    int gids [width*height];
    int gids2 [width*height];
    int i = 0;

    element = doc.FirstChildElement("map")->FirstChildElement("layer")->FirstChildElement("data");
    for(tinyxml2::XMLElement* child=element->FirstChildElement(); child != NULL; child=child->NextSiblingElement())
    {
        gid = child->Attribute("gid");
        gids[i] = std::stoi(gid)-1;
        ++i;
    }
    i=0;
    element = doc.FirstChildElement("map")->FirstChildElement("layer");
    element = element->NextSiblingElement("layer")->FirstChildElement("data");
    for(tinyxml2::XMLElement* child2=element->FirstChildElement(); child2 != NULL; child2=child2->NextSiblingElement())
    {
        gid2 = child2->Attribute("gid");
        gids2[i] = std::stoi(gid2)-1;
        ++i;
    }
    i=0;
    element = doc.FirstChildElement("map")->FirstChildElement("layer");
    element = element->NextSiblingElement("layer");
    element = element->NextSiblingElement("layer")->FirstChildElement("data");
    for(tinyxml2::XMLElement* child2=element->FirstChildElement(); child2 != NULL; child2=child2->NextSiblingElement())
    {
        gid2 = child2->Attribute("gid");
        ++i;
    }


   if (!map.load(imagen.c_str(), sf::Vector2u(32, 32), gids, width, height))
        std::cerr << "Error cargando el mapa1";

    if (!map2.load(imagen.c_str(), sf::Vector2u(32, 32), gids2, width, height))
        std::cerr << "Error cargando el mapa2";

}


void LevelFactory::pintarse(){

    Ventana::getInstancia()->window.draw(map);
    Ventana::getInstancia()->window.draw(map2);
}

LevelFactory::~LevelFactory()
{
    //dtor
}
