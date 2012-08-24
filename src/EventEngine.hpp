#ifndef EVENTENGINE_HPP_INCLUDED
#define EVENTENGINE_HPP_INCLUDED


#include <SFML/Graphics.hpp>
#include "Structures.hpp"

class EventEngine
{
    public:
        EventEngine();

        void registerApp(sf::RenderWindow* app);

        void updateKeyboard();
        void updateMouse();
        void updateMousePosition();

        Position getMousePosition(sf::View&);
        Position getMousePosition();

        KeyboardState getKeyboard();
        MouseState getMouse();

        static EventEngine* instance() {
            return &_EventEngine;
        }

    private:
        static EventEngine _EventEngine;
        sf::RenderWindow* _app;
        static EventEngine _eventEngine;

        KeyboardState _keyboard;
        MouseState _mouse;
        Position _pos;
};

#endif // EVENTENGINE_HPP_INCLUDED
