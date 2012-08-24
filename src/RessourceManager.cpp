#include "RessourceManager.hpp"

RessourceManager RessourceManager::_RessourceManager;

RessourceManager::RessourceManager()
{
    _ressourceFilePath = "data/config/ressources.puce";
    loadRessources();

}

RessourceManager::~RessourceManager()
{

}


void RessourceManager::loadRessources()
{
    std::ofstream error("errors/ressources.error", std::ios::app);
    error.seekp(0, std::ios::end);

    std::ifstream file(_ressourceFilePath);
    file.seekg(0, std::ios::beg);

    std::string section;
    std::string chemin;
    std::string mot;

    if(file)
    {

        while(file)
        {
            file >> mot;

            if(mot != "")
            {
                if(mot == "[FONTS]")
                {
                    mot = "";
                    file >> mot;

                    while(mot != "[TEXTURE]" && mot != "[SOUND]" && mot != "[MUSIC]" && mot != "[TILE]" && mot !="[ENTITE]" && !file.eof())
                    {

                        RFont ressource;

                        if(!ressource.font.loadFromFile(mot))
                        {
                            std::cout << "FONT LOAD ERROR : " << mot << std::endl;
                            file >> mot;
                        }
                        else
                        {
                            file>>mot;
                            ressource.nom = mot;
                            _fonts.push_back(ressource);
                        }
                        mot = "";
                        file >> mot;
                    }

                }
                if(mot == "[TEXTURE]")
                {
                    mot = "";
                    file >> mot;

                    while(mot != "[FONTS]" && mot != "[SOUND]" && mot != "[MUSIC]"&&  mot != "[TILE]" && mot !="[ENTITE]"  && !file.eof())
                    {

                        RTexture ressource;

                        if(!ressource.texture.loadFromFile(mot))
                        {
                            std::cout << "TEXTURE LOAD ERROR : " << mot << std::endl;
                            file >> mot;
                        }
                        else
                        {
                            file>>mot;
                            ressource.nom = mot;
                            _textures.push_back(ressource);
                        }
                        mot = "";
                        file >> mot;
                    }
                }
                if(mot == "[MUSIC]")
                {
                    mot = "";
                    file >> mot;

                    while(mot != "[TEXTURE]" && mot != "[SOUND]" && mot != "[FONTS]" && mot != "[TILE]" && mot !="[ENTITE]" && !file.eof())
                    {

                        RMusic ressource;

                        if(!ressource.music.openFromFile(mot))
                        {
                            std::cout << "MUSIC LOAD ERROR : " << mot << std::endl;
                            file >> mot;
                        }
                        else
                        {
                            ressource.music.setLoop(true);
                            ressource.music.stop();
                            file>>mot;
                            ressource.nom = mot;
                            _musics.push_back(&ressource);
                        }
                        mot = "";
                        file >> mot;
                    }
                }
                if(mot == "[SOUND]")
                {
                    mot = "";
                    file >> mot;

                    while(mot != "[TEXTURE]" && mot != "[MUSIC]" && mot != "[FONTS]" && mot != "[TILE]" && mot !="[ENTITE]" && !file.eof())
                    {

                        RSound ressource;

                        if(!ressource.buffer.loadFromFile(mot))
                        {
                            std::cout << "SOUND BUFFER LOAD ERROR : " << mot << std::endl;
                            file >> mot;
                        }
                        else
                        {
                            ressource.sound.setBuffer(ressource.buffer);
                            ressource.sound.stop();

                            file>>mot;
                            ressource.nom = mot;
                            _sounds.push_back(&ressource);
                        }
                        mot = "";
                        file >> mot;
                    }
                }
                if (mot == "[TILE]")
                {
                    mot = "";
                    file >> mot;

                    while(mot != "[FONTS]" && mot != "[SOUND]" && mot != "[MUSIC]" && mot != "[TEXTURE]" && mot !="[ENTITE]" && !file.eof())
                    {

                        RTile ressource;

                        if(!ressource.texture.loadFromFile(mot))
                        {
                            std::cout << "ENTITE LOAD ERROR : " << mot << std::endl;
                            file >> mot;
                        }
                        else
                        {
                            file>>mot;
                            ressource.nom = mot;
                            _tiles.push_back(ressource);
                        }
                        mot = "";
                        file >> mot;
                    }

                }
                if(mot == "[ENTITE]")
                {
                    mot = "";
                    file >> mot;

                    while(mot != "[FONTS]" && mot != "[SOUND]" && mot != "[MUSIC]" && mot != "[TEXTURE]" && mot !="[TILE]" && !file.eof())
                    {

                        REntite ressource;

                        if(!ressource.texture.loadFromFile(mot))
                        {
                            std::cout << "ENTITE LOAD ERROR : " << mot << std::endl;
                            file >> mot;
                        }
                        else
                        {
                            file>>mot;
                            ressource.nom = mot;
                            _entites.push_back(ressource);
                        }
                        mot = "";
                        file >> mot;
                    }

                }
            }
            mot = "";

        }

    }
    else
    {
        error << "Impossible de lire le fichier Ressources/Graphics.graphic" << std::endl;
    }

}

