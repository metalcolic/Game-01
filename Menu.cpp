#include "Menu.hpp"
#include "IntroState.hpp"
#include "Editeur.hpp"
#include "Game.hpp"
#include <iostream>

Menu Menu::_menuState;

void Menu::init(Game *game)
{

//////////////////FONTS////////////////////////////////

    if(!_font.loadFromFile("data/fonts/caveman.ttf"))
        std::cout << "Can't load data/fonts/caveman.ttf" <<std::endl;


//////////////////TEXTES////////////////////////////////


    _titre.setFont(_font);
    _titre.setString("PUCE");
    _titre.setCharacterSize(80);
    _titre.setPosition((600 - _titre.getGlobalBounds().width) / 2 ,-10);
    _titre.setColor(sf::Color(195,135,100));

    _sousTitre.setFont(_font);
    _sousTitre.setString(sf::String("& THE LEG STEALER"));
    _sousTitre.setCharacterSize(20);
    _sousTitre.setPosition((600 - _titre.getGlobalBounds().width) / 2 , _titre.getGlobalBounds().height );
    _sousTitre.setColor(sf::Color(150,90,100));

//////////////////MUSIQUE////////////////////////////////


    if(!_music.openFromFile("data/music/8bit.ogg"))
        std::cout << "Can't load data/music/8bit.ogg" <<std::endl;

    _music.play();
    _music.setLoop(true);
    _music.setVolume(3);

//////////////////NUAGE 1////////////////////////////////

    if(!_text.loadFromFile("data/menu/tileset_nuage1.png"))


    _text.setSmooth(false);
    _nuage.setTexture(_text);

    _nuage.setPosition(10,150);
    sf::IntRect rect(0,0,300,_nuage.getGlobalBounds().height);
    _nuage.setTextureRect(rect);

//////////////////NUAGE 2////////////////////////////////

   if(!_text2.loadFromFile("data/menu/tileset_nuage2.png"))


    _text2.setSmooth(false);
    _nuage2.setTexture(_text2);
    _nuage2.setPosition(530,60);
    sf::IntRect rect2(0,0,262,_nuage2.getGlobalBounds().height);

    _nuage2.setTextureRect(rect2);

//////////////////MONTAGNES////////////////////////////////

    if(!_textM.loadFromFile("data/menu/mountains1.png"))


    _textM.setSmooth(false);
    _mountain.setTexture(_textM);

//////////////////PUCE////////////////////////////////

   if(!_textP.loadFromFile("data/menu/puce_volante_tileset.png"))


    _textP.setSmooth(false);
    _puce.setTexture(_textP);
    _puce.setPosition(200,250);

    sf::IntRect rect3(0,0,300,_puce.getGlobalBounds().height);
    _puce.setTextureRect(rect3);

//////////////////FORET////////////////////////////////

    if(!_textF.loadFromFile("data/menu/foret_defilante.png"))


    _textF.setSmooth(false);
    _foret1.setTexture(_textF);
    _foret2.setTexture(_textF);
    _foret3.setTexture(_textF);

    _foret1.setTextureRect(sf::IntRect(0,0,400,_foret1.getGlobalBounds().height));
    _foret2.setTextureRect(sf::IntRect(400,0,400,_foret2.getGlobalBounds().height));
    _foret3.setTextureRect(sf::IntRect(800,0,403,_foret3.getGlobalBounds().height));

    _foret1.setPosition(0,0);
    _foret2.setPosition(400,0);
    _foret3.setPosition(800,0);

//////////////////MENU////////////////////////////////

    if(!_textMenu.loadFromFile("data/menu/menu.png"))


    _textMenu.setSmooth(false);
    _menu.setTexture(_textMenu);
    _menu.setPosition(600,200);

    int _boucle = 0;
    _montre.restart();
    _montre2.restart();
}

void Menu::cleanup()
{}

void Menu::pause()
{
    _music.stop();
}
void Menu::resume()
{
    _music.play();
}

void Menu::handleEvents(Game* game)
{
    sf::Event event;
    while(game->_app->pollEvent(event))
    {
        if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            game->quit();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            game->pushState(IntroState::instance());

        if(sf::Keyboard::isKeyPressed((sf::Keyboard::E)))
        {
            game->_app->setMouseCursorVisible(false);
            game->pushState(Editeur::instance());
        }

    }
}

void Menu::update(Game* game)
{
    if(_foret1.getPosition().x < -400)
        _foret1.setPosition(800,0);

    if(_foret2.getPosition().x < -400)
        _foret2.setPosition(800,0);

    if(_foret3.getPosition().x < -400)
        _foret3.setPosition(800,0);

    _foret1.move(-50 * _montre2.getElapsedTime().asSeconds(),0);
    _foret2.move(-50* _montre2.getElapsedTime().asSeconds(),0);
    _foret3.move(-50 * _montre2.getElapsedTime().asSeconds(),0);

    _montre2.restart();



    if(_montre.getElapsedTime().asSeconds() >= 0.13)
    {
        if(_boucle == 0)
        {
            rect = sf::IntRect(300,0,300,_nuage.getGlobalBounds().height);
            rect2 = sf::IntRect(262,0,262,_nuage2.getGlobalBounds().height);
            rect3 = sf::IntRect(300,0,300,_puce.getGlobalBounds().height);
            _boucle  = 1;
        }
        else
        {
            rect = sf::IntRect(0,0,300,_nuage.getGlobalBounds().height);
            rect2 = sf::IntRect(0,0,262,_nuage2.getGlobalBounds().height);
            rect3 = sf::IntRect(0,0,300,_puce.getGlobalBounds().height);
            _boucle  = 0;
        }
        _montre.restart();
        _nuage.setTextureRect(rect);
        _nuage2.setTextureRect(rect2);
        _puce.setTextureRect(rect3);
    }




}

void Menu::draw(Game* game)
{
    game->_app->clear(sf::Color(30,30,70));

    game->_app->draw(_mountain);
    game->_app->draw(_nuage);
    game->_app->draw(_nuage2);

    game->_app->draw(_menu);

    game->_app->draw(_foret1);
    game->_app->draw(_foret2);
    game->_app->draw(_foret3);

    game->_app->draw(_titre);
    game->_app->draw(_sousTitre);
    game->_app->draw(_puce);

    game->_app->display();
}








