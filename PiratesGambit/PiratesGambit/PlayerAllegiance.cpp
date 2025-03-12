#include "PlayerAllegiance.h"

void PlayerAllegiance::updateAllegianceLevel()
{
    if (allegianceValue < 0) {
        allegianceLevel = AllegianceLevel::Hostile;
    }
    else if (allegianceValue == 0) {
        allegianceLevel = AllegianceLevel::Neutral;
    }
    else {
        allegianceLevel = AllegianceLevel::Friendly;
    }
}
