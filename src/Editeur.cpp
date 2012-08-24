#include "Game.hpp"
#include "Menu.hpp"
#include "Editeur.hpp"

Editeur Editeur::_Editeur;

void Editeur::init(Game *game)
{
     _carte = new Map(game);
     _puce = new Puce(game);

     _carte->setTileWidth(TILE_WIDTH);
     _carte->setTileHeight(TILE_HEIGHT);

    _lastCouche = AUCUNE;
    _bloquage = true;
    _couche = DEVANT;
    _rotation = false;
    _scale = false;

    _zoom_coef = 1.f;
    _zoom_coef_total = 1.f;

    _entree = 0;
    _initMap = true;
    _entiteMode = false;
    _grille = true;


    _idTileSelect = 1;
    _tileSelect.setTexture(_rMgr->getTile(_idTileSelect));

    _idEntiteSelect = 0;
    _entiteSelect.setTexture(_rMgr->getEntite(_idEntiteSelect), true);


    _vueMap.reset(sf::FloatRect(0,0,650,600));
    _vueMap.setViewport(sf::FloatRect(0.1875f,0.f,.8125f,1.f));


    _initSprite.setTexture(_rMgr->getTexture("puceroom"));
    _interface.setTexture(_rMgr->getTexture("panneau"));

    _horizontale.setFillColor(sf::Color(190,190,190));
    _verticale.setFillColor(sf::Color(190,190,190));

    _statut.setFont(_rMgr->getFont(1));
    _statut.setString("");
    _statut.setPosition(40,220);
    _statut.setCharacterSize(28);

    _mapLocation.setFont(_rMgr->getFont(1));
    _mapLocation.setString("");
    _mapLocation.setPosition(5,550);
    _mapLocation.setCharacterSize(19);


    _textWidth.setFont(_rMgr->getFont(1));
    _textWidth.setString("");
    _textWidth.setCharacterSize(25);
    _textWidth.setPosition(155  , 150);

    _textHeight.setFont(_rMgr->getFont(1));
    _textHeight.setString("");
    _textHeight.setCharacterSize(25);
    _textHeight.setPosition(155, 180);

    initGui(game);


}

