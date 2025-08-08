
// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

//  GeneralUtil.cpp

//  Created on: 2025 08 01
//  Created by:

//  Purpose:

#include "util/GeneralUtil.hpp"

#include <iostream>
#include <charconv>

namespace Internal {
    std::string Util::DescendantsToString(const Core::Page* classToList, uint16_t indent) {
        std::ostringstream stringStream;

        if (!classToList) return "";

        // Print current page
        stringStream << generateIndent(indent) << "Page: " << classToList->GetName() << "\n";

        // Print commands in this page
        if (classToList->ContainsCommands()) {
            stringStream << generateIndent(indent + 1) << "Commands:\n";
            for (const auto &cmd: classToList->GetCommands()) {
                stringStream << generateIndent(indent + 2) << "- " << cmd->GetName() << "\n";
            }
        }

        // Recurse into child pages
        if (classToList->ContainsPages()) {
            stringStream << generateIndent(indent + 1) << "Child Pages:\n";
            for (const auto &page: classToList->GetPages()) {
                stringStream << DescendantsToString(page.get(), indent + 2); // recursive call
            }
        }

        return stringStream.str();
    }

    bool Util::TryParseInt(const std::string &str, int &outValue) {
        auto result = std::from_chars(str.data(), str.data() + str.size(), outValue);
        return result.ec == std::errc() && result.ptr == str.data() + str.size();
    }

    void Util::StrLower(std::string &outStr) {
        std::transform(outStr.begin(), outStr.end(), outStr.begin(),
                       [](unsigned char c) { return std::tolower(c); });
    }

    std::string Util::generateIndent(uint16_t depth) {
        std::ostringstream stringStream;
        for (int i = 0; i < depth; ++i)
            stringStream << "  ";
        return stringStream.str();
    }
}
