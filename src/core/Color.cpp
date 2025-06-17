
// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

//  Color.cpp

//  Created on: 2025 06 16
//  Created by: thatgato

//  Purpose: RGB and Enum style color wrapping into ANSI colors, mainly for logging purposes

#include "core/Color.hpp"
#include <unordered_map>

namespace Core {
    const std::unordered_map<EColor, RGB> Color::colorMap = {
        {EColor::RED, {255, 0, 0}},
        {EColor::WHITE, {255, 255, 255}},
        {EColor::GREEN, {0, 255, 0}},
        {EColor::YELLOW, {255, 255, 0}},
        {EColor::ORANGE, {255, 105, 0}},
        {EColor::CYAN, {0, 255, 255}},
        {EColor::BLUE, {0, 0, 255}},
    };

    const std::string terminator = "\033[0m";

    std::string Color::Wrap(const std::string &original, EColor color, bool background) {
        return getANSIColor(color, background) + original + terminator;
    }

    std::string Color::Wrap(const std::string &original, RGB color, bool background) {
        return getANSIColor(color, background) + original + terminator;
    }

    std::string Color::getANSIColor(EColor color, bool forBackground) {
        std::string res = "\033[" + std::to_string(forBackground ? 48 : 38)
                          + ";2;"
                          + std::to_string(colorMap.at(color).r) + ";"
                          + std::to_string(colorMap.at(color).g) + ";"
                          + std::to_string(colorMap.at(color).b)
                          + "m";
        return res;
    }

    std::string Color::getANSIColor(RGB color, bool forBackground) {
        std::string res = "\033[" + std::to_string(forBackground ? 48 : 38)
                          + ";2;"
                          + std::to_string(color.r) + ";"
                          + std::to_string(color.g) + ";"
                          + std::to_string(color.b)
                          + "m";
        return res;
    }
}
