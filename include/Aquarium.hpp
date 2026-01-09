#pragma once
#include <memory>
#include <string>
#include "Fish.hpp"
#include <vector>
#include "FishUtility.hpp"

enum class Background {B0, B1, B2};

class Aquarium {
    public:
        Aquarium(unsigned int width, unsigned int height);
        void update(float dt);  
        void addFish(FishSpecies species);
        void removeFish();
        void draw(sf::RenderWindow& window);
        void setBackground(Background bg);

        unsigned int getWidth();
        unsigned int getHeight();

    private: 
        unsigned int WIDTH;
        unsigned int HEIGHT;
        unsigned int DEFAULT_SPEED;
        unsigned int DEFAULT_SIZE;

        unsigned int xPadding = 50;
        unsigned int yPadding = 85;

        RangeX xBounds;
        RangeY yBounds;

        std::string getBackgroundName(Background bg);
        void scaleBackground();

        sf::Texture backgroundTexture;
        std::optional<sf::Sprite> backgroundSprite;
        std::vector<Fish> fishes;
};