#ifndef STRUCTURES_HPP_INCLUDED
#define STRUCTURES_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Map;
class EventEngine;

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1)))
#define ABS(X) ((((X)<0)?(-(X)):(X)))



enum Couche{DEVANT,DERRIERE, AUCUNE};

enum Etat{ARRET, DROITE, GAUCHE, ECHELLE, SAUT};

struct Position
{
    int x;
    int y;
};

struct Dimensions
{
    int width;
    int height;
};

struct Tile
{
    sf::Sprite image;
};

struct KeyboardState
{
    bool Escape;
    bool LControl;
    bool left;
    bool right;
    bool space;
    bool up;
    bool down;

    KeyboardState()
    {
        Escape = false;
        LControl = false;
        left = false;
        right = false;
        space = false;
        up = false;
        down = false;
    }

};

struct MouseState
{
    bool left;
    bool right;
    bool middle;

    MouseState(){
    left = false;
    right = false;
    middle = false;
    }
};




#endif // STRUCTURES_HPP_INCLUDED
