#include "Fish.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <array>
#include <iostream>
#include "Aquarium.hpp"
#include "FishDatabase.hpp"
#include "FishUtility.hpp"

static float degToRad(float degrees) {
    return degrees * 3.14159265f / 180.f;
}

Fish::Fish(FishSpecies species, RangeX& initXBounds, RangeY& initYBounds): velocity(50.f, 50.f), directionCooldown(3.f), textures{}, xBounds(initXBounds){
    std::string speciesName = FishUtility::getSpeciesName(species);
    setTextures(speciesName);
    sf::Vector2f startPosition;

    sf::FloatRect bounds = sprite->getGlobalBounds();
    sprite->setOrigin(sf::Vector2f(bounds.size.x / 2.f, bounds.size.y / 2.f));

    size = FishUtility::getRandomSize(species);

    float scale = size / bounds.size.x;
    sprite->setScale({scale, scale});

    // randomize initial direction a bit
    velocity.x *= (static_cast<unsigned int>(FishUtility::getRandomScore({1, 10})) % 2 == 0) ? 1.f : -1.f;
    //velocity.y = 0;
    velocity.y *= (rand() % 2 == 0) ? 1.f : -1.f;

    yBounds = FishUtility::getDwellingPositions(initYBounds, FishUtility::getDwellingCategory(species));
    startPosition.y = yBounds.top + 
                  static_cast<float>(rand() % (yBounds.bottom - yBounds.top + 1));
    startPosition.x = xBounds.left + static_cast<float>(rand() % (xBounds.right - xBounds.left + 1));
    sprite->setPosition(startPosition);

}

// Update fish state (movement)
void Fish::update(float deltaTime){
    // Move the fish
    sprite->move(velocity * deltaTime);
    maybeChangeDirection(deltaTime);
    updateSpriteByTime(deltaTime);

    // Determine tilt angle based on y-velocity
    float tiltAngle = std::atan2(velocity.y, velocity.x); // radians
    sprite->setRotation(sf::radians(tiltAngle));

    sf::Vector2f scale = sprite->getScale();
    scale.x = std::abs(scale.x);  // keep horizontal scale normal

    if (velocity.x < 0.f)
        scale.y = -std::abs(scale.y); // flip vertically to face left
    else
        scale.y = std::abs(scale.y);  // normal
    sprite->setScale(scale);

    // Handle bouncing off window edges
    handleBounds();
}

// Draw fish to the window
void Fish::draw(sf::RenderWindow& window){
    window.draw(*sprite);
}

void Fish::updateSpriteByTime(float deltaTime){
    animationTimer += deltaTime;             // increment timer
    if (animationTimer >= animationInterval) {
        animationTimer -= animationInterval; // reset timer
        currentTextureIndex = (currentTextureIndex + 1) % NUM_TEXTURES; // next texture
        sprite->setTexture(textures[currentTextureIndex]); // update sprite
    }
}

// Bounce the fish if it hits window boundaries
void Fish::handleBounds() {
    sf::Vector2f pos = sprite->getPosition();
    sf::FloatRect bounds = sprite->getGlobalBounds();
    
    float halfWidth = bounds.size.x / 2.f;
    float halfHeight = bounds.size.y / 2.f;

    // Left
    if (pos.x - halfWidth < xBounds.left) {
        pos.x = halfWidth + xBounds.left;
        velocity.x = std::abs(velocity.x);
    }
    // Right
    else if (pos.x + halfWidth > xBounds.right) {
        pos.x = xBounds.right - halfWidth;
        velocity.x = -std::abs(velocity.x);
    }

    // Top
    if(velocity.y != 0){
        if (pos.y - halfHeight < yBounds.top) {
            pos.y = halfHeight + yBounds.top;
            velocity.y = std::abs(velocity.y);
        }
        // Bottom
        else if (pos.y + halfHeight > yBounds.bottom) {
            pos.y = yBounds.bottom - halfHeight;
            velocity.y = -std::abs(velocity.y);
        }
    }

    sprite->setPosition(pos);
}


void Fish::maybeChangeDirection(float deltaTime)
{
    directionCooldown -= deltaTime;
    if (directionCooldown > 0.f) return;

    // Reset cooldown (1–3 seconds)
    directionCooldown = 1.f + (rand() % 200) / 100.f;

    float changeProbability = 0.4f; // 40%

    float r = static_cast<float>(rand()) / RAND_MAX;
    if (r > changeProbability)
        return; 

    changeDirection();
}

void Fish::changeDirection() {
    float speed = std::hypot(velocity.x, velocity.y);

    int r = rand() % 100; // 0-99
    float angle;

    if (r < 80) {
        // 80% chance: strictly horizontal
        bool goingRight = rand() % 2; // randomly pick left or right
        angle = goingRight ? 0.f : M_PI; // 0 rad = right, π = left
    } else {
        // 20% chance: full random direction
        angle = degToRad(rand() % 360);
    }

    // Update velocity
    velocity.x = std::cos(angle) * speed;
    velocity.y = std::sin(angle) * speed;
}

void Fish::setTextures(std::string speciesName){
    for(size_t i = 0; i < NUM_TEXTURES; i++){
        if(!textures[i].loadFromFile("resources/fishes/" + speciesName + "/f" + std::to_string(i) + ".png")){
            std::cerr << "Unable to load fish texture \n";
            return;
        }
    }
    sprite = sf::Sprite(textures[0]);
}
