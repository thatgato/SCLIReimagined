
// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

//  Core.cpp

//  Created on: 2025 06 14
//  Created by: thatgato

//  Purpose: Handles the core logic of the application such as registering different kinds of pages, navigating and entering command contexts.

#include "core/Core.hpp"

#include <format>
#include <iostream>
#include <sstream>
#include <queue>

#include "commands/geometry/Vector.hpp"
#include "core/Logger.hpp"
#include "internal/util/GeneralUtil.hpp"

namespace Core {
    std::vector<std::unique_ptr<Page>> Application::m_topLevelPages;
    std::unordered_map<int, const Page*> Application::m_pagesInSelection;
    std::unordered_map<int, BaseCommand*> Application::m_commandsInSelection;
    ApplicationFlags Application::m_applicationFlags = {
        false,
        nullptr
    };

    std::queue<const Page*> Application::m_pageQueue;

    void Application::Startup(int argc, char* argv[]) {
        LOG("Beginning page construction");
        constructPages();

        LOG(std::format(
                "Hi, so apparently we have {} number of pages in the top level registry!",
                m_topLevelPages.size()));
        std::ostringstream oss;
        oss << "Pages in registry: ";
        for (const auto &page: m_topLevelPages) { oss << page->GetName() << "\t"; }
        LOG(oss.str());

        LOG("Entering core loop from startup");

        coreLoop({EParseResult::ESCAPE}, true);
    }

    // might create a struct for data from the previous loop; especially for transporting info about the back command etc
    void Application::coreLoop(CoreLoopData loopData, bool firstRun) {
        ParseResult parseResult = loopData.prevParseResult;
        if (firstRun) {
            // This runs the first time after startup; so we show the top level pages for selection
            std::cout << "Displaying top-level pages:" << std::endl;
            setupPageChildSelection(m_topLevelPages);
        }
        std::string listenRes = listen();
        parseResult           = parse(listenRes);

        if (listenRes.empty()) {
            // ignore empty str -> redo the loop
            coreLoop({parseResult});
            return;
        }

        // Listen; main loop here
        switch (parseResult.parseRes) {
            case EParseResult::PAGE_SELECT: // currentpage flag is modified when setupPageChildSelection is called
                setupPageChildSelection(parseResult.pageToLoad);
                m_pageQueue.push(parseResult.pageToLoad);
                coreLoop({parseResult});
                break;
            case EParseResult::COMMAND_SELECT:
                m_applicationFlags.currentActiveCommand = parseResult.commandToLoad;
                m_applicationFlags.isInCommandMode = true;
                // clear the console
                std::system("cls");
                m_applicationFlags.currentActiveCommand->setup();
                coreLoop({parseResult});
                break;
            case EParseResult::ACTIVE_CMD_ARG:

                m_applicationFlags.currentActiveCommand->tick(listenRes);
                coreLoop({parseResult});
                break;
            case EParseResult::INTERNAL_COMMAND:
                break;
            case EParseResult::ESCAPE:

                if (!m_applicationFlags.isInCommandMode) {
                    LOGI("Exiting application");
                    std::exit(0);
                }

                LOGI("Escaped. Calling exit on current command!");

                m_applicationFlags.isInCommandMode = false;
                m_applicationFlags.currentActiveCommand->exit();
                m_applicationFlags.currentActiveCommand = nullptr;

                setupPageChildSelection(m_applicationFlags.currentPage);
                coreLoop({parseResult});
                break;
            case EParseResult::INVALID:
                LOGW("Invalid parsing.");
                coreLoop({parseResult});
                break;
            case EParseResult::BACK:
                LOG("Backed from page: " + parseResult.pageBackedFrom->GetName() + "; Continuing operation as normal");
                if (parseResult.pageToLoad == nullptr) { setupPageChildSelection(m_topLevelPages); } else {
                    LOG("Loading " + parseResult.pageToLoad->GetName());
                    setupPageChildSelection(parseResult.pageToLoad);
                }

                coreLoop({parseResult});
                break;
            case EParseResult::NO_OP:
                LOGI("No operation.");
                coreLoop({parseResult});
                break;
        }
    }

