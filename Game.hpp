#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <string>

#include "Structures.hpp"

class GameState;

class Game
{
  public:
        Game(int, int, int, std::string);
        Game(std::string);
        Game();
        ~Game();

        void init(int, int, int, std::string);
        void init(std::string);
        void init();

        void cleanup();


        void changeState(GameState *state);
        void pushState(GameState *state);
        void popState();



        void handleEvent();
        void update();
        void draw();


        bool running() { return _running; }
        void quit() { _running = false; }

        sf::RenderWindow* getApp();

        sf::RenderWindow* _app;

    private:

        Dimensions _dimensions;

        std::vector<GameState*> _states;

        bool _running;

};

#endif // GAME_HPP_INCLUDED
