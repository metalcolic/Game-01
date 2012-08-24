#ifndef ENTITE_HPP_INCLUDED
#define ENTITE_HPP_INCLUDED

#include "Structures.hpp"
#include <SFML/Graphics.hpp>

class Entite
{
    public:
        Entite(sf::RenderWindow* app, sf::Texture& text, int x, int y);

        void setCouche(Couche pcouche);
        void rotation(int);
        void scale(float);

        void setPosition(int,int);
        void setBloquant(bool );
        bool isBloquant();
        bool isHover(sf::Vector2f posMouse);

        void draw();
    private:
        sf::RenderWindow* _app;
        Position _pos;
        bool _bloquant;
        sf::Sprite _image;
        Couche _couche;


};

#endif // ENTITE_HPP_INCLUDED
