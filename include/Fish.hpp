#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

static constexpr int NUM_TEXTURES = 4; 

enum class FishSpecies {
    CLOWNFISH,
    VANDERBILT_CHROMIS,
    PURPLE_TANG,
    BLUE_TANG,
    ROYAL_GRAMMA
};

class Fish {
public:
    // Constructor
    Fish(sf::Vector2f startPosition);

    // Update fish state (movement, behavior)
    void update(float deltaTime);

    void updateSpriteByTime(float deltaTime);

    // Draw fish to the window
    void draw(sf::RenderWindow& window) const;

    void setTextures(FishSpecies species);

    void maybeChangeDirection(float deltaTime);

private:
    int currentTextureIndex = 0;    // which texture is showing now
    float animationTimer = 0.f;     // counts time
    float animationInterval = 0.15f;  // seconds per frame

    std::vector<sf::Texture> textures;
    sf::Vector2f velocity;
    std::optional<sf::Sprite> sprite;
    float directionCooldown;

    std::string getFishSpeciesName(FishSpecies species);
    void setTextures(std::string speciesName);
    void handleBounds();
};