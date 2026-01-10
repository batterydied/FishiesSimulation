#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "FishUtility.hpp"

static constexpr int NUM_TEXTURES = 4; 

class Fish {
public:
    // Constructor
    Fish(FishSpecies species, RangeX& initXBounds, RangeY& initYBounds);

    // Update fish state (movement, behavior)
    void update(float deltaTime);

    void updateSpriteByTime(float deltaTime);

    // Draw fish to the window
    void draw(sf::RenderWindow& window);

    void setTextures(FishSpecies species);

private:
    int currentTextureIndex = 0;    // which texture is showing now
    float animationTimer = 0.f;     // counts time
    float animationInterval = 0.15f;  // seconds per frame

    std::array<sf::Texture, NUM_SPRITES> textures;
    sf::Vector2f velocity;
    std::optional<sf::Sprite> sprite;
    float directionCooldown;

    RangeX xBounds;
    RangeY yBounds;
    unsigned int size;

    std::string getFishSpeciesName(FishSpecies species);
    void setTextures(std::string speciesName);
    void handleBounds();
    void maybeChangeDirection(float deltaTime);
    void changeDirection();
};