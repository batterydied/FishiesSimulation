#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <random>
#include "FishDatabase.hpp"

FishUtility::FishUtility() {
    initializeFishDatabase();
}

range FishUtility::getSizeRange(FishSizeCategory category) {
    switch(category){
        case FishSizeCategory::XXS: return {1, 1.15};
        case FishSizeCategory::XS: return {1.25, 1.5};
        case FishSizeCategory::SM: return {1.5, 2};
        case FishSizeCategory::MD: return {2, 2.5};
        case FishSizeCategory::LG: return {3, 4};
        case FishSizeCategory::XL: return {5, 6};
        case FishSizeCategory::XXL: return {6, 8};
    }
    return {1, 1};
};

range FishUtility::getActivityRange(FishActivityCategory category) {
    //chances of moving
    switch(category){
        case FishActivityCategory::VERY_PASSIVE: return {.15, .20};
        case FishActivityCategory::PASSIVE: return {.2, .3};
        case FishActivityCategory::MODERATE: return {.5, .6};
        case FishActivityCategory::ACTIVE: return {.75, .8};
        case FishActivityCategory::VERY_ACTIVE: return {.8, .99};
    }
    return {.5, .6};
};

range FishUtility::getSpeedRange(FishSpeedCategory category) {
    switch(category){
        case FishSpeedCategory::VERY_SLOW: return {1, 1.05};
        case FishSpeedCategory::SLOW: return {1.2, 1.3};
        case FishSpeedCategory::MEDIUM: return {1.5, 1.65};
        case FishSpeedCategory::FAST: return {2, 2.25};
        case FishSpeedCategory::VERY_FAST: return {3, 3.5};
    }
    return {1.5, 1.65};
};

range FishUtility::getDwellingRange(FishDwellingCategory category) {
    //where the fish will stay with respect to height of the tank
    switch(category){
        case FishDwellingCategory::TOP: return {.7, .9};
        case FishDwellingCategory::MID_TOP: return {.5, .9};
        case FishDwellingCategory::MID: return {.4, .6};
        case FishDwellingCategory::MID_BOTTOM: return {.1, .55};
        case FishDwellingCategory::BOTTOM: return {.1, .2};
        case FishDwellingCategory::ALL: return {.1, .9};
    }
    return {.4, .6};
};

float FishUtility::getRandomScore(range& r) {
    static std::mt19937 rng{ std::random_device{}() };
    std::uniform_real_distribution<float> dist(r.minVal, r.maxVal);
    float value = dist(rng);
    float roundedTo4 = std::round(value * 10000.f) / 10000.f;
    return roundedTo4;
};

void FishUtility::loadFishTextures(FishSpeciesData& species) {
    for (size_t i = 0; i < NUM_SPRITES; i++) {
        std::string path = "resources/fishes/" + species.name + "/f" + std::to_string(i) + ".png";
        if (!species.textures[i].loadFromFile(path)) {
            std::cerr << "Failed to load texture: " << path << "\n";
        }
    }
};

void FishUtility::initializeFishDatabase(){
    size_t numSpecies = std::size(FishDatabase);
    for(size_t i = 0; i < numSpecies; i++){
        FishSpeciesData& species = FishDatabase[i];
        loadFishTextures(species);
    }
};

void FishUtility::printAllSpecies(){
    size_t numSpecies = std::size(FishDatabase);
    for(size_t i = 0; i < numSpecies; i++){
        std::cout << FishDatabase[i].name << "\n";
    }
}

void FishUtility::printRandomScore(){
    range r = getSizeRange(FishSizeCategory::LG);
    std::cout << getRandomScore(r) << "\n";
}

