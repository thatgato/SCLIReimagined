

// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

#pragma once
#include <string>
#include <unordered_map>


// Made it top level so it's easily accessible from anywhere if this header is included
enum class EColor { WHITE, GREEN, YELLOW, ORANGE, RED, CYAN, BLUE, GRAY };

struct RGB {
    uint8_t r, g, b;
};

namespace Core {
    class Color {
        public:
            // is it better to define enums here, or in the namespace...?

            [[nodiscard]] static std::string Wrap(const std::string &original, EColor color,
                                                  bool background = false);

            [[nodiscard]] static std::string Wrap(const std::string &original, RGB color, bool background = false);

        private:
            static const std::unordered_map<EColor, RGB> colorMap;

            [[nodiscard]] static std::string getANSIColor(EColor color, bool forBackground = false);

            [[nodiscard]] static std::string getANSIColor(RGB color, bool forBackground = false);
    };

    #define CWRAP(string, color) Core::Color::Wrap(string, color)
}
