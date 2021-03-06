#include <iostream>
#include "gui/GUI.hpp"

#include "src/Game.hpp"
#include "src/Menu.hpp"
#include "src/IntroState.hpp"
#include "src/RessourceManager.hpp"
#include "src/EventEngine.hpp"

int main()
{
    RessourceManager RManager;

    EventEngine *EManager = EventEngine::instance();

    Game jeu;

    jeu.init("Puce & the leg stealer");

    EManager->registerApp(jeu.getApp());

    jeu.pushState(IntroState::instance());

    jeu.pushState(Menu::instance());

    while(jeu.running())
    {
        jeu.handleEvent();
        jeu.update();
        jeu.draw();
    }

    return EXIT_SUCCESS;

}
