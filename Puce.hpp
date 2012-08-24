#ifndef PUCE_HPP_INCLUDED
#define PUCE_HPP_INCLUDED


#include "Structures.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include "Game.hpp"
#include "EventEngine.hpp"
#include "RessourceManager.hpp"
#include "Case.hpp"
#include "Map.hpp"

class Puce
{

  public:
    Puce(Game* game);
    void setPosition(int x, int y);

    Position getPosition();
    Dimensions getDimensions();

    sf::IntRect& getBoundingBox();

    void draw();
    void update(Map* map);

    void recupererVecteur();
    bool deplace(Map*map, sf::Sprite*, float vx, float vy);
    bool essaiDeplacement(Map*map, sf::Sprite*, float vx, float vy);

  private:
    RessourceManager *_rMgr;
    EventEngine *_eMgr;
    Game* _game;

    sf::Sprite _image;
    std::vector<sf::IntRect> _rects;
    Etat _etat, _oldEtat;

    Position _position, _positionBounding;
    Dimensions _dimensions;

    sf::IntRect _boundingBox;


    float _vitesse, _vx, _vy, _vitesseChute, _saut, _gravite;


    sf::Clock _montre;

};



#endif // PUCE_HPP_INCLUDED
