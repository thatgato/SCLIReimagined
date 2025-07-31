

// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

#pragma once
#include <memory>
#include <string>
#include <vector>

#include "BaseCommand.hpp"

namespace Core {
    class Page {
        public:
            explicit Page(std::string name, Page* parent = nullptr);

            void SetDesc(std::string desc);

            void AddChildPage(std::unique_ptr<Page> child);

            void AddChildCommand(std::unique_ptr<BaseCommand> child);

            [[nodiscard]] Page* GetParent() const;

            [[nodiscard]] const std::string& GetName() const;

            [[nodiscard]] bool ContainsCommands() const;

            [[nodiscard]] bool ContainsPages() const;

            [[nodiscard]] const std::vector<std::unique_ptr<Page>>& GetPages() const;

            [[nodiscard]] const std::vector<std::unique_ptr<BaseCommand>>& GetCommands() const;

        private:
            std::string m_name;
            Page* m_parent;
            std::string m_desc = "No description provided. The developer was too lazy >.>";
            std::vector<std::unique_ptr<Page>> m_pageChildren;
            std::vector<std::unique_ptr<BaseCommand>> m_commandChildren;
    };
}
