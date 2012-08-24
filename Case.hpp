#ifndef CASE_HPP_INCLUDED
#define CASE_HPP_INCLUDED

#include "Structures.hpp"

class Case
{
   public:
        Case(sf::RenderWindow* _app);
        bool setTuile(Couche, sf::Texture&);

        void setPosition(int x, int y);
        Position& getMapPosition();
        Position& getPosition();

        void setBloquante(bool Block);
        bool isBloquante();
        bool draw();

        Case& getCase();
    private:
        sf::RenderWindow* _app;
        Position _pos;
        Position _mapPos;
        bool _bloquante;
        sf::Sprite _devant, _derriere;

};

#endif // CASE_HPP_INCLUDED
