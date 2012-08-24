#include "Entite.hpp"
#include <iostream>

Entite::Entite(sf::RenderWindow* app, sf::Texture& texture ,int x, int y) : _app(app)
{
    _image.setTexture(texture);
    _image.setOrigin(_image.getLocalBounds().width / 2,_image.getLocalBounds().height / 2);
    _pos.x = x;
    _pos.y = y;
    _image.setPosition(x + _image.getLocalBounds().width / 2, y + _image.getLocalBounds().height / 2);
}

void Entite::setCouche(Couche pcouche)
{
    if(pcouche == DEVANT)
        _couche = pcouche;
    else if(pcouche == DERRIERE)
    {
        _couche = pcouche;
        _image.setColor(sf::Color(150,150,150,255));
    }
}

void Entite::scale(float coef)
{
    _image.setScale(_image.getScale().x + coef, _image.getScale().y + coef);
}

void Entite::rotation(int coef)
{
    _image.rotate(coef * 10);
}

void Entite::setPosition(int x,int y)
{
    _pos.x = x;
    _pos.y = y;


    _image.setPosition(x,y);
}

bool Entite::isHover(sf::Vector2f posMouse)
{
    if(posMouse.x > _pos.x && posMouse.x < _pos.x + _image.getGlobalBounds().width && posMouse.y > _pos.y && posMouse.y < _pos.y + _image.getGlobalBounds().height)
    {
         return true;

    }
    else
        return false;
}
void Entite::setBloquant(bool block)
{
    _bloquant = block;
}
bool Entite::isBloquant()
{
    return _bloquant;
}

void Entite::draw()
{
    _app->draw(_image);
}




