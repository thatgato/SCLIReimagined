
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
    enum class ECommandResult {
        OK,
        FORCE_EXIT // not sure if we will need this as of rn
    };

    class Page; // needed because of circular reference
    class BaseCommand {
        public:
            explicit BaseCommand(std::string name, Page* parent = nullptr);

            virtual ~BaseCommand() = default;

            virtual void setup() = 0;

            virtual ECommandResult tick(std::string &input) = 0;

            virtual void exit() = 0;

            [[nodiscard]] const std::string& GetName() const;

            [[nodiscard]] Page* getParent() const;

        protected:
            std::string m_cmdName;
            Page* m_parent;
    };
}
