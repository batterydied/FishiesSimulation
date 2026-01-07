#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <vector>
#include <unordered_map>

constexpr int NUM_SPRITES = 4;

enum class FishSizeCategory { XXS, XS, SM, MD, LG, XL, XXL };
enum class FishSpeedCategory { VERY_SLOW, SLOW, MEDIUM, FAST, VERY_FAST };
enum class FishActivityCategory { VERY_PASSIVE, PASSIVE, MODERATE, ACTIVE, VERY_ACTIVE };
enum class FishDwellingCategory { TOP, MID_TOP, MID, MID_BOTTOM, BOTTOM, ALL };

struct range {
    float minVal;
    float maxVal;
};

struct FishSpeciesData {
    std::string name;
    std::array<sf::Texture, NUM_SPRITES> textures;
    FishSizeCategory sizeCategory;
    FishSpeedCategory speedCategory;
    FishActivityCategory activityCategory;
    FishDwellingCategory dwellingCategory;
};

class FishUtility{
public:
    FishUtility();

    void printAllSpecies();
    void printRandomScore();

private:
    void loadFishTextures(FishSpeciesData& species);
    void initializeFishDatabase();
    range getSizeRange(FishSizeCategory category);
    range getSpeedRange(FishSpeedCategory category);
    range getDwellingRange(FishDwellingCategory category);
    range getActivityRange(FishActivityCategory category);
    float getRandomScore(range& r);
};