void Editeur::initGui(Game *game)
{
    _gui = new tgui::Layer(game->_app);
    _layout = new tgui::Layout(game->_app);

    _bouton_quit = new tgui::Button(game->_app, "Quit");
    _bouton_menu = new tgui::Button(game->_app, "Menu");
    _bouton_newMap = new tgui::Button(game->_app, "New Map");
    _bouton_clean = new tgui::Button(game->_app, "Clean");
    _bouton_mode = new tgui::Button(game->_app, "Mode Map");
    _bouton_grille = new tgui::Button(game->_app, "Grille");
    _bouton_couche = new tgui::Button(game->_app, "Devant");
    _bouton_bloquage = new tgui::Button(game->_app, "Bloquant");
    _bouton_rotation = new tgui::Button(game->_app, "Rotation");
    _bouton_scale = new tgui::Button(game->_app, "Taille");
    _select_tailleX = new tgui::NumberSelect(game->_app);

    _bouton_grille->setActive(true);
    _bouton_bloquage->setActive(true);

    auto fonction_scale = [this](){
        if(_scale == true)
        {
            _scale = false;
            _bouton_scale->setActive(false);
        }
        else
        {
            _scale = true;
            _bouton_scale->setActive(true);
        }
    };

    auto fonction_couche = [this](){
        if(_couche == DEVANT)
        {
            _couche = DERRIERE;
            _bouton_couche->setText("Derrière");
        }
        else
        {
            _couche = DEVANT;
            _bouton_couche->setText("Devant");
        }
    };

    auto fonction_bloquage = [this](){
        if(_bloquage)
        {
            _bouton_bloquage->setActive(false);
            _bloquage = false;
        }
        else
        {
            _bouton_bloquage->setActive(true);
            _bloquage = true;
        }
    };


    auto fonction_grille = [this](){
        if(_grille)
        {
            _grille = false;
            _bouton_grille->setActive(false);
            _bouton_grille->setText("Grille");
        }
        else
        {
            _grille = true;
            _bouton_grille->setActive(true);
            _bouton_grille->setText("Grille");
        }
    };

    auto fonction_mode = [_bouton_mode, this] () {
        if(_entiteMode)
        {
           _entiteMode = false;
           _bouton_mode->setText("Mode Map");
        }
        else
        {
            _entiteMode = true;
           _bouton_mode->setText("Mode Entité");
        }

    };

    auto fonction_quitter = [game](){
        game->quit();
    };
    auto fonction_menu = [game](){

    };

    auto fonction_newMap = [this](){
        mapReinit();
    };

    auto fonction_clean = [this](){
         _carte->cleanMap();
    };

    auto fonction_rotation = [this](){
        if(_rotation)
        {
           _rotation = false;
           _bouton_rotation->setActive(false);
        }
        else
        {
            _rotation = true;
           _bouton_rotation->setActive(true);
        }
    };

    _bouton_quit->setAction(fonction_quitter, tgui::BUTTON::CLICK_RELEASED);
    _bouton_menu->setAction(fonction_menu, tgui::BUTTON::CLICK_RELEASED);
    _bouton_newMap->setAction(fonction_newMap, tgui::BUTTON::CLICK_RELEASED);
    _bouton_clean->setAction(fonction_clean, tgui::BUTTON::CLICK_RELEASED);
    _bouton_mode->setAction(fonction_mode, tgui::BUTTON::CLICK_RELEASED);
    _bouton_grille->setAction(fonction_grille, tgui::BUTTON::CLICK_RELEASED);
    _bouton_couche->setAction(fonction_couche, tgui::BUTTON::CLICK_RELEASED);
    _bouton_bloquage->setAction(fonction_bloquage, tgui::BUTTON::CLICK_RELEASED);
    _bouton_rotation->setAction(fonction_rotation, tgui::BUTTON::CLICK_RELEASED);
    _bouton_scale->setAction(fonction_scale, tgui::BUTTON::CLICK_RELEASED);

    _layout->addWidget(_bouton_mode,0,0);
    _layout->addWidget(_bouton_couche,1,0);
    _layout->addWidget(_bouton_bloquage,2,0);
    _layout->addWidget(_bouton_rotation,3,0);
    _layout->addWidget(_bouton_scale,4,0);
    _layout->addWidget(_bouton_clean,5,0);
    _layout->addWidget(_bouton_grille,6,0);
    _layout->addWidget(_bouton_newMap,7,0);
    _layout->addWidget(_bouton_menu,8,0);
    _layout->addWidget(_bouton_quit,9,0);
    _layout->addWidget(_select_tailleX, 10,0);

    _layout->setPos(0,7);

    _layout->open();

    _gui->addWidget(_layout);

}

void Editeur::mapReinit()
{
    _carte->cleanMap();
    _initMap = true;

    _entree = 0;
    _textWidth.setString("");
    _textWidth.setPosition(155  , 150);
    _textHeight.setString("");
    _textHeight.setPosition(155, 180);
    _statut.setString("");
    _textHeight.setCharacterSize(30);
    _textWidth.setCharacterSize(30);
}

void Editeur::cleanup()
{
    delete _gui;
    delete _layout;
    delete _bouton_quit;
    delete _bouton_menu;
    delete _bouton_newMap;
    delete _bouton_clean;
    delete _bouton_mode;
    delete _bouton_grille;
    delete _bouton_couche;
    delete _bouton_bloquage;
    delete _bouton_rotation;
    delete _select_tailleX;
    delete _puce;
    delete _carte;
}

void Editeur::pause()
{

}
void Editeur::resume()
{

}



void Editeur::handleEvents(Game* game)
{
    sf::Event event;
    while(game->_app->pollEvent(event))
    {
        _eMgr->updateKeyboard();
        _eMgr->updateMouse();

        handleInterfaceEvents(game, event);
        handleMapEvents(game,event);
        handleNewMapEvents(game,event);

    }
}

