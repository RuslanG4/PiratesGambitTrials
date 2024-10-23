#pragma once
#include"Includes.h"


class TextureManager {
public:
    static TextureManager& getInstance() {
        static TextureManager instance;
        instance.loadTexture("landTile", LAND_SPRITE);
        instance.loadTexture("grassyLandTile", GRASSY_LAND_SPRITE);
        instance.loadTexture("sandTile", SAND_SPRITE);
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