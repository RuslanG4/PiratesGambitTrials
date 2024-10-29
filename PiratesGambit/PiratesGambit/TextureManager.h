#pragma once
#include"Includes.h"


class TextureManager {
public:
    static TextureManager& getInstance() {
        static TextureManager instance;
        instance.loadTexture("landTile", LAND_SPRITE);
        instance.loadTexture("grassyLandTile", GRASSY_LAND_SPRITE);
        //sand corners
        instance.loadTexture("TRsandTile", SAND_TR);
        instance.loadTexture("TLsandTile", SAND_TL);
        instance.loadTexture("BRsandTile", SAND_BR);
        instance.loadTexture("BLsandTile", SAND_BL);
        //snad flats
        instance.loadTexture("flatTop", SAND_FT);
        instance.loadTexture("flatBottom", SAND_FB);
        instance.loadTexture("flatLeft", SAND_FL);
        instance.loadTexture("flatRight", SAND_FR);
        //sand land locked corners
        instance.loadTexture("LLSANDTR", TR_LANDLOCK);
        instance.loadTexture("LLSANDTL", TL_LANDLOCK);
        instance.loadTexture("LLSANDBR", BR_LANDLOCK);
        instance.loadTexture("LLSANDBL", BL_LANDLOCK);
        ///
        instance.loadTexture("waterTile", WATER_SPRITE);
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

    sf::Texture& getTexture(const std::string& name) {
        return textures[name];
    }

    TextureManager(TextureManager const&) = delete;
    void operator=(TextureManager const&) = delete;

private:
    TextureManager() {}

    std::map<std::string, sf::Texture> textures;
};