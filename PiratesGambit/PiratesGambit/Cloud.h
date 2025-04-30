#pragma once
#include"Includes.h"
#include"TextureManager.h"
class Cloud
{
public:
	Cloud(sf::Vector2f _pos, sf::Vector2f _vel)
	{
		cloudSprite.setTexture(TextureManager::getInstance().getTexture("CLOUD"));
		cloudSprite.setPosition(_pos);
		cloudSprite.setOrigin(48, 48);

		vel = _vel;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> scaleDist(1.0f, 3.0f);
		std::uniform_real_distribution<float> lifeTimeDist(8.0f, 20.0f);

		float scale = scaleDist(gen);
		cloudSprite.setScale(scale, scale);
	
		lifetime = lifeTimeDist(gen);
		timeAlive = 0.0f;
	}
	bool isMarkedForDeletion() const { return animationFinish; }

	void Update(float _dt)
	{
		timeAlive += _dt * 0.001f;
		if (timeAlive > lifetime)
			animationFinish = true;


		cloudSprite.setPosition(cloudSprite.getPosition() + vel);
		float progress = timeAlive / lifetime;
		float alpha = 40 * (1.0f - (timeAlive / lifetime));
		cloudSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));

	}
	void Render(const std::unique_ptr<sf::RenderWindow>& window) const
	{
		window->draw(cloudSprite);

	}
private:
	sf::Sprite cloudSprite;
	sf::Vector2f vel;
	float lifetime;
	float timeAlive;
	bool animationFinish{ false };
};

