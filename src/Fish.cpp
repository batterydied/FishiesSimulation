#include "Fish.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <array>
#include <iostream>

static float degToRad(float degrees) {
    return degrees * 3.14159265f / 180.f;
}

Fish::Fish(sf::Vector2f startPosition): velocity(50.f, 50.f), directionCooldown(3.f), textures(NUM_TEXTURES){
    setTextures("Clownfish");
    sprite->setPosition(startPosition);
    // sf::FloatRect bounds = sprite.getGlobalBounds();
    // sprite.setOrigin(sf::Vector2f(bounds.size.x / 2.f, bounds.size.y / 2.f));

    // float scale = 200 / bounds.size.x;
    // sprite.setScale({scale, scale});

    // // randomize initial direction a bit
    // velocity.x *= (rand() % 2 == 0) ? 1.f : -1.f;
    // velocity.y *= (rand() % 2 == 0) ? 1.f : -1.f;
}

// Update fish state (movement)
void Fish::update(float deltaTime){
    // // Move the fish
    // sprite.move(velocity * deltaTime);
    // maybeChangeDirection(deltaTime);
    // updateSpriteByTime(deltaTime);

    // // Determine tilt angle based on y-velocity
    // float tiltAngle = std::atan2(velocity.y, velocity.x); // radians
    // sprite.setRotation(sf::radians(tiltAngle));

    // sf::Vector2f scale = sprite.getScale();
    // scale.x = std::abs(scale.x);  // keep horizontal scale normal

    // if (velocity.x < 0.f)
    //     scale.y = -std::abs(scale.y); // flip vertically to face left
    // else
    //     scale.y = std::abs(scale.y);  // normal
    // sprite.setScale(scale);

    // // Handle bouncing off window edges
    // handleBounds();
    updateSpriteByTime(deltaTime);
}

// Draw fish to the window
void Fish::draw(sf::RenderWindow& window) const{
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
void Fish::handleBounds(){
    sf::Vector2f pos = sprite->getPosition();
    sf::FloatRect bounds = sprite->getGlobalBounds();
    sf::Vector2u windowSize(1400, 750);

    float radius = std::max(bounds.size.x, bounds.size.y) / 2.f;

    // Left
    if (pos.x - radius < 0.f) {
        pos.x = radius;
        velocity.x = std::abs(velocity.x);
    }
    // Right
    else if (pos.x + radius > windowSize.x) {
        pos.x = windowSize.x - radius;
        velocity.x = -std::abs(velocity.x);
    }

    // Top
    if (pos.y - radius < 0.f) {
        pos.y = radius;
        velocity.y = std::abs(velocity.y);
    }
    // Bottom
    else if (pos.y + radius > windowSize.y) {
        pos.y = windowSize.y - radius;
        velocity.y = -std::abs(velocity.y);
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

    float angleChange = degToRad((rand() % 90) - 45);

    float angle = std::atan2(velocity.y, velocity.x);
    float speed = std::hypot(velocity.x, velocity.y);

    angle += angleChange;

    velocity.x = std::cos(angle) * speed;
    velocity.y = std::sin(angle) * speed;
};

std::string Fish::getFishSpeciesName(FishSpecies species){
    switch(species){
        case FishSpecies::CLOWNFISH: return "Clownfish";
        case FishSpecies::BLUE_TANG: return "BlueTang";
        case FishSpecies::PURPLE_TANG: return "PurpleTang";
        case FishSpecies::ROYAL_GRAMMA: return "RoyalGramma";
        case FishSpecies::VANDERBILT_CHROMIS: return "VanderbiltChromis";
    }
    return "Clownfish";
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

