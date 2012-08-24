#ifndef EDITEUR_HPP_INCLUDED
#define EDITEUR_HPP_INCLUDED

#include "GameState.hpp"
#include "RessourceManager.hpp"
#include "EventEngine.hpp"

#include "Structures.hpp"
#include "Case.hpp"
#include "Entite.hpp"
#include <vector>
#include "../gui/GUI.hpp"
#include "Puce.hpp"
#include "Map.hpp"

class Editeur: public GameState
{
    public:
        void init(Game *game);
        void cleanup();

        void initGui(Game *game);
        void mapReinit();
        void rotation();

        void pause();
        void resume();

        void handleEvents(Game* game);

        void update(Game* game);
        void draw(Game* game);
        void drawGrille(Game* game);

        static Editeur* instance() {
            return &_Editeur;
        }

    protected:
        Editeur() : _rMgr(RessourceManager::instance()), _eMgr(EventEngine::instance()), _puce(), _carte(), _gui() { }

    private:
        void handleInterfaceEvents(Game*game, sf::Event& event);
        void handleMapEvents(Game* game, sf::Event& event);
        void handleNewMapEvents(Game* game, sf::Event& event);




        static Editeur _Editeur;
        RessourceManager* _rMgr;
        EventEngine* _eMgr;

        Puce *_puce;
        Map* _carte;

        sf::Text _textMapWidth, _textMapHeight, _statut, _textWidth ,_textHeight, _mapLocation;
        sf::String _textEnter;
        sf::RectangleShape _horizontale, _verticale;
        int _entree, _idTileSelect, _idEntiteSelect;
        bool _initMap;
        sf::Sprite _initSprite, _interface;

        sf::View _vueMap;
        sf::Vector2i _pos_mouse_map;

        sf::Sprite _tileSelect, _entiteSelect;


        bool _entiteMode, _grille, _bloquage;

        float _zoom_coef, _zoom_coef_total;


        Couche _couche, _lastCouche;
        bool _rotation, _scale;


        tgui::Layer *_gui;
        tgui::Layout *_layout;
        tgui::Button *_bouton_quit;
        tgui::Button *_bouton_menu;
        tgui::Button *_bouton_newMap;
        tgui::Button *_bouton_clean;
        tgui::Button *_bouton_mode;
        tgui::Button *_bouton_grille;
        tgui::Button *_bouton_couche;
        tgui::Button *_bouton_bloquage;
        tgui::Button *_bouton_rotation;
        tgui::Button *_bouton_scale;
        tgui::NumberSelect *_select_tailleX;


};

#endif // EDITEUR_HPP_INCLUDED
