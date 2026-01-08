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
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}

void Game::update(float dt) {
    //aquarium.update(dt);
}

void Game::render() {
    window.clear();
    aquarium.draw(window);
    window.display();
}

