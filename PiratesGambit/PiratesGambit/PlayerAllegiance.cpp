#include "PlayerAllegiance.h"

void PlayerAllegiance::updateAllegianceLevel()
{
    if (allegianceValue <= 20) allegianceLevel = AllegianceLevel::Hostile;
    else if (allegianceValue > 80) allegianceLevel = AllegianceLevel::Friendly;
    else allegianceLevel = AllegianceLevel::Neutral;
}