    void Application::constructPages() {
        // Create and move every page and their commands here.
        auto TLP_GEOMETRY = std::make_unique<Page>("Geometry");
        TLP_GEOMETRY->AddChild<Commands::Geometry::Vector>("Vector");

        std::cout << Internal::Util::DescendantsToString(TLP_GEOMETRY.get());

        m_topLevelPages.push_back(std::move(TLP_GEOMETRY));
    }

    void Application::setupPageChildSelection(const Page* page) {
        m_commandsInSelection.clear();
        m_pagesInSelection.clear();
        m_applicationFlags.currentPage = page;

        int i = 1;
        if (page->ContainsPages()) {
            std::cout << "Available Pages:" << std::endl;

            for (auto &childPage: page->GetPages()) {
                m_pagesInSelection[i] = childPage.get(); // update the current page selection map for selecting later
                std::cout << std::format("{}: {}", i, childPage->GetName()) << std::endl;
                i++;
            }
        }

        if (page->ContainsCommands()) {
            std::cout << "Available Commands:" << std::endl;

            for (auto &childCommand: page->GetCommands()) {
                m_commandsInSelection[i] = childCommand.get();
                // update the current page selection map for selecting later
                std::cout << std::format("{}: {}", i, childCommand->GetName()) << std::endl;
                i++;
            }
        }
    }

    void Application::setupPageChildSelection(const std::vector<std::unique_ptr<Page>> &page) {
        m_applicationFlags.currentPage = nullptr;
        int i                          = 1;
        for (auto &childPage: page) {
            m_pagesInSelection[i] = childPage.get(); // update the current page selection map for selecting later

            std::cout << std::format("{}: {}", i, childPage->GetName()) << std::endl;
            i++;
        }
    }

    std::string Application::listen() {
        std::cout << ">> ";
        std::string line;
        std::getline(std::cin, line);
        return line;
    }

    ParseResult Application::parse(const std::string &input) {
        std::string inputLower = input;
        Util::StrLower(inputLower); // turns inputLower into all lowercase
        // First try to see if its an internal command
        // TODO
        // Then try to see if its a page selection command

        if (inputLower == "e" || inputLower == "exit") { return {.parseRes = EParseResult::ESCAPE}; }
        // on escape we should exit() on currentcmd and load the previous (pagequeue.front)
        if ((inputLower == "b" || inputLower == "back") && !m_applicationFlags.isInCommandMode) {
            if (m_pageQueue.empty()) {
                LOGW("Tried to back from the top-level");
                return {.parseRes = EParseResult::NO_OP};
            }

            const Page* pageWeAreBackingFrom = m_applicationFlags.currentPage;

            m_pageQueue.pop();
            LOG("Page queue popped");

            if (m_pageQueue.empty()) {
                return {.parseRes = EParseResult::BACK, .pageBackedFrom = pageWeAreBackingFrom};
                // pagetoload = nullptr --> load toplevel
            }
            return {
                .parseRes = EParseResult::BACK, .pageToLoad = m_pageQueue.front(),
                .pageBackedFrom = pageWeAreBackingFrom
            };
        }
        if (m_applicationFlags.isInCommandMode) { return {.parseRes = EParseResult::ACTIVE_CMD_ARG}; }


        int res;
        if (Util::TryParseInt(input, res)) {
            if (m_pagesInSelection.contains(res)) {
                const Page* selectedPage = m_pagesInSelection[res];

                LOG("Valid page selection argument found");

                if (selectedPage->ContainsPages() || selectedPage->ContainsCommands()) {
                    return {.parseRes = EParseResult::PAGE_SELECT, .pageToLoad = selectedPage};
                }

                throw std::runtime_error("Invalid page selection; The page has no children.");
            }
            if (m_commandsInSelection.contains(res)) {
                LOG("Valid command selection argument found");
                return {.parseRes = EParseResult::COMMAND_SELECT, .commandToLoad = m_commandsInSelection[res]};
            }
            return {.parseRes = EParseResult::INVALID};
        } else { return {.parseRes = EParseResult::INVALID}; }
    }

    bool Application::validateParseResult(EParseResult result) { return false; }
}
