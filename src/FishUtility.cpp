#include "FishDatabase.hpp"
#include <iostream>
#include <random>
#include <cmath>
#include "FishUtility.hpp"

Range FishUtility::getSizeRange(FishSizeCategory category){
    switch(category){
        case FishSizeCategory::XXS: return {0.4f, 0.5f};    // 20–25
        case FishSizeCategory::XS:  return {0.5f, 0.6f};    // 25–30
        case FishSizeCategory::SM:  return {0.6f, 0.7f};    // 30–35
        case FishSizeCategory::MD:  return {1.1f, 1.25f};   // 55–63
        case FishSizeCategory::LG:  return {1.6f, 1.9f};    // 80–95
        case FishSizeCategory::XL:  return {2.6f, 3.1f};    // 130–155
        case FishSizeCategory::XXL: return {3.8f, 4.5f};    // 190–225
    }
    return {1, 1};
}

Range FishUtility::getActivityRange(FishActivityCategory category){
    switch(category){
        case FishActivityCategory::VERY_PASSIVE: return {.15, .20};
        case FishActivityCategory::PASSIVE: return {.2, .3};
        case FishActivityCategory::MODERATE: return {.5, .6};
        case FishActivityCategory::ACTIVE: return {.75, .8};
        case FishActivityCategory::VERY_ACTIVE: return {.8, .99};
    }
    return {.5, .6};
}

Range FishUtility::getSpeedRange(FishSpeedCategory category){
    switch(category){
        case FishSpeedCategory::VERY_SLOW: return {1, 1.05};
        case FishSpeedCategory::SLOW: return {1.2, 1.3};
        case FishSpeedCategory::MEDIUM: return {1.5, 1.65};
        case FishSpeedCategory::FAST: return {2, 2.25};
        case FishSpeedCategory::VERY_FAST: return {3, 3.5};
    }
    return {1.5, 1.65};
}

Range FishUtility::getDwellingRange(FishDwellingCategory category){
    switch(category){
        case FishDwellingCategory::TOP: return {.5, .1};
        case FishDwellingCategory::MID: return {.65, .25};
        case FishDwellingCategory::BOTTOM: return {.9, .5};
        case FishDwellingCategory::GROUNDED: return {.9, .9};
        case FishDwellingCategory::ALL: return {.9, .1};
    }
    return {1, .1};
}

float FishUtility::getRandomScore(Range r){
    static std::mt19937 rng{ std::random_device{}() };
    std::uniform_real_distribution<float> dist(r.minVal, r.maxVal);
    float value = dist(rng);
    return std::round(value * 10000.f) / 10000.f; // round to 4 decimals
}

RangeY FishUtility::getDwellingPositions(RangeY& defaultRange, FishDwellingCategory category){
    unsigned int top = defaultRange.top;
    unsigned int bottom = defaultRange.bottom;
    unsigned int diff = bottom - top;

    Range scale = getDwellingRange(category);

    unsigned int newTop = static_cast<unsigned int>(diff * scale.maxVal) + top;
    unsigned int newBottom = static_cast<unsigned int>(diff * scale.minVal) + top;

    return {newTop, newBottom};
}

// --- Print functions ---
void FishUtility::printAllSpecies(){
    for (const auto& [name, species] : FishDatabase) {
        std::cout << species.name << "\n";
    }
}

void FishUtility::printRandomScore(){
    Range r = getSizeRange(FishSizeCategory::LG);
    std::cout << getRandomScore(r) << "\n";
}

std::string FishUtility::getSpeciesName(FishSpecies species){
    FishSpeciesData speciesData = FishDatabase[species];
    return speciesData.name;
}

FishSizeCategory FishUtility::getSizeCategory(FishSpecies species){
    FishSpeciesData speciesData = FishDatabase[species];
    return speciesData.size;
}

unsigned int FishUtility::getRandomSize(FishSpecies species){
    return static_cast<int>(
        std::round(FishUtility::getRandomScore(FishUtility::getSizeRange(FishUtility::getSizeCategory(species)))) * 50
    );
}

FishDwellingCategory FishUtility::getDwellingCategory(FishSpecies species){
    FishSpeciesData speciesData = FishDatabase[species];
    return speciesData.dwelling;
}