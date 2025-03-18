#include "Tree.h"

#include "BarrelInventory.h"
#include "Camera.h"
#include "ParticleManager.h"
#include "TextureManager.h"

Tree::Tree()
{
	inventory = std::make_unique<Inventory>();


	renderableInventory = std::make_unique<BarrelInventory>(4, 2);
	int randO = rand() % 2;
	if(randO == 1)
	{
		sprite.setTexture(TextureManager::getInstance().getTexture("TREEA"));
		
	}else
	{
		sprite.setTexture(TextureManager::getInstance().getTexture("TREEB"));
	}
	sprite.setOrigin(16, 46);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(1.5f, 2.f); 

	scale = dist(gen);

	sprite.setScale(scale, scale);

	myHitbox = std::make_unique<HitBox>(sf::Vector2f(12, 5));

	animationTime = static_cast<float>(rand() % 100) / 100.0f;
}

void Tree::render(const std::unique_ptr<sf::RenderWindow>& window)
{
	window->setView(Camera::getInstance().getCamera());
	window->draw(sprite);
	for (auto& leaf : leafParticles)
	{
		leaf.Render(window);
	}
	//myHitbox->render(window);
}

void Tree::interact()
{
}

void Tree::update(float _dt)
{
	animationTime += _dt * 0.001; 
	animateRandomizedTreeSway(animationTime);

	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> chance(0.f, 1.f);

	if (chance(gen) < 0.0015f) // 0.15% chance per frame
	{
		sf::Vector2f leafPos = sprite.getPosition();
		leafPos.y -= (rand() % 20) + 30;
		leafPos.x += (rand() % 10 - 5) * scale;
		leafParticles.emplace_back(leafPos);
	}

	for(auto& leaf : leafParticles)
	{
		leaf.Update(_dt);
	}

	std::erase_if(leafParticles, [](const Particle& particle) {
		return particle.isMarkedForDeletion();
		});

}

void Tree::animateRandomizedTreeSway(float _dt)
{
	float swayAmount = 0.03f;  // Max sway variation (2%)
	float swaySpeed = 2.0f;

	float offset = static_cast<float>(sprite.getPosition().x) * 0.1f;
	float scaleX = scale * (1.0f + std::sin(_dt * swaySpeed + offset) * swayAmount);

	sprite.setScale(scaleX, scale);  // Keep Y scale consistent
}

void Tree::RenderUI(const std::unique_ptr<sf::RenderWindow>& _window)
{
}
