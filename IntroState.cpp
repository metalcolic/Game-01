#include "IntroState.hpp"
#include "Game.hpp"
#include "Menu.hpp"

IntroState IntroState::_IntroState;

void IntroState::init(Game *game)
{

}

void IntroState::cleanup()
{}

void IntroState::pause()
{

}
void IntroState::resume()
{

}

void IntroState::handleEvents(Game* game)
{
    sf::Event event;
    while(game->_app->pollEvent(event))
    {
        if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            game->quit();


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            game->popState();

    }
}

void IntroState::update(Game* game)
{

}

void IntroState::draw(Game* game)
{
    game->_app->clear(sf::Color(30,30,70));


    game->_app->display();
}








