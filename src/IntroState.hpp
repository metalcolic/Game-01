#ifndef INTROSTATE_HPP_INCLUDED
#define INTROSTATE_HPP_INCLUDED

#include "GameState.hpp"

class IntroState: public GameState
{
    public:
        void init(Game *game);
        void cleanup();

        void pause();
        void resume();

        void handleEvents(Game* game);
        void update(Game* game);
        void draw(Game* game);

        static IntroState* instance() {
            return &_IntroState;
        }

    protected:
        IntroState() { }

    private:
        static IntroState _IntroState;

};


#endif // INTROSTATE_HPP_INCLUDED
