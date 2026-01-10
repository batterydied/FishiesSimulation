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
enum class FishDwellingCategory { TOP, MID, BOTTOM, GROUNDED, ALL };
enum class FishSpecies {
    CLOWNFISH, BLUE_TANG, PURPLE_TANG, ROYAL_GRAMMA, VANDERBILT_CHROMIS, TEST
};

struct Range {
    float minVal;
    float maxVal;
};

struct RangeX {
    unsigned int left;
    unsigned int right;
};

struct RangeY {
    unsigned int top;
    unsigned int bottom;
};

struct FishSpeciesData {
    std::string name;
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
    static RangeY getDwellingPositions(RangeY& defaultRange, FishDwellingCategory category);
    static float getRandomScore(Range r);

private:
    static Range getSizeRange(FishSizeCategory category);
    static Range getSpeedRange(FishSpeedCategory category);
    static Range getDwellingRange(FishDwellingCategory category);
    static Range getActivityRange(FishActivityCategory category);
    static std::string getSpeciesName(FishSpecies species);
};

