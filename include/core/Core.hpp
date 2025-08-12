
// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.


#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include <__fwd/queue.h>

#include "Page.hpp"

namespace Core {
    enum class EParseResult {
        PAGE_SELECT,
        COMMAND_SELECT,
        INTERNAL_COMMAND,
        ACTIVE_CMD_ARG,
        ESCAPE,
        BACK,
        INVALID,
        NO_OP
    };

    struct ApplicationFlags {
        bool isInCommandMode;
        BaseCommand* currentActiveCommand;
        const Page* currentPage;
    };

    struct ParseResult {
        EParseResult parseRes;
        const Page* pageToLoad = nullptr;
        // const std::vector<std::unique_ptr<Page>> &listOfPagesToLoad; -> might need later; not now tho; just assume to load top level if the pagetoload is nullptr on a back or pageselect parse result
        const Page* pageBackedFrom = nullptr;
        BaseCommand* commandToLoad = nullptr;
    };

    struct CoreLoopData {
        ParseResult prevParseResult;
    };


    class Application {
        public:
            Application() = delete;

            static void Startup(int argc, char* argv[]);

        private:
            static std::vector<std::unique_ptr<Page>> m_topLevelPages;
            static std::unordered_map<int, const Page*> m_pagesInSelection;
            static std::unordered_map<int, BaseCommand*> m_commandsInSelection;
            static std::queue<const Page*> m_pageQueue;
            static ApplicationFlags m_applicationFlags;

            static void coreLoop(CoreLoopData loopData, bool firstRun = false);

            static void constructPages();

            static void setupPageChildSelection(const Page* page);

            static void setupPageChildSelection(const std::vector<std::unique_ptr<Page>> &page);

            static std::string listen();

            static ParseResult parse(const std::string &input);

            static bool validateParseResult(EParseResult result);
    };
}
