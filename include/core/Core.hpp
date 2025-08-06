
// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.


#pragma once
#include <memory>
#include <unordered_map>
#include <vector>

#include "Page.hpp"

namespace Core {
    class Application {
        public:
            Application() = delete;

            static void Startup(int argc, char* argv[]);

        private:
            static std::vector<std::unique_ptr<Page>> m_topLevelPages;
            static std::unordered_map<int, Page *> m_pagesInSelection;

            static void constructPages();

            static void setPageSelection(const std::vector<std::unique_ptr<Page>> &pages);
    };
}
