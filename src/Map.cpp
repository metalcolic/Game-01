#include "Map.hpp"

Map::Map(Game *game) : _game(game), _rMgr(RessourceManager::instance())
{
    _mapWidth = 0;
    _mapHeight = 0;
    _tileWidth = 0;
    _tileHeight = 0;
}


void Map::init()
{
    for(int i = 0 ; i < _mapHeight ; i++)
    {
        for(int j = 0; j < _mapWidth ; j++)
        {
            _map.push_back(Case(_game->_app));
            _map.back().setTuile(DERRIERE, _rMgr->getTile(0));
            _map.back().setPosition( j * _tileWidth, i * _tileHeight );
            _map.back().setBloquante(false);
        }
    }
}

int Map::getMapWidth()
{
    return _mapWidth;
}

void Map::setMapWidth(int temp)
{
    _mapWidth = temp;
}

int Map::getMapHeight()
{
    return _mapHeight;
}

void Map::setMapHeight(int temp)
{
    _mapHeight = temp;
}

int Map::getTileWidth()
{
    return _tileWidth;
}

void Map::setTileWidth(int temp)
{
    _tileWidth = temp;
}

int Map::getTileHeight()
{
    return _tileHeight;
}

void Map::setTileHeight(int temp)
{
    _tileHeight = temp;
}

Case& Map::getCase(int x, int y)
{
    int id = y * _mapWidth + x;

    return _map[id];
}


void Map::cleanMap()
{
    for(int i = 0; i < (int)_map.size(); i++)
        _map[i].setTuile(DERRIERE, _rMgr->getTile(0));

    _entiteDevant.clear();
    _entiteDerriere.clear();

}

void Map::update()
{

}

void Map::draw()
{
    for(int i = 0; i < (int)_entiteDerriere.size(); i++)
        _entiteDerriere[i].draw();


    for(int i = 0; i < (int)_map.size(); i++)
         _map[i].draw();


    for(int i = 0; i < (int)_entiteDevant.size(); i++)
        _entiteDevant[i].draw();
}


bool Map::Collision(sf::IntRect * perso)
{
    int xmin, xmax, ymin, ymax, mapWidth, mapHeight;
    xmin = perso->left / _tileWidth;
    ymin = perso->top / _tileHeight;
    xmax = (perso->left  + perso->width - 1 ) / _tileWidth;
    ymax =  (perso->top + perso->height - 1) / _tileHeight;

    mapWidth = _tileWidth * _mapWidth;
    mapHeight = _tileHeight * _mapHeight;

    std::cout << xmin<< "::" << ymin<< "  "<< xmax<< "::" << ymax << std::endl;

    if(perso->left < 0 || perso->left + perso->width  > mapWidth ||
       perso->top < 0 || perso->top + perso->height > mapHeight )
       return true;

    for(int i = xmin; i <= xmax; i++)
    {
        for(int j = ymin; j <= ymax; j++)
        {


            if(getCase(i,j).isBloquante())
                return true;
        }
    }

    return false;
}



