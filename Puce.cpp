#include "Puce.hpp"


Puce::Puce(Game* game) :_rMgr(RessourceManager::instance()),  _eMgr(EventEngine::instance()), _game(game)
{
    _image.setTexture(_rMgr->getEntite("puce"));

    _rects.push_back(sf::IntRect(0,0, _image.getGlobalBounds().width, _image.getGlobalBounds().height ));

    _oldEtat = DROITE;
    _etat = ARRET;


    _position.x = 0;
    _position.y = 0;

    _dimensions.width = _image.getGlobalBounds().width;
    _dimensions.height = _image.getGlobalBounds().height;

    _boundingBox = sf::IntRect(0,0,50,121);


    _vitesseChute = 0.981f;

    _montre.restart();
    _vitesse = 0.8f;
    _saut = 1.f;
    _vitesseChute = 0.07f;
    _vx = 0.f;
    _vy = 0.f;
    _gravite = .981f;

}

void Puce::draw()
{
    _game->_app->draw(_image);
}

void Puce::update(Map* map)
{


    recupererVecteur();

    if(_etat == SAUT)
    {
        _saut -= _vitesseChute;
        _vy = (_vy - _saut ) *_montre.getElapsedTime().asMilliseconds();
    }
    else
     {
         _vy = (_vy + _gravite) *_montre.getElapsedTime().asMilliseconds();
         _saut = 1.25f;
     }

    _vx *= _montre.getElapsedTime().asMilliseconds();



    deplace(map, &_image, _vx , _vy);


    _montre.restart();



}

bool Puce::deplace(Map*map, sf::Sprite* perso, float vx,float vy)
{
    int i;
	if (essaiDeplacement(map, perso,vx,vy))
		return true;

    for(i=0;i<ABS(vx);i++)
	{
		if (essaiDeplacement(map, perso,SGN(vx),0)==0)
			break;
	}
	for(i=0;i<ABS(vy);i++)
	{
		if (essaiDeplacement(map, perso,0,SGN(vy))==0)
			break;
	}

}

bool Puce::essaiDeplacement(Map* map, sf::Sprite* perso, float vx,float vy)
{

    sf::IntRect test(perso->getPosition().x + vx, perso->getPosition().y + vy, perso->getGlobalBounds().width, perso->getGlobalBounds().height);


	if (!map->Collision(&test))
	{
		_image.setPosition(test.left, test.top);
		return 1;
	}
	return 0;
}

void Puce::setPosition(int x, int y)
{
    _position.x = x;
    _position.y = y;
}

Position Puce::getPosition()
{
    return _position;
}

Dimensions Puce::getDimensions()
{
    return _dimensions;
}

sf::IntRect& Puce::getBoundingBox()
{
    return _boundingBox;
}

void Puce::recupererVecteur()
{
    _vx = _vy = 0;

    if(_eMgr->getKeyboard().left)
      {
        if(_etat == SAUT)
            _vx = -_vitesse / 2;
        else
            _vx = -_vitesse;
      }

    if(_eMgr->getKeyboard().right)
    {
        if(_etat == SAUT)
            _vx = _vitesse / 2;
        else
            _vx = _vitesse;
      }


    if(_eMgr->getKeyboard().up)
        _vy = 0;

    if(_eMgr->getKeyboard().down)
        _vy = 0;

    if(_eMgr->getKeyboard().space && _etat != SAUT)
         _etat = SAUT;

    if(!_eMgr->getKeyboard().space && _etat == SAUT)
        _etat = ARRET;
}
