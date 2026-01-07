#pragma once 

#include <vector>
#include "FishUtility.hpp"

std::vector<FishSpeciesData> FishDatabase = {
    {
        "BlueTang",
        {},                         
        FishSizeCategory::LG,
        FishSpeedCategory::FAST,
        FishActivityCategory::VERY_ACTIVE,
        FishDwellingCategory::MID_TOP
    },
    {
        "Clownfish",
        {},
        FishSizeCategory::SM,
        FishSpeedCategory::MEDIUM,
        FishActivityCategory::PASSIVE,
        FishDwellingCategory::MID_BOTTOM
    },
    {
        "PurpleTang",
        {},
        FishSizeCategory::LG,
        FishSpeedCategory::FAST,
        FishActivityCategory::VERY_ACTIVE,
        FishDwellingCategory::MID_TOP
    },
    {
        "VanderbiltChromis",
        {},
        FishSizeCategory::XS,
        FishSpeedCategory::MEDIUM,
        FishActivityCategory::ACTIVE,
        FishDwellingCategory::MID_TOP
    },
    {
        "RoyalGramma",
        {},
        FishSizeCategory::SM,
        FishSpeedCategory::SLOW,
        FishActivityCategory::PASSIVE,
        FishDwellingCategory::MID_BOTTOM
    }
};
