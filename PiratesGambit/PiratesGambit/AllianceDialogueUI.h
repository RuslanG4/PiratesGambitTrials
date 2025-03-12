#pragma once
#include "Button.h"
#include "IconButton.h"
#include"Includes.h"

class AllianceDialogueUI {
public:
    static AllianceDialogueUI& getInstance() {
        static AllianceDialogueUI instance;
        return instance;
    }

    void Init();

    void UpdateText();

    void Update();

    void OpenMenu();
    void CloseMenu();

    bool isMenuOpen() const { return isOpen; }

    void setAllianceLevel(int level);

    void Render(const std::unique_ptr<sf::RenderWindow>& _window) const;

private:
    AllianceDialogueUI() : textSpeed(10), charIndex(0)
    {
        Init();
    }
    AllianceDialogueUI(const AllianceDialogueUI&) = delete;
    void operator=(const AllianceDialogueUI&) = delete;

    void ScaleTextToFit();

    bool isOpen = false;

    sf::RectangleShape background;
    sf::Sprite dialogueBox;
    sf::Sprite characterPortrait;
    sf::CircleShape allianceIndicator;

    std::unique_ptr<IconButton> exitButton;
    std::unique_ptr<IconButton> purchaseButton;

    sf::Text dialogueText;

    std::string fullText;
    std::string currentText;
    int charIndex;
    sf::Clock clock;
    int textSpeed; // Milliseconds per character
};


