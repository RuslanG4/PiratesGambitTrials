#include "ProgressBar.h"

ProgressBar::ProgressBar(sf::Vector2f _pos)
{
    backgroundBar.setSize(sf::Vector2f(300, 20));
    backgroundBar.setFillColor(sf::Color(50, 50, 50));
    backgroundBar.setPosition(_pos);

    progressBar.setSize(sf::Vector2f(backgroundBar.getSize().x, 20));
    progressBar.setFillColor(sf::Color(0, 200, 0));
    progressBar.setPosition(_pos);
}

void ProgressBar::Render(const std::unique_ptr<sf::RenderWindow>& _win) const
{
    _win->draw(backgroundBar);
    _win->draw(progressBar);
}

void ProgressBar::Update()
{
    if (!isActive) {
        float elapsed = timer.getElapsedTime().asSeconds();

        if (elapsed >= 20.f) {
            isActive = true;
        }
        float progress = (elapsed / 20.f) * backgroundBar.getSize().x;
        progressBar.setSize(sf::Vector2f(progress, progressBar.getSize().y));
    }
}
