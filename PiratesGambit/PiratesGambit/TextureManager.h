#pragma once
#include"Includes.h"


class TextureManager {
public:
    static TextureManager& getInstance() {
        static TextureManager instance;
        return instance;
    }

    bool loadTexture(const std::string& name, const std::string& filename) {
        sf::Texture texture;
        if (texture.loadFromFile(filename)) {
            textures[name] = texture;
            return true;
        }
        return false;
    }

    bool loadFont(const std::string& filename)
    {
        sf::Font font;
        if (font.loadFromFile(filename)) {
            globalFont = font;
            return true;
        }
        return false;
    }

    sf::Font& getFont()
    {
        return globalFont;
    }

    sf::Texture& getTexture(const std::string& name) {
        return textures[name];
    }

    TextureManager(TextureManager const&) = delete;
    void operator=(TextureManager const&) = delete;

private:
    TextureManager()
    {
        loadFont(FONT);
        //
        loadTexture("landTile", LAND_SPRITE);
        loadTexture("grassyLandTile", GRASSY_LAND_SPRITE);
        loadTexture("sandTile", SAND_SPRITE);
        //sand corners
        loadTexture("TRsandTile", SAND_TR);
        loadTexture("TLsandTile", SAND_TL);
        loadTexture("BRsandTile", SAND_BR);
        loadTexture("BLsandTile", SAND_BL);
        //snad flats
        loadTexture("flatTop", SAND_FT);
        loadTexture("flatBottom", SAND_FB);
        loadTexture("flatLeft", SAND_FL);
        loadTexture("flatRight", SAND_FR);
        //sand land locked corners
        loadTexture("LLSANDTR", TR_LANDLOCK);
        loadTexture("LLSANDTL", TL_LANDLOCK);
        loadTexture("LLSANDBR", BR_LANDLOCK);
        loadTexture("LLSANDBL", BL_LANDLOCK);
        ///
        loadTexture("waterTile", WATER_SPRITE);
        //SHIPS
        loadTexture("PLAYER_BOAT", PLAYER);
        loadTexture("PLAYER_BOAT_DAMAGED", PLAYER_DAMAGED);
        loadTexture("PLAYER_BOAT_PLASTERED", PLAYER_PLASTERED);
        loadTexture("CANNON_BALL", CANNON_BALL);
        //
        loadTexture("PIRATE_CAPTAIN", PIRATE_CAPTAIN);
        //
        loadTexture("BARREL", BARREL);
        //ICONS
    	loadTexture("CANNON_BALL_ICON", CANNON_BALL_ICON);
        
    }

    std::map<std::string, sf::Texture> textures;

    sf::Font globalFont;
};