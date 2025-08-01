
// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

//  BaseCommand.hpp

//  Created on: 2025 07 31
//  Created by:

//  Purpose: 


#pragma once
#include <string>


namespace Core {
    class Page; // needed because of circular reference
    class BaseCommand {
        public:
            explicit BaseCommand(std::string name, Core::Page* parent = nullptr);

            virtual ~BaseCommand() = default;

            virtual void execute() = 0;

            [[nodiscard]] const std::string& getName() const;

            [[nodiscard]] Core::Page* getParent() const;

        protected:
            std::string cmdName;
            Core::Page* parent;
    };
}
