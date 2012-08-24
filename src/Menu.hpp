#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "GameState.hpp"
#include <vector>

class Menu : public GameState
{
    public:
        void init(Game *game);
        void cleanup();

        void pause();
        void resume();

        void handleEvents(Game* game);
        void update(Game* game);
        void draw(Game* game);

        static Menu* instance() {
            return &_menuState;
        }

    protected:
        Menu() { }

    private:
        static Menu _menuState;

        sf::Font _font;
        sf::Text _titre, _sousTitre;

        sf::Texture _text, _text2, _textM , _textP, _textF, _textMenu;
        sf::Sprite _nuage, _nuage2, _puce, _mountain, _foret1, _foret2, _foret3, _menu;
        sf::IntRect rect, rect2, rect3;


        sf::Music _music;

        sf::Clock _montre, _montre2;
        int _boucle;
};

#endif // MENU_HPP_INCLUDED
