#pragma once
#include <unordered_map>
#include <string>

enum class FishSizeCategory { XXS, XS, SM, MD, LG, XL, XXL };
enum class FishSpeedCategory { VERY_SLOW, SLOW, MEDIUM, FAST, VERY_FAST };
enum class FishActivityCategory { VERY_PASSIVE, PASSIVE, MODERATE, ACTIVE, VERY_ACTIVE };
enum class FishDwellingCategory { TOP, MID, BOTTOM, GROUNDED, ALL };
enum class FishSpecies {
    CLOWNFISH, BLUE_TANG, PURPLE_TANG, ROYAL_GRAMMA, VANDERBILT_CHROMIS, TEST
};

struct FishSpeciesData {
    std::string name;
    FishSizeCategory size;
    FishSpeedCategory speed;
    FishActivityCategory activity;
    FishDwellingCategory dwelling;
};

// 🔑 Allow unordered_map to hash our enum class key
namespace std {
    template <>
    struct hash<FishSpecies> {
        size_t operator()(const FishSpecies &fs) const noexcept {
            return hash<int>()(static_cast<int>(fs));
        }
    };
}

inline std::unordered_map<FishSpecies, FishSpeciesData> FishDatabase = {
    { FishSpecies::BLUE_TANG, {
        "Blue Tang",
        FishSizeCategory::LG,
        FishSpeedCategory::FAST,
        FishActivityCategory::VERY_ACTIVE,
        FishDwellingCategory::TOP
    }},
    { FishSpecies::CLOWNFISH, {
        "Clownfish",
        FishSizeCategory::SM,
        FishSpeedCategory::MEDIUM,
        FishActivityCategory::PASSIVE,
        FishDwellingCategory::BOTTOM
    }},
    { FishSpecies::PURPLE_TANG, {
        "Purple Tang",
        FishSizeCategory::LG,
        FishSpeedCategory::FAST,
        FishActivityCategory::VERY_ACTIVE,
        FishDwellingCategory::TOP
    }},
    { FishSpecies::VANDERBILT_CHROMIS, {
        "Vanderbilt Chromis",
        FishSizeCategory::XS,
        FishSpeedCategory::MEDIUM,
        FishActivityCategory::ACTIVE,
        FishDwellingCategory::TOP
    }},
    { FishSpecies::ROYAL_GRAMMA, {
        "Royal Gramma",
        FishSizeCategory::SM,
        FishSpeedCategory::SLOW,
        FishActivityCategory::PASSIVE,
        FishDwellingCategory::BOTTOM
    }}
};
