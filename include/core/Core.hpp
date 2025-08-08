
// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.


#pragma once
#include <memory>
#include <unordered_map>
#include <vector>

#include "Page.hpp"

namespace Core {
    enum class EParseResult {
        PAGE_SELECT,
        COMMAND_SELECT,
        INTERNAL_COMMAND,
        OTHER_OR_INVALID
    };


    class Application {
        public:
            Application() = delete;

            static void Startup(int argc, char* argv[]);

        private:
            static std::vector<std::unique_ptr<Page>> m_topLevelPages;
            static std::unordered_map<int, Page*> m_pagesInSelection;
            static std::unordered_map<int, BaseCommand*> m_commandsInSelection;

            static void coreLoop();

            static void constructPages();

            static void setupPageChildSelection(const Page* page);

            static void setupPageChildSelection(const std::vector<std::unique_ptr<Page>> &page);

            static std::string listen();

            static EParseResult parse(std::string &input);

            static bool validateParseResult(EParseResult result);
    };
}
