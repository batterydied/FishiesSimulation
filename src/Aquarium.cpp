#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include "Aquarium.hpp"
#include <memory>
#include <string>

Aquarium::Aquarium(unsigned int width, unsigned int height): WIDTH(width), HEIGHT(height), DEFAULT_SPEED(100), DEFAULT_SIZE(100){
    xBounds = {xPadding, width - xPadding};
    yBounds = {yPadding, height - yPadding}; 
    setBackground(Background::B0);
    addFish(FishSpecies::BLUE_TANG);
    addFish(FishSpecies::CLOWNFISH);
    addFish(FishSpecies::PURPLE_TANG);
    addFish(FishSpecies::VANDERBILT_CHROMIS);
    addFish(FishSpecies::ROYAL_GRAMMA);
};

void Aquarium::addFish(FishSpecies species){
    fishes.push_back(Fish(species, xBounds, yBounds));
};

void Aquarium::draw(sf::RenderWindow& window) {
    if(backgroundSprite){
        scaleBackground();
        window.draw(*backgroundSprite);
    }else{ //Draw a black rectangle as fallback
        sf::RectangleShape blackBackground(sf::Vector2f(static_cast<float>(WIDTH), static_cast<float>(HEIGHT)));
        blackBackground.setFillColor(sf::Color::Black);
        window.draw(blackBackground);
    }

    for(auto fish : fishes){
        fish.draw(window);
    }
};

void Aquarium::setBackground(Background bg){
    backgroundTexture = sf::Texture();

    if(!backgroundTexture.loadFromFile("resources/backgrounds/" + getBackgroundName(bg) + ".png")){
        std::cerr << "Unable to load background \n";
    }else{
        backgroundSprite = sf::Sprite(backgroundTexture);
    }
};

std::string Aquarium::getBackgroundName(Background bg){
    switch(bg){
        case Background::B0: return "b0";
        case Background::B1: return "b1";
        case Background::B2: return "b2";
    }
    return "b0";
};

void Aquarium::update(float dt) {
    for(auto& fish : fishes){
        fish.update(dt);
    }
};

void Aquarium::scaleBackground(){
    sf::Vector2u textureSize = backgroundTexture.getSize();
    float scaleX = static_cast<float>(WIDTH) / textureSize.x;
    float scaleY = static_cast<float>(HEIGHT) / textureSize.y;
    backgroundSprite->setScale({scaleX, scaleY});
};

