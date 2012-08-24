#include "Game.hpp"
#include "GameState.hpp"
#include <iostream>
Game::Game(int w, int h, int bpp, std::string titre) : _app(NULL)
{
    init(w,h,bpp,titre);
    _running = true;
}
Game::Game() : _app(NULL)
{
    _running = true;
}

Game::Game(std::string titre) : _app(NULL)
{
    _running = true;
    init(titre);
}

Game::~Game()
{
    delete _app;
    _app = NULL;

}

void Game::init(int w, int h, int bpp, std::string titre)
{
    if(_app == NULL)
    {
        _app = new sf::RenderWindow(sf::VideoMode(w,h,bpp), titre);
        _app->setFramerateLimit(60);
        _app->setVerticalSyncEnabled(true);

        _running = true;

        _dimensions.width = w;
        _dimensions.height = h;
    }
}
void Game::init(std::string titre)
{
    if(_app == NULL)
    {
        _app = new sf::RenderWindow(sf::VideoMode(800,600,32), titre, sf::Style::Close);
        _app->setFramerateLimit(60);
        _app->setVerticalSyncEnabled(true);

        _running = true;

        _dimensions.width = 800;
        _dimensions.height = 600;
    }
}
void Game::init()
{
    if(_app == NULL)
    {
        _app = new sf::RenderWindow(sf::VideoMode(800,600,32), "Application");
        _app->setFramerateLimit(60);
        _app->setVerticalSyncEnabled(true);

        _running = true;

        _dimensions.width = 800;
        _dimensions.height = 600;
    }
}

void Game::cleanup()
{
    // cleanup the all states
	while ( !_states.empty() ) {
		_states.back()->cleanup();
		_states.pop_back();
	}
}

void Game::changeState(GameState *state)
{
    if(!_states.empty()) {
        _states.back()->cleanup();
        _states.pop_back();
    }

    _states.push_back(state);
    _states.back()->init(this);

}
void Game::pushState(GameState *state)
{
    if(!_states.empty()){
        _states.back()->pause();
    }

    _states.push_back(state);
    _states.back()->init(this);

}

void Game::popState()
{
    if(!_states.empty()){
        _states.back()->cleanup();
        _states.pop_back();
    }
    if(!_states.empty()){
        _states.back()->resume();
    }
}


void Game::handleEvent()
{
    _states.back()->handleEvents(this);
}
void Game::update()
{
    _states.back()->update(this);
}
void Game::draw()
{
    _states.back()->draw(this);
}


sf::RenderWindow* Game::getApp()
{
    return _app;
}

