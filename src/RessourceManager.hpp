#ifndef RESSOURCEMANAGER_HPP
#define RESSOURCEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>


enum RTYPE { FONTS, MUSIC, SOUND, TEXTURE};

struct RTexture
{
  sf::Texture texture;
  std::string nom;
};

struct RFont
{
    sf::Font font;
    std::string nom;
};

struct RMusic
{
    sf::Music music;
    std::string nom;
};

struct RSound
{
    sf::SoundBuffer buffer;
    sf::Sound sound;
    std::string nom;
};

struct RTile
{
    sf::Texture texture;
    std::string nom;
};

struct REntite
{
    sf::Texture texture;
    std::string nom;
};

class RessourceManager
{
    public:
        RessourceManager();
        virtual ~RessourceManager();

        void loadRessources();

        RSound* getSound(int);
        RSound* getSound(std::string);

        sf::Texture& getTexture(int);
        sf::Texture& getTexture(std::string);

        RMusic* getMusic(int);
        RMusic* getMusic(std::string);

        sf::Font& getFont(int);
        sf::Font& getFont(std::string);

        sf::Texture& getTile(int);
        sf::Texture& getTile(std::string);

        sf::Texture& getEntite(int);
        sf::Texture& getEntite(std::string);

        int getTileSize();
        int getEntiteSize();

        static RessourceManager* instance() {
            return &_RessourceManager;
        }



    private:
        std::vector<RTexture> _textures;
        std::vector<RMusic*> _musics;
        std::vector<RSound*> _sounds;
        std::vector<RFont> _fonts;
        std::vector<RTile> _tiles;
        std::vector<REntite> _entites;


        std::string _ressourceFilePath;

        static RessourceManager _RessourceManager;
};



#endif // RESSOURCEMANAGER_HPP