void Editeur::handleMapEvents(Game* game, sf::Event& event)
{

    _gui->update();
if(!_gui->isGuiHover() && sf::Mouse::getPosition(*game->_app).x > 150 )
{

    if(event.type == sf::Event::MouseMoved)
        {
            sf::Vector2i pos(_eMgr->getMousePosition().x, _eMgr->getMousePosition().y);
            _eMgr->updateMousePosition();

            if(_eMgr->getMouse().middle)
            {
                _vueMap.move(((pos.x - _eMgr->getMousePosition().x) * _zoom_coef_total ),(pos.y - _eMgr->getMousePosition().y) * _zoom_coef_total);
            }

            std::ostringstream oss;

            oss << "x: "<< _eMgr->getMousePosition(_vueMap).x / TILE_WIDTH << std::endl << "y: "<<_eMgr->getMousePosition(_vueMap).y / TILE_HEIGHT;
            _mapLocation.setString(oss.str());

        }

        if(_eMgr->getMouse().left && !_eMgr->getMouse().right)
        {
            sf::Vector2f mPos(_eMgr->getMousePosition(_vueMap).x,_eMgr->getMousePosition(_vueMap).y);

            if(!_entiteMode)
            {
                if(mPos.x >= 0 && mPos.y >= 0 && mPos.x < _carte->getMapWidth() * TILE_WIDTH && mPos.y < _carte->getMapHeight() * TILE_HEIGHT)
                {

                    int id;
                    Position temp;
                    temp.x = mPos.x / TILE_WIDTH;
                    temp.y = mPos.y / TILE_HEIGHT;
                    id = temp.y * _carte->getMapWidth() + temp.x;

                    _carte->_map[id].setTuile(DERRIERE, _rMgr->getTile(_idTileSelect));
                    _carte->_map[id].setBloquante(_bloquage);
                }

            }
            else
            {
                if(_couche == DERRIERE)
                {
                    _lastCouche = DERRIERE;
                    _carte->_entiteDerriere.push_back(Entite(game->_app, _rMgr->getEntite(_idEntiteSelect), mPos.x, mPos.y));
                    _carte->_entiteDerriere.back().setCouche(_couche);
                    _carte->_entiteDerriere.back().setBloquant(_bloquage);
                }
                else if (_couche == DEVANT)
                {
                    _lastCouche = DEVANT;

                    _carte->_entiteDevant.push_back(Entite(game->_app, _rMgr->getEntite(_idEntiteSelect), mPos.x, mPos.y));
                    _carte->_entiteDevant.back().setCouche(_couche);
                    _carte->_entiteDevant.back().setBloquant(_bloquage);
                }

            }
        }
        if(_eMgr->getMouse().right && !_eMgr->getMouse().left)
        {
            sf::Vector2f mPos(_eMgr->getMousePosition(_vueMap).x,_eMgr->getMousePosition(_vueMap).y);
            if(!_entiteMode)
            {
                if(mPos.x >= 0 && mPos.y >= 0 && mPos.x <= _carte->getMapWidth() * TILE_WIDTH && mPos.y <= _carte->getMapHeight() * TILE_HEIGHT)
                {
                    int id;
                    Position temp;
                    temp.x = mPos.x / TILE_WIDTH;
                    temp.y = mPos.y / TILE_HEIGHT;
                    id = temp.y * _carte->getMapWidth() + temp.x;

                    _carte->_map[id].setTuile(DERRIERE, _rMgr->getTile(0));
                    _carte->_map[id].setBloquante(false);
                }

            }
            else
            {
                bool find = false;
                for(int i = _carte->_entiteDevant.size() - 1; i>= 0 ; i--)
                {
                    if(_carte->_entiteDevant[i].isHover(mPos))
                    {
                        _carte->_entiteDevant.erase(_carte->_entiteDevant.begin() + i);
                        i = -1;
                        find = true;
                    }
                }

                if(find == false)
                {
                    for(int i = _carte->_entiteDerriere.size() - 1; i>= 0 ; i--)
                    {
                        if(_carte->_entiteDerriere[i].isHover(mPos))
                        {
                            _carte->_entiteDerriere.erase(_carte->_entiteDerriere.begin() + i);
                            i = -1;
                            find = true;
                        }
                    }
                }

            }
        }

        if(event.type == sf::Event::MouseWheelMoved)
        {
            if(_scale)
            {
                if(_lastCouche == DERRIERE)
                {
                    if(event.mouseWheel.delta > 0)
                        _carte->_entiteDerriere.back().scale(0.2);
                    else if (event.mouseWheel.delta < 0)
                        _carte->_entiteDerriere.back().scale(-0.2);

                }
                else if (_lastCouche == DEVANT)
                {
                    if(event.mouseWheel.delta > 0)
                        _carte->_entiteDevant.back().scale(0.2);
                    else if (event.mouseWheel.delta < 0)
                         _carte->_entiteDevant.back().scale(0.2);
                }
            }
            if(_rotation)
            {
                if(_lastCouche == DERRIERE)
                {
                    if(event.mouseWheel.delta > 0)
                        _carte->_entiteDerriere.back().rotation(1);
                    else if (event.mouseWheel.delta < 0)
                        _carte->_entiteDerriere.back().rotation(-1);

                }
                else if (_lastCouche == DEVANT)
                {
                    if(event.mouseWheel.delta > 0)
                        _carte->_entiteDevant.back().rotation(1);
                    else if (event.mouseWheel.delta < 0)
                        _carte->_entiteDevant.back().rotation(-1);
                }
            }
            else
            {
                if(!_entiteMode)
                {
                    if(event.mouseWheel.delta > 0)
                    {
                        if(_idTileSelect > 1 && _idTileSelect <= _rMgr->getTileSize())
                            _idTileSelect-- ;

                        _tileSelect.setTexture(_rMgr->getTile(_idTileSelect));
                    }
                    else if (event.mouseWheel.delta < 0)
                    {
                        if(_idTileSelect >= 1 && _idTileSelect < _rMgr->getTileSize()-1)
                            _idTileSelect++;

                        _tileSelect.setTexture(_rMgr->getTile(_idTileSelect));
                    }
                }
                else
                {
                    if(event.mouseWheel.delta > 0)
                    {
                        if(_idEntiteSelect > 0 && _idEntiteSelect <= _rMgr->getEntiteSize())
                            _idEntiteSelect-- ;

                        _entiteSelect.setTexture(_rMgr->getEntite(_idEntiteSelect), true);
                    }
                    else if (event.mouseWheel.delta < 0)
                    {
                        if(_idEntiteSelect >= 0 && _idEntiteSelect < _rMgr->getEntiteSize()-1)
                            _idEntiteSelect++;

                        _entiteSelect.setTexture(_rMgr->getEntite(_idEntiteSelect), true);
                    }
                }
            }

        }

        if(event.type == sf::Event::MouseWheelMoved && _eMgr->getKeyboard().LControl)
        {
            int wheel = event.mouseWheel.delta;

            if(wheel < 0)
            {
                _zoom_coef = 1.03f;
                _zoom_coef_total *= _zoom_coef;
            }
            else if(wheel > 0)
            {
                _zoom_coef = 1/(1.03f);

                _zoom_coef_total *= _zoom_coef;
            }

            if(_zoom_coef_total < 1.0f)
            {
                _zoom_coef = 1.f;
                _zoom_coef_total = 1.f;
            }

            if(_zoom_coef_total > 2.0f)
            {
                _zoom_coef = 1.f;
                _zoom_coef_total = 2.f;
            }
            _vueMap.zoom(_zoom_coef);
        }
}


}
void Editeur::handleNewMapEvents(Game* game, sf::Event& event)
{

            if(event.type == sf::Event::TextEntered && _initMap)
        {
            char c = static_cast<char> (event.text.unicode);

            if(c >= '0' && c <= '9' && _entree == 0)
            {
                _textEnter += event.text.unicode;
                _textWidth.setString(_textEnter);
            }
            else if(c >= '0' && c <= '9' && _entree == 1)
            {
                _textEnter += event.text.unicode;
                _textHeight.setString(_textEnter);
            }
            else if(c == '\r')
            {
                int temp;
                std::stringstream in(_textEnter.toAnsiString());
                in >> temp;
                if(_entree == 0)
                {
                    if(temp > 100)
                    {
                        _statut.setString("Width Error (max = 100)");
                        _statut.setColor(sf::Color::Red);
                        _textWidth.setString("");

                    }
                    else if(temp == 0)
                    {
                        _statut.setString("Width Error (min = 1)");
                    }
                    else
                    {
                        _statut.setString("Width ok!");
                        _statut.setColor(sf::Color::Green);

                        _carte->setMapWidth(temp);

                        _horizontale.setSize(sf::Vector2f(_carte->getMapWidth() * TILE_WIDTH,1));
                        _entree = 1;
                    }

                }
                else if(_entree == 1)
                {
                    if(temp > 80 )
                    {
                        _statut.setString("Height Error (max = 80)");
                        _statut.setColor(sf::Color::Red);
                        _textHeight.setString("");
                    }
                    else if(temp == 0)
                    {
                        _statut.setString("Height Error (min = 1)");
                    }
                    else
                    {
                        _statut.setString("Height ok!");
                        _statut.setColor(sf::Color::Green);

                        _carte->setMapHeight(temp);

                        _verticale.setSize(sf::Vector2f(1 , _carte->getMapHeight() * TILE_HEIGHT));
                        _entree = 2;
                    }

                }
                if (_entree == 2)
                {

                    _carte->init();



                    _textWidth.setString("Largeur: " + _textWidth.getString());
                    _textWidth.setPosition(5,510);
                    _textHeight.setString("Hauteur: " + _textHeight.getString());
                    _textHeight.setPosition(5,530);

                    _textHeight.setCharacterSize(19);
                    _textWidth.setCharacterSize(19);

                    _initMap = false;

                }

                _textEnter.clear();

            }
        }
}
void Editeur::handleInterfaceEvents(Game*game, sf::Event& event)
{

        if(event.type == sf::Event::Closed || _eMgr->getKeyboard().Escape)
            game->quit();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        {
            game->_app->setMouseCursorVisible(true);
            game->popState();
        }

}

