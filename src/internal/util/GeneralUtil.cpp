
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
    // TODO: Figure out!!! im too tired:(
    std::string Util::DescendantsToString(const Core::Page* classToList, uint8_t depth) {
        std::cout << "assing " << classToList->GetName();


        std::ostringstream stringStream;
        for (int i = 0; i < depth; ++i)
            stringStream << "  ";
        stringStream << classToList->GetName();

        if (classToList->ContainsPages()) {
            for (const auto &page: classToList->GetPages()) {
                stringStream << DescendantsToString(page.get(), depth + 1) << std::endl;
            }
        } else if (classToList->ContainsCommands()) {
            for (auto &cmd: classToList->GetCommands()) {
                for (int i = 0; i < depth; ++i)
                    stringStream << "  ";
                stringStream << cmd->getName() << std::endl;
            }
        }
        stringStream << std::endl;
        return stringStream.str();
    }
}
