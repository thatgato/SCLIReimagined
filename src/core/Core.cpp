
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

        // Display top pages
        std::cout << "Displaying top-level pages:" << std::endl;
        setPageSelection(m_topLevelPages);
    }

    void Application::constructPages() {
        // Create and move every page and their commands here.
        auto TLP_GEOMETRY = std::make_unique<Page>("Geometry");
        TLP_GEOMETRY->AddChild<Commands::Geometry::Vector>("Vector");

        std::cout << Internal::Util::DescendantsToString(TLP_GEOMETRY.get());

        m_topLevelPages.push_back(std::move(TLP_GEOMETRY));
    }

    void Application::setPageSelection(const std::vector<std::unique_ptr<Page>> &pages) {
        int i = 1;
        for (auto &page: pages) {
            m_pagesInSelection[i] = page.get(); // update the current page selection map for selecting later
            std::cout << std::format("{}: {}", i, page->GetName()) << std::endl;
        }
    }

    std::string Application::listen() {
        std::cout << ">> ";
        std::string line;
        std::getline(std::cin, line);
        return line;
    }

    EParseResult Application::parse(std::string &input) {
        // First try to see if its an internal command
        // TODO
        // Then try to see if its a page selection command
        int res;
        if (Util::TryParseInt(input, res)) {
            if (m_pagesInSelection.contains(res)) { LOG("Valid page selection argument found; todo implement this"); }
        }
    }

    bool Application::validateParseResult(EParseResult result) {}
}
