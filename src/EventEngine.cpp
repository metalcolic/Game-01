#include "EventEngine.hpp"
#include <iostream>


EventEngine EventEngine::_EventEngine;

EventEngine::EventEngine() : _app(NULL) {}

void EventEngine::registerApp(sf::RenderWindow* app)
{
    _app = app;
}

void EventEngine::updateKeyboard()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        _keyboard.Escape = true;
    else
        _keyboard.Escape = false;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        _keyboard.LControl = true;
    else
        _keyboard.LControl = false;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        _keyboard.left = true;
    else
        _keyboard.left = false;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        _keyboard.right = true;
    else
        _keyboard.right = false;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        _keyboard.space = true;
    else
        _keyboard.space = false;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        _keyboard.up = true;
    else
        _keyboard.up = false;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        _keyboard.down = true;
    else
        _keyboard.down = false;



}
void EventEngine::updateMouse()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        _mouse.left = true;
    else
        _mouse.left = false;

    if(sf::Mouse::isButtonPressed(sf::Mouse::Middle))
        _mouse.middle = true;
    else
        _mouse.middle = false;

    if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
        _mouse.right = true;
    else
        _mouse.right = false;

}
void EventEngine::updateMousePosition()
{
    _pos.x = sf::Mouse::getPosition(*_app).x;
    _pos.y = sf::Mouse::getPosition(*_app).y;
}


Position EventEngine::getMousePosition()
{
    return _pos;
}

Position EventEngine::getMousePosition(sf::View& vue)
{

    sf::Vector2i pos = static_cast<sf::Vector2i> (_app->convertCoords(sf::Vector2i(getMousePosition().x, getMousePosition().y), vue));
    Position temp;
    temp.x = pos.x;
    temp.y = pos.y;

    return temp;
}

KeyboardState EventEngine::getKeyboard()
{
    return _keyboard;
}
MouseState EventEngine::getMouse()
{
    return _mouse;
}
