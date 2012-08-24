#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Case.hpp"
#include "Entite.hpp"
#include "Structures.hpp"
#include <vector>
#include "Game.hpp"
#include "RessourceManager.hpp"

class Map
{
  public:
    Map(Game *game);
    void init();

    int getMapWidth();
    void setMapWidth(int);

    int getMapHeight();
    void setMapHeight(int);

    int getTileWidth();
    void setTileWidth(int);

    int getTileHeight();
    void setTileHeight(int);

    Case& getCase(int x, int y);

    void cleanMap();

    void update();
    void draw();

    bool Collision(sf::IntRect*);

    std::vector<Case> _map;
    std::vector<Entite> _entiteDevant, _entiteDerriere;

  private:
    Game* _game;
    RessourceManager* _rMgr;
    int _mapWidth, _mapHeight, _tileWidth, _tileHeight;


};

#endif // MAP_HPP_INCLUDED
