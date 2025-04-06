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
        bool fontsLoaded= true;
        bool texturesLoaded = true;

        fontsLoaded &= loadFont("Roboto", ROBOTO_FONT);
        fontsLoaded &= loadFont("Comic", ROBOTO_FONT);
        fontsLoaded &= loadFont("Varsity", VARSITY_FONT);

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
        texturesLoaded &= loadTexture("CANNON_BALL", CANNON_BALL);
        texturesLoaded &= loadTexture("HARPOON", HARPOON);
        texturesLoaded &= loadTexture("PIRATE_CAPTAIN", PIRATE_CAPTAIN);
        texturesLoaded &= loadTexture("BUCCANEER", BUCCANEER_SPRITE);
        texturesLoaded &= loadTexture("GUNNER", GUNNER_SPRITE);
        texturesLoaded &= loadTexture("HARPOONER", HARPOONER_SPRITE);
        texturesLoaded &= loadTexture("CANNON_UNIT", CANNON_UNIT_SPRITE);
        texturesLoaded &= loadTexture("BIRD", BIRD_SPRITE);
        texturesLoaded &= loadTexture("BARREL", BARREL_SPRITE);
        texturesLoaded &= loadTexture("TREEA", TREE0);
        texturesLoaded &= loadTexture("TREEB", TREE1);
        texturesLoaded &= loadTexture("CANNON_BALL_ICON", CANNON_BALL_ICON);
        texturesLoaded &= loadTexture("INDICATOR_ICON", INDICATOR_ICON);
        texturesLoaded &= loadTexture("SWORD_ICON", SWORD_ICON);
        texturesLoaded &= loadTexture("SHOOT_ICON", SHOOT_ICON);
        texturesLoaded &= loadTexture("MONEY_ICON", MONEY_ICON);
        texturesLoaded &= loadTexture("CHEST_ICON", CHEST_ICON);
        texturesLoaded &= loadTexture("COIN_ICON", COIN_ICON);
        texturesLoaded &= loadTexture("SKULL_ICON", SKULL_ICON);
        texturesLoaded &= loadTexture("ACTION_BORDER", ACTION_BORDER);
        texturesLoaded &= loadTexture("BULKY_BORDER", BULKY_BORDER);
        texturesLoaded &= loadTexture("BLOOD_PARTICLES", BLOOD_PARTICLES);
        texturesLoaded &= loadTexture("SHOOT_PARTICLES", SHOOT_PARTICLES);
        texturesLoaded &= loadTexture("EXPLOSION_PARTICLE", EXPLOSION_PARTICLE);
        texturesLoaded &= loadTexture("LEAF_PARTICLE", LEAF_PARTICLE);
        texturesLoaded &= loadTexture("SMOKE_PARTICLE", SMOKE_PARTICLE);
        texturesLoaded &= loadTexture("PLAYER_MENU_UI", PLAYER_MENU_UI);
        texturesLoaded &= loadTexture("ARMY_MENU_UI", ARMY_MENU_UI);
        texturesLoaded &= loadTexture("background", BACKGROUND);
        texturesLoaded &= loadTexture("BUILDINGS", BUILDINGS);
        texturesLoaded &= loadTexture("SEA_BG", SEA_BG);
        texturesLoaded &= loadTexture("BUTTONS", BUTTONS);
        texturesLoaded &= loadTexture("WHEEL", WHEEL);
        texturesLoaded &= loadTexture("PIRATE_ONE", PIRATE_ONE);
        texturesLoaded &= loadTexture("POP_UP", POP_UP);

        //keys
        texturesLoaded &= loadTexture("V-KEY", V_KEY);
        texturesLoaded &= loadTexture("X-KEY", X_KEY);
        texturesLoaded &= loadTexture("E-KEY", E_KEY);
    //Boats
        texturesLoaded &= loadBoatTexture("Red","HEALTHY", RED_SHIP_HEALTHY);
        texturesLoaded &= loadBoatTexture("Red", "DAMAGED", RED_SHIP_DAMAGED);
        texturesLoaded &= loadBoatTexture("Red", "BROKEN", RED_SHIP_BROKEN);

        texturesLoaded &= loadBoatTexture("Yellow", "HEALTHY", YELLOW_SHIP_HEALTHY);
        texturesLoaded &= loadBoatTexture("Yellow", "DAMAGED", YELLOW_SHIP_DAMAGED);
        texturesLoaded &= loadBoatTexture("Yellow", "BROKEN", YELLOW_SHIP_BROKEN);

        texturesLoaded &= loadBoatTexture("Black", "HEALTHY", BLACK_SHIP_HEALTHY);
        texturesLoaded &= loadBoatTexture("Black", "DAMAGED", BLACK_SHIP_DAMAGED);
        texturesLoaded &= loadBoatTexture("Black", "BROKEN", BLACK_SHIP_BROKEN);

        texturesLoaded &= loadBoatTexture("Blue", "HEALTHY", BLUE_SHIP_HEALTHY);
        texturesLoaded &= loadBoatTexture("Blue", "DAMAGED", BLUE_SHIP_DAMAGED);
        texturesLoaded &= loadBoatTexture("Blue", "BROKEN", BLUE_SHIP_BROKEN);

        texturesLoaded &= loadBoatTexture("Green", "HEALTHY", GREEN_SHIP_HEALTHY);
        texturesLoaded &= loadBoatTexture("Green", "DAMAGED", GREEN_SHIP_DAMAGED);
        texturesLoaded &= loadBoatTexture("Green", "BROKEN", GREEN_SHIP_BROKEN);

        return fontsLoaded && texturesLoaded;
    }

    sf::Font& getFont(const std::string& name) {
        return fonts[name];
    }

    sf::Texture& getTexture(const std::string& name) {
        return textures[name];
    }

    sf::Texture& getBoatTexture(const std::string& parent, const std::string& name) {
        return boatTextures.at(parent).at(name);
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

    bool loadBoatTexture(const std::string& parent, const std::string& name, const std::string& filename) {
        sf::Texture texture;
        if (texture.loadFromFile(filename)) {
            boatTextures[parent][name] = std::move(texture);
            return true;
        }
        return false;
    }

    bool loadFont(const std::string& name, const std::string& filename) {
        sf::Font font;
        if (font.loadFromFile(filename)) {
            fonts[name] = font;
            return true;
        }
        return false;
    }
    bool fontLoaded = false;
    std::map<std::string, std::map<std::string, sf::Texture>> boatTextures;
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
};
