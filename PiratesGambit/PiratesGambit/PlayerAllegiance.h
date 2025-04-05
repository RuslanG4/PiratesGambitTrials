#pragma once
#include"Includes.h"

class PlayerAllegiance {
public:
    PlayerAllegiance() {
    }

	void changeAllegiance(int change) {
		allegianceValue += change;
		updateAllegianceLevel();
	}

    void setAllegiance(int value) {
        allegianceValue = value;
        updateAllegianceLevel();
    }

    int getAllegianceValue() const {
        return allegianceValue;
    }

    AllegianceLevel getAllegianceLevel() const {
        return allegianceLevel;
    }

    bool isFriendly() const {
        return allegianceLevel == AllegianceLevel::Friendly;
    }

    bool isHostile() const {
        return allegianceLevel == AllegianceLevel::Hostile;
    }

private:
    int allegianceValue; 
    AllegianceLevel allegianceLevel;

    void updateAllegianceLevel();
};