void Editeur::update(Game* game)
{
    _tileSelect.setPosition(sf::Mouse::getPosition(*game->_app).x, sf::Mouse::getPosition(*game->_app).y);
    _entiteSelect.setPosition(sf::Mouse::getPosition(*game->_app).x, sf::Mouse::getPosition(*game->_app).y);

    if(!_initMap)
        _puce->update(_carte);

}

void Editeur::draw(Game* game)
{
    game->_app->clear(sf::Color(100,100,100));

    if(_initMap)
    {
        game->_app->draw(_initSprite);
        game->_app->draw(_statut);

        game->_app->draw(_textWidth);

        game->_app->draw(_textHeight);
    }
    else
    {

        game->_app->setView(_vueMap);

            if(_grille)
                drawGrille(game);

            _carte->draw();

            _puce->draw();

        game->_app->setView(game->_app->getDefaultView());
            game->_app->draw(_interface);
            _gui->draw();

            if(sf::Mouse::getPosition(*game->_app).x > 150)
            {
                game->_app->setMouseCursorVisible(false);
                if(!_entiteMode)
                    game->_app->draw(_tileSelect);
                else
                    game->_app->draw(_entiteSelect);
            }
            else
            {
                game->_app->setMouseCursorVisible(true);
            }


            game->_app->draw(_textWidth);
            game->_app->draw(_textHeight);
            game->_app->draw(_mapLocation);
    }


    game->_app->display();
}

void Editeur::drawGrille(Game* game)
{
    if(_grille)
    {
        for(int i=0; i <= _carte->getMapWidth(); i++)
        {
            if( i == 0)
                _verticale.setPosition(i * TILE_WIDTH, 0);
            else
                _verticale.setPosition(i * TILE_WIDTH -1 , 0);

            game->_app->draw(_verticale);
        }
        for(int i=0; i <= _carte->getMapHeight(); i++)
        {
            _horizontale.setPosition(0,i * TILE_HEIGHT);
            game->_app->draw(_horizontale);
        }
    }
}





