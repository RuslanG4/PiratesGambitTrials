#pragma once
#include "Includes.h"

class TextureManager {
public:
    static TextureManager& getInstance() {
        static TextureManager instance;
        return instance;
    }

    // Explicit loading function
    bool loadAllResources() {
        bool fontsLoaded = loadFont(FONT);
        bool texturesLoaded = true;

        texturesLoaded &= loadTexture("landTile", LAND_SPRITE);
        texturesLoaded &= loadTexture("grassyLandTile", GRASSY_LAND_SPRITE);
        texturesLoaded &= loadTexture("sandTile", SAND_SPRITE);
        texturesLoaded &= loadTexture("TRsandTile", SAND_TR);
        texturesLoaded &= loadTexture("TLsandTile", SAND_TL);
        texturesLoaded &= loadTexture("BRsandTile", SAND_BR);
        texturesLoaded &= loadTexture("BLsandTile", SAND_BL);
        texturesLoaded &= loadTexture("flatTop", SAND_FT);
        texturesLoaded &= loadTexture("flatBottom", SAND_FB);
        texturesLoaded &= loadTexture("flatLeft", SAND_FL);
        texturesLoaded &= loadTexture("flatRight", SAND_FR);
        texturesLoaded &= loadTexture("LLSANDTR", TR_LANDLOCK);
        texturesLoaded &= loadTexture("LLSANDTL", TL_LANDLOCK);
        texturesLoaded &= loadTexture("LLSANDBR", BR_LANDLOCK);
        texturesLoaded &= loadTexture("LLSANDBL", BL_LANDLOCK);
        texturesLoaded &= loadTexture("waterTile", WATER_SPRITE);
        texturesLoaded &= loadTexture("PLAYER_BOAT", PLAYER);
        texturesLoaded &= loadTexture("PLAYER_BOAT_DAMAGED", PLAYER_DAMAGED);
        texturesLoaded &= loadTexture("PLAYER_BOAT_PLASTERED", PLAYER_PLASTERED);
        texturesLoaded &= loadTexture("RED_BOAT", RED_SHIP_HEALTHY);
        texturesLoaded &= loadTexture("CANNON_BALL", CANNON_BALL);
        texturesLoaded &= loadTexture("HARPOON", HARPOON);
        texturesLoaded &= loadTexture("PIRATE_CAPTAIN", PIRATE_CAPTAIN);
        texturesLoaded &= loadTexture("BUCCANEER", BUCCANEER_SPRITE);
        texturesLoaded &= loadTexture("GUNNER", GUNNER_SPRITE);
        texturesLoaded &= loadTexture("HARPOONER", HARPOONER_SPRITE);
        texturesLoaded &= loadTexture("BARREL", BARREL);
        texturesLoaded &= loadTexture("TREEA", TREE0);
        texturesLoaded &= loadTexture("TREEB", TREE1);
        texturesLoaded &= loadTexture("CANNON_BALL_ICON", CANNON_BALL_ICON);
        texturesLoaded &= loadTexture("SWORD_ICON", SWORD_ICON);
        texturesLoaded &= loadTexture("SHOOT_ICON", SHOOT_ICON);
        texturesLoaded &= loadTexture("MONEY_ICON", MONEY_ICON);
        texturesLoaded &= loadTexture("COIN_ICON", COIN_ICON);
        texturesLoaded &= loadTexture("SKULL_ICON", SKULL_ICON);
        texturesLoaded &= loadTexture("ACTION_BORDER", ACTION_BORDER);
        texturesLoaded &= loadTexture("BULKY_BORDER", BULKY_BORDER);
        texturesLoaded &= loadTexture("BLOOD_PARTICLES", BLOOD_PARTICLES);
        texturesLoaded &= loadTexture("SHOOT_PARTICLES", SHOOT_PARTICLES);
        texturesLoaded &= loadTexture("LEAF_PARTICLE", LEAF_PARTICLE);
        texturesLoaded &= loadTexture("PLAYER_MENU_UI", PLAYER_MENU_UI);
        texturesLoaded &= loadTexture("ARMY_MENU_UI", ARMY_MENU_UI);
        texturesLoaded &= loadTexture("background", BACKGROUND);
        texturesLoaded &= loadTexture("BUILDINGS", BUILDINGS);
        texturesLoaded &= loadTexture("SEA_BG", SEA_BG);
        texturesLoaded &= loadTexture("BUTTONS", BUTTONS);
        texturesLoaded &= loadTexture("WHEEL", WHEEL);
        texturesLoaded &= loadTexture("PIRATE_ONE", PIRATE_ONE);
        texturesLoaded &= loadTexture("POP_UP", POP_UP);

        return fontsLoaded && texturesLoaded;
    }

    sf::Font& getFont() {
        return *globalFont;
    }

    sf::Texture& getTexture(const std::string& name) {
        return textures[name];
    }

    bool isFontLoaded() const { return fontLoaded; }

    TextureManager(TextureManager const&) = delete;
    void operator=(TextureManager const&) = delete;

private:
    TextureManager() {}  // Make constructor private

    bool loadTexture(const std::string& name, const std::string& filename) {
        sf::Texture texture;
        if (texture.loadFromFile(filename)) {
            textures[name] = texture;
            return true;
        }
        return false;
    }

    bool loadFont(const std::string& filename) {
        globalFont = std::make_unique<sf::Font>();
        if (globalFont->loadFromFile("ASSETS\\FONTS\\VarsityTeam-Bold.otf")) {
            fontLoaded = true;
            return true;
        }
        return false;
    }
    bool fontLoaded = false;
    std::map<std::string, sf::Texture> textures;
    std::unique_ptr<sf::Font> globalFont;
};
