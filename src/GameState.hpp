#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include "Game.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class GameState
{
  public:

    virtual void init(Game *game) = 0;
    virtual void cleanup() {}

    virtual void pause() {}
    virtual void resume() {}

    virtual void handleEvents(Game *game) = 0;
    virtual void update(Game *game) = 0;
    virtual void draw(Game *game) = 0;

    void changeState(Game *game, GameState* state) { game->changeState(state); }

  protected:
     GameState() { }
};

#endif // GAMESTATE_HPP_INCLUDED
