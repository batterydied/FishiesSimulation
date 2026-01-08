#pragma once
#include <memory>
#include <string>

enum class Background {B0, B1, B2, B3, B4};

class Aquarium {
    public:
        Aquarium(unsigned int width, unsigned int height);
        void update(float dt);  
        void addFish();
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

        std::string getBackgroundName(Background bg);
        sf::Texture backgroundTexture;
        std::optional<sf::Sprite> backgroundSprite;
};