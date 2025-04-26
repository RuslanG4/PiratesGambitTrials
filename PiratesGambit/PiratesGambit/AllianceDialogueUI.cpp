#include "AllianceDialogueUI.h"
#include"FollowPlayerState.h"
#include "TextureManager.h"

void AllianceDialogueUI::Init()
{
    background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    background.setFillColor(sf::Color(0, 0, 0, 150)); // Semi-transparent gray

    dialogueBox.setTexture(TextureManager::getInstance().getTexture("PLAYER_MENU_UI"));
    dialogueBox.setScale(9, 8);
    dialogueBox.setPosition(SCREEN_WIDTH / 2 - dialogueBox.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - dialogueBox.getGlobalBounds().height / 2);

    characterPortrait.setTexture(TextureManager::getInstance().getTexture("PIRATE_ONE"));
    characterPortrait.setScale(8,8);
    characterPortrait.setPosition(dialogueBox.getPosition() + sf::Vector2f(100,80));

    dialogueText.setFont(TextureManager::getInstance().getFont("Comic"));
    dialogueText.setCharacterSize(36U);
    dialogueText.setFillColor(sf::Color::White);

    costText.setPosition(characterPortrait.getPosition().x + characterPortrait.getGlobalBounds().width + 50, characterPortrait.getPosition().y + 150);

    exitButton = std::make_unique<IconButton>(2, 2,
        sf::Vector2f(dialogueBox.getPosition().x + 300, dialogueBox.getPosition().y + 600),
        TextureManager::getInstance().getTexture("CLOSE_ICON"));

    purchaseButton = std::make_unique<IconButton>(2, 2,
        sf::Vector2f(dialogueBox.getPosition().x + dialogueBox.getGlobalBounds().width - 300, dialogueBox.getPosition().y + 600),
        TextureManager::getInstance().getTexture("MONEY_ICON"));

    allianceStatus = std::make_unique<AllianceStatusUI>(characterPortrait.getPosition() + sf::Vector2f(350, 0));

    UpdateText();
}

void AllianceDialogueUI::UpdateText()
{
    fullText = "Arr, ye be lookin’ for a crew, eh? \n"
			   "I’ve got me finest scallywags,\n"
	  "but they don’t work for free!\n"
   "Pay up, or walk the plank!";
    currentText = "";
    charIndex = 0;
    clock.restart();
    ScaleTextToFit();
}

void AllianceDialogueUI::Update()
{
    if (isOpen) {
        if (charIndex < fullText.size()) {
            if (clock.getElapsedTime().asMilliseconds() > textSpeed) {
                currentText += fullText[charIndex];
                dialogueText.setString(currentText);
                charIndex++;
                clock.restart();
            }
        }

        exitButton->Update();
        purchaseButton->Update();

        if(exitButton->IsTriggered())
        {
            CloseMenu();
        }
        if (purchaseButton->IsTriggered()) {
            enemyRef->ChangeState(new FollowPlayerState(playerRef));
            CloseMenu();
        }
    }
}

void AllianceDialogueUI::OpenMenu(const std::shared_ptr<Enemy>& _enemyRef, const std::shared_ptr<Player>& _playerRef)
{
    playerRef = _playerRef;
    enemyRef = _enemyRef;
    dialogueText.setString("");
    isOpen = true;
    UpdateText();
	allianceStatus->updateAllegianceLevel(_enemyRef->GetPlayerAllegiance().getAllegianceLevel());
    allianceStatus->PlaceIndicatorOnAllegianceBar(_enemyRef->GetPlayerAllegiance().getAllegianceValue());
}

void AllianceDialogueUI::CloseMenu()
{
    isOpen = false;
    exitButton->ResetTrigger();
    purchaseButton->ResetTrigger();
}

void AllianceDialogueUI::Render(const std::unique_ptr<sf::RenderWindow>& _window) const
{
    if (isOpen) {
        _window->setView(_window->getDefaultView());
        _window->draw(background);
        _window->draw(dialogueBox);
        _window->draw(characterPortrait);
        _window->draw(dialogueText);
        _window->draw(allianceIndicator);
        allianceStatus->Render(_window);
        purchaseButton->Render(_window);
        exitButton->Render(_window);
    }
}

void AllianceDialogueUI::ScaleTextToFit()
{
    sf::Vector2f position{
        dialogueBox.getPosition().x,
        dialogueBox.getPosition().y + 300
    };
    dialogueText.setPosition(position.x + 100, position.y + 50);

}
