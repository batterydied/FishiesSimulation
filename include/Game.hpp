#pragma once
#include <SFML/Graphics.hpp>
#include "Aquarium.hpp"
#include "FishUtility.hpp"

class Game {
public:
    Game();;
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();
    void handleResize(sf::RenderWindow& window, const sf::Event::Resized& resized, float targetRatio, const sf::Vector2f& baseSize);
    
    sf::RenderWindow window;
    sf::Clock clock;

    Aquarium aquarium;
    FishUtility utility;
};
