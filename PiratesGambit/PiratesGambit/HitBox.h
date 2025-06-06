#pragma once
#include"Includes.h"

class HitBox
{
public:
	HitBox(sf::Vector2f _size) {
		hitbox.setSize(_size);
		hitbox.setFillColor(sf::Color::Transparent);
		hitbox.setOutlineThickness(2.f);
		hitbox.setOutlineColor(sf::Color::Black);
		hitbox.setOrigin(_size.x / 2, _size.y / 2);
	}

	void render(const std::unique_ptr<sf::RenderWindow>& window)const { window->draw(hitbox); }

	void setPosition(sf::Vector2f _pos) { hitbox.setPosition(_pos); }
	void setRotation(float _rotation) { hitbox.setRotation(_rotation); }
	sf::Vector2f getPosition() const { return hitbox.getPosition(); }
	sf::Vector2f getSize() const { return hitbox.getSize(); }

	sf::FloatRect GetGlobalBounds() const { return hitbox.getGlobalBounds(); }

	sf::Vector2f getTopLeftCorner() const { return { getPosition().x - getSize().x / 2, getPosition().y - getSize().y / 2 }; }
private:
	sf::RectangleShape hitbox;
};

