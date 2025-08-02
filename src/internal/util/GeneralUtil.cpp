
// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

//  GeneralUtil.cpp

//  Created on: 2025 08 01
//  Created by:

//  Purpose:

#include "util/GeneralUtil.hpp"

#include <iostream>

namespace Internal {
    std::string Util::DescendantsToString(const Core::Page* classToList, uint16_t indent) {
        std::ostringstream stringStream;

        if (!classToList) return "";

        // Print current page
        stringStream << generateIdent(indent) << "Page: " << classToList->GetName() << "\n";

        // Print commands in this page
        if (classToList->ContainsCommands()) {
            stringStream << generateIdent(indent + 1) << "Commands:\n";
            for (const auto &cmd: classToList->GetCommands()) {
                stringStream << generateIdent(indent + 2) << "- " << cmd->getName() << "\n";
            }
        }

        // Recurse into child pages
        if (classToList->ContainsPages()) {
            stringStream << generateIdent(indent + 1) << "Child Pages:\n";
            for (const auto &page: classToList->GetPages()) {
                stringStream << DescendantsToString(page.get(), indent + 2); // recursive call
            }
        }

        return stringStream.str();
    }

    std::string Util::generateIdent(uint16_t depth) {
        std::ostringstream stringStream;
        for (int i = 0; i < depth; ++i)
            stringStream << "  ";
        return stringStream.str();
    }
}