RSound* RessourceManager::getSound(int id)
{
    if(id < 0 || id >= (int)_sounds.size())
        return _sounds[0];
    else
        return _sounds[id];

}

RSound* RessourceManager::getSound(std::string nom)
{
    for(int i = 0; i < (int)_sounds.size(); i++)
    {
        if(nom == _sounds[i]->nom)
            return _sounds[i];
    }
    return _sounds[0];
}


sf::Texture& RessourceManager::getTexture(int id)
{
    if(id < 0 || id >= (int)_textures.size())
        return _textures[0].texture;
    else
        return _textures[id].texture;
}

sf::Texture& RessourceManager::getTexture(std::string nom)
{
    for(int i = 0; i < (int)_textures.size(); i++)
    {
        if(nom == _textures[i].nom)
            return _textures[i].texture;
    }
    return _textures[0].texture;
}

RMusic* RessourceManager::getMusic(int id)
{
    if(id < 0 || id >= (int)_musics.size())
        return _musics[0];
    else
        return _musics[id];
}

RMusic* RessourceManager::getMusic(std::string nom)
{
    for(int i = 0; i < (int)_musics.size(); i++)
    {
        if(nom == _musics[i]->nom)
            return _musics[i];
    }
    return _musics[0];
}

sf::Font& RessourceManager::getFont(int id)
{
    if(id < 0 || id >= (int)_fonts.size())
        return _fonts[0].font;
    else
    {
        return _fonts[id].font;
    }
}

sf::Font& RessourceManager::getFont(std::string nom)
{
    for(int i = 0; i < (int)_fonts.size(); i++)
    {
        if(nom == _fonts[i].nom)
        {
            return _fonts[i].font;
        }

    }
    return _fonts[0].font;
}

sf::Texture& RessourceManager::getTile(int id)
{
     if(id < 0 || id >= (int)_tiles.size())
        return _tiles[0].texture;
    else
    {
        return _tiles[id].texture;
    }
}
sf::Texture& RessourceManager::getTile(std::string nom)
{
    for(int i = 0; i < (int)_tiles.size(); i++)
    {
        if(nom == _tiles[i].nom)
        {
            return _tiles[i].texture;
        }

    }
    return _tiles[0].texture;
}

sf::Texture& RessourceManager::getEntite(int id)
{
    if(id < 0 || id >= (int)_entites.size())
        return _entites[0].texture;
    else
    {
        return _entites[id].texture;
    }
}
sf::Texture& RessourceManager::getEntite(std::string nom)
{
    for(int i = 0; i < (int)_entites.size(); i++)
    {
        if(nom == _entites[i].nom)
        {
            return _entites[i].texture;
        }

    }
    return _entites[0].texture;
}

int RessourceManager::getTileSize()
{
    return _tiles.size();
}
int RessourceManager::getEntiteSize()
{
    return _entites.size();
}


