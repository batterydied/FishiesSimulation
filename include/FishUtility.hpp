#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <vector>
#include <unordered_map>
#include "FishDatabase.hpp"

constexpr int NUM_SPRITES = 4;


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

class FishUtility{
public:
    FishUtility();
    void printAllSpecies();
    void printRandomScore();
    static RangeY getDwellingPositions(RangeY& defaultRange, FishDwellingCategory category);
    static float getRandomScore(Range r);
    static std::string getSpeciesName(FishSpecies species);
    static unsigned int getRandomSize(FishSpecies species);

private:
    static Range getSizeRange(FishSizeCategory category);
    static Range getSpeedRange(FishSpeedCategory category);
    static Range getDwellingRange(FishDwellingCategory category);
    static Range getActivityRange(FishActivityCategory category);
     static FishSizeCategory getSizeCategory(FishSpecies species);
};

