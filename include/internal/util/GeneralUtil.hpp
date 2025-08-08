

// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

#pragma once
#include <sstream>

#include "../../core/Page.hpp"

namespace Internal {
    class Util {
        public:
            static std::string DescendantsToString(const Core::Page* classToList, uint16_t indent = 0);

            static bool TryParseInt(const std::string &str, int &outValue);

            static void StrLower(std::string &outStr);

        private:
            static std::string generateIndent(uint16_t depth = 0);
    };
}

using Util = Internal::Util;
