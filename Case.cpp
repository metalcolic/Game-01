#include "Case.hpp"
#include <iostream>



Case::Case(sf::RenderWindow* app) : _app(app)
{
    _bloquante = false;
}
bool Case::setTuile(Couche couche, sf::Texture& ressource)
{
    if(couche == DERRIERE)
    {
        _derriere.setTexture(ressource);
        return true;
    }
    else if(couche == DEVANT)
    {
        _devant.setTexture(ressource);
        return true;
    }

    return false;
}

void Case::setPosition(int x, int y)
{
    if(x >= 0 && y >= 0)
    {
        _mapPos.x = x / TILE_WIDTH;
        _mapPos.y = y / TILE_HEIGHT;

        _pos.x = _mapPos.x * TILE_WIDTH;
        _pos.y = _mapPos.y * TILE_HEIGHT;

        _derriere.setPosition(_pos.x, _pos.y);
        _devant.setPosition(_pos.x, _pos.y);
    }
}

Position& Case::getMapPosition()
{
    return _mapPos;
}

Position& Case::getPosition()
{
    return _pos;
}

void Case::setBloquante(bool Block)
{
    _bloquante = Block;

}
bool Case::isBloquante()
{
    return _bloquante;
}
bool Case::draw()
{
    _app->draw(_derriere);
    _app->draw(_devant);


    return true;
}

Case& Case::getCase()
{
    return *this;
}
