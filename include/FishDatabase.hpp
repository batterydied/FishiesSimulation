#pragma once

#include <unordered_map>
#include "FishUtility.hpp"
#include <array>

inline std::unordered_map<std::string, FishSpeciesData> FishDatabase = {
    { "BlueTang", {
        "Blue Tang",
        FishSizeCategory::LG,
        FishSpeedCategory::FAST,
        FishActivityCategory::VERY_ACTIVE,
        FishDwellingCategory::TOP
    }},
    { "Clownfish", {
        "Clownfish",
        FishSizeCategory::SM,
        FishSpeedCategory::MEDIUM,
        FishActivityCategory::PASSIVE,
        FishDwellingCategory::BOTTOM
    }},
    { "PurpleTang", {
        "Purple Tang",
        FishSizeCategory::LG,
        FishSpeedCategory::FAST,
        FishActivityCategory::VERY_ACTIVE,
        FishDwellingCategory::TOP
    }},
    { "VanderbiltChromis", {
        "Vanderbilt Chromis",
        FishSizeCategory::XS,
        FishSpeedCategory::MEDIUM,
        FishActivityCategory::ACTIVE,
        FishDwellingCategory::TOP
    }},
    { "RoyalGramma", {
        "Royal Gramma",
        FishSizeCategory::SM,
        FishSpeedCategory::SLOW,
        FishActivityCategory::PASSIVE,
        FishDwellingCategory::BOTTOM
    }}
};