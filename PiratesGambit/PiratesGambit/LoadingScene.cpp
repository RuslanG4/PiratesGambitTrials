#include "LoadingScene.h"

#include "GamePlayScene.h"
#include "MainMenuScene.h"
#include "SceneManager.h"

LoadingScene::LoadingScene()
{
    generationThread = std::thread([this]() {
        Scene* newScene = generateNextScene();

        {
            std::lock_guard<std::mutex> lock(sceneMutex);
            nextScene = newScene;
            //sf::sleep(sf::milliseconds(1000));
            sceneReady = true;
        }
        });

    if (!font.loadFromFile("ASSETS\\FONTS\\VarsityTeam-Bold.otf"))
    {
        std::cout << "I wanna die";
    }

    background.setTexture(TextureManager::getInstance().getTexture("SEA_BG"));
    background.setScale(10, 9);

    loadingText.setFont(font);
    loadingText.setString("Loading...");
    loadingText.setCharacterSize(70);
    loadingText.setFillColor(sf::Color(212, 175, 55));
    loadingText.setOutlineColor(sf::Color::Black);
    loadingText.setOutlineThickness(10.f);

    rotatingSquare.setTexture(TextureManager::getInstance().getTexture("WHEEL"));
    rotatingSquare.setOrigin(16, 16); // Set origin to center for smooth rotation
    rotatingSquare.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); // Center of screen
    rotatingSquare.setScale(9, 9);

    toolTips = loadTooltips("ASSETS/FILES/toolTips.txt");

    int randomToolTip = rand() % toolTips.size();

    toolTipText.setFont(font);
    toolTipText.setString(toolTips[randomToolTip]);
    toolTipText.setCharacterSize(50);
    toolTipText.setFillColor(sf::Color(212, 175, 55));
    toolTipText.setOutlineColor(sf::Color::Black);
    toolTipText.setOutlineThickness(10.f);

    centerText(loadingText, -300);
    centerText(toolTipText, 300);
}

void LoadingScene::handleInput(const std::unique_ptr<sf::RenderWindow>& window, sf::Event newEvent)
{
    if (sceneReady) {
    	if (newEvent.type == sf::Event::KeyPressed || newEvent.type == sf::Event::MouseButtonPressed) {
    		SceneManager::getInstance().setScene(nextScene);
    	}
    }
}

void LoadingScene::update(float dt)
{
    if (!sceneReady) {
        rotatingSquare.rotate(rotationSpeed * (dt * 0.001f));
    }
    else {
        loadingText.setString("Press to continue...");
        centerText(loadingText, -300);

        float time = clock.getElapsedTime().asSeconds();

        int alpha = static_cast<int>(127.5f * (std::sin(time * 3.0f) + 1.0f)); // Range: 0 to 255

        sf::Color textColor = loadingText.getFillColor();
        textColor.a = alpha;
        sf::Color textOutlineColor = loadingText.getOutlineColor();
        textOutlineColor.a = alpha;
        loadingText.setFillColor(textColor);
        loadingText.setOutlineColor(textOutlineColor);
    }

}

void LoadingScene::render(const std::unique_ptr<sf::RenderWindow>& window)
{
    window->draw(background);
    window->draw(loadingText);
    window->draw(toolTipText);
    if(!sceneReady)
        window->draw(rotatingSquare);
}

std::vector<std::string> LoadingScene::loadTooltips(const std::string& filename)
{
    std::vector<std::string> tooltips;

    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    for (std::string line; std::getline(file, line); ) {
        if (!line.empty()) {
            tooltips.emplace_back(std::move(line));
        }
    }

    return tooltips;
}

void LoadingScene::centerText(sf::Text& _text, int _y)
{
    sf:: FloatRect textBounds = _text.getLocalBounds();

    _text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    _text.setPosition(rotatingSquare.getPosition().x, rotatingSquare.getPosition().y + _y);
}

Scene* LoadingScene::generateNextScene()
{
    auto gamePlayScene = new GamePlayScene();
    return gamePlayScene; // Replace with your actual scene
}
