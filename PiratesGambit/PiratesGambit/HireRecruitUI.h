#pragma once
#include "AnimatedCharacterIcon.h"
#include"Includes.h"
#include "Structs.h"
#include"InfoBoxUI.h"
#include "BuccaneerIcon.h"
#include "GunnerIcon.h"
#include "Slider.h"
#include"IconButton.h"
#include"Player.h"
#include "ProgressBar.h"

class HireRecruitUI
{
public:
    // Singleton Accessor
    static HireRecruitUI& getInstance() {
        static HireRecruitUI instance; 
        return instance;
    }

    void SetUpUi();

    void PassUI(UnitName _type, int _unitAmount, Building& building);
    void PassPlayer(std::shared_ptr<Player>& _playerRef) { playerRef = _playerRef; }

    // Delete copy constructor & assignment operator (Singleton Rule)
    HireRecruitUI(const HireRecruitUI&) = delete;
    HireRecruitUI& operator=(const HireRecruitUI&) = delete;

    void SetCharacter();
    void AddCharacterToPlayer() const;
    void resetValues();

    void Render(const std::unique_ptr<sf::RenderWindow>& _window) const;
    void Update(float _dt);

    void OpenUI();
    void CloseUI();

    static bool IsUIOpen() { return uiOpen; }
    bool IsMenuOpen() const { return isMenuOpen; }


private:
    // Private Constructor (Only accessible via getInstance)
    HireRecruitUI()
    {
        SetUpUi();
    }

    std::shared_ptr<Player> playerRef;
    UnitName nameOfUnitSelling;

    static bool uiOpen;
    bool isMenuOpen{ false };
    bool resetValue = false;
    int unitsLeftReference;
    int availableUnits;

    sf::Sprite background;
    sf::Sprite unit;
    AnimationState animationState;

    Building* buildingRef;

    std::unique_ptr<ProgressBar> progressBar;
    std::unique_ptr<InfoBoxUI> costPerTroop;
    std::unique_ptr<InfoBoxUI> totalCost;
    std::unique_ptr<InfoBoxUI> available;
    std::unique_ptr<InfoBoxUI> recruit;
    std::unique_ptr<IconButton> purchase;
    std::unique_ptr<IconButton> cancel;
    std::unique_ptr<AnimatedCharacterIcon> unitIcon;
    std::unique_ptr<Slider> amountSlider;
};

