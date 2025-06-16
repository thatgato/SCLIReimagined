

// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

#pragma once
#include <string>


namespace Core {
    class Color {
        public:
            enum class EColor { WHITE, GREEN, YELLOW, ORANGE, RED, CYAN, BLUE };

            // is it better to define enums here, or in the namespace...?
            struct RGB {
                int r, g, b;
            };

            [[nodiscard]] std::string Wrap(std::string &original, EColor color, bool background = false) noexcept;

            [[nodiscard]] std::string Wrap(std::string &original, RGB color, bool background = false) noexcept;

        private:
            [[nodiscard]] std::string getANSIColor(EColor color, bool forBackground = false) noexcept;
    };
}
