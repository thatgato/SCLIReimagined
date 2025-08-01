

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

            template<typename T, typename... Args>
            T* AddChild(Args &&... args) {
                constexpr bool baseOfCmd  = std::is_base_of_v<BaseCommand, T>;
                constexpr bool baseOfPage = std::is_base_of_v<Page, T>;
                static_assert(baseOfCmd || baseOfPage,
                              "You can only add a child to a page if it derives from BaseCommand or BasePage.");

                // this forwarding stuff is cool, look into it later
                auto child = std::make_unique<T>(std::forward<Args>(args)..., this);
                auto ptr   = child.get();
                if constexpr (baseOfCmd == true) { m_commandChildren.push_back(std::move(child)); } else {
                    m_pageChildren.push_back(std::move(child));
                }
                return ptr;
            }

            [[nodiscard]] Page* GetParent() const;

            [[nodiscard]] const std::string& GetName() const;

            [[nodiscard]] bool ContainsCommands() const;

            [[nodiscard]] bool ContainsPages() const;

            [[nodiscard]] const std::vector<std::unique_ptr<Page>>& GetPages() const;

            [[nodiscard]] const std::vector<std::unique_ptr<BaseCommand>>& GetCommands() const;

        protected:
            std::string m_name;
            Page* m_parent;
            std::string m_desc = "No description provided, I was too lazy";
            std::vector<std::unique_ptr<Page>> m_pageChildren;
            std::vector<std::unique_ptr<BaseCommand>> m_commandChildren;
    };
}
