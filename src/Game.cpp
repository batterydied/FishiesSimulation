#include "Game.hpp"
#include <iostream>
#include "Aquarium.hpp"

Game::Game()
    : window(sf::VideoMode({1400, 800}), "Fishies Simulation"),
      aquarium(1400, 800)
{
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        float dt = clock.restart().asSeconds();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    const float targetRatio = 16.f / 9.f;
    const sf::Vector2f baseSize(1400, 800);

    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (const auto* resized = event->getIf<sf::Event::Resized>()) {
            handleResize(window, *resized, targetRatio, baseSize);
        }
    }
}

void Game::handleResize(sf::RenderWindow& window, const sf::Event::Resized& resized,
                  float targetRatio, const sf::Vector2f& baseSize)
{
    float windowRatio = static_cast<float>(resized.size.x) / resized.size.y;

    // Create view in base coordinates
    sf::View view(sf::FloatRect(sf::Vector2f(0.f, 0.f), baseSize));

    // Always full window
    view.setViewport(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f)));

    if (windowRatio > targetRatio) {
        // Too wide → crop sides
        float scale = windowRatio / targetRatio;
        view.setSize(sf::Vector2f(baseSize.x * scale, baseSize.y));
    } else {
        // Too tall → crop top/bottom
        float scale = targetRatio / windowRatio;
        view.setSize(sf::Vector2f(baseSize.x, baseSize.y * scale));
    }

    window.setView(view);
}

void Game::update(float dt) {
    aquarium.update(dt);
}

void Game::render() {
    window.clear();
    aquarium.draw(window);
    window.display();
}

