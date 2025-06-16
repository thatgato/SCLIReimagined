
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
    std::string Color::Wrap(std::string &original, EColor color, bool background) noexcept {
        static const std::unordered_map<Color::EColor, RGB> colorMap = {
            {Color::EColor::RED, {255, 0, 0}}
            // TODO FINISH
        };
        return "";
    }
}
