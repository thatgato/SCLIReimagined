
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

#include "commands/geometry/Vector.hpp"
#include "core/Logger.hpp"
#include "internal/util/GeneralUtil.hpp"

namespace Core {
    std::vector<std::unique_ptr<Page>> Application::m_topLevelPages;
    std::unordered_map<int, Page*> Application::m_pagesInSelection;
    std::unordered_map<int, BaseCommand*> Application::m_commandsInSelection;
    ApplicationFlags Application::m_applicationFlags = {
        false,
        nullptr
    };

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
        EParseResult parseRes = loopData.prevParseResult;
        if (firstRun) {
            // This runs the first time after startup; so we show the top level pages for selection
            std::cout << "Displaying top-level pages:" << std::endl;
            setupPageChildSelection(m_topLevelPages);
        }
        std::string listenRes = listen();
        parseRes              = parse(listenRes);
        // Listen; main loop here
        switch (parseRes) {
            case EParseResult::PAGE_SELECT:
                coreLoop({parseRes});
                break;
            case EParseResult::COMMAND_SELECT:
                m_applicationFlags.isInCommandMode = true;
                m_applicationFlags.currentActiveCommand->setup();
                coreLoop({parseRes});
                break;
            case EParseResult::ACTIVE_CMD_ARG:
                m_applicationFlags.currentActiveCommand->tick(listenRes);
                coreLoop({parseRes});
                break;
            case EParseResult::INTERNAL_COMMAND:
                break;
            case EParseResult::ESCAPE:
                LOGW("Escaped.");
                break;
            case EParseResult::INVALID:
                LOGW("Invalid parsing.");
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
        int i = 1;
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

    EParseResult Application::parse(const std::string &input) {
        std::string inputLower = input;
        Util::StrLower(inputLower); // turns inputLower into all lowercase
        // First try to see if its an internal command
        // TODO
        // Then try to see if its a page selection command

        if (inputLower == "e" || inputLower == "exit") { return EParseResult::ESCAPE; }
        if (m_applicationFlags.isInCommandMode) { return EParseResult::ACTIVE_CMD_ARG; }


        int res;
        if (Util::TryParseInt(input, res)) {
            if (m_pagesInSelection.contains(res)) {
                Page* selectedPage = m_pagesInSelection[res];
                LOG("Valid page selection argument found; todo implement this");
                if (selectedPage->ContainsPages() || selectedPage->ContainsCommands()) {
                    setupPageChildSelection(selectedPage);
                    return EParseResult::PAGE_SELECT;
                }
                throw std::runtime_error("Invalid page selection; The page has no children.");
            }
            if (m_commandsInSelection.contains(res)) {
                LOG("Valid command selection argument found; todo implement this");
                m_applicationFlags.currentActiveCommand = m_commandsInSelection[res];
                return EParseResult::COMMAND_SELECT;
            }
            return EParseResult::INVALID;
        } else { return EParseResult::INVALID; }
    }

    bool Application::validateParseResult(EParseResult result) {}
}
