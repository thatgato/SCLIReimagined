
// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

//  Page.cpp

//  Created on: 2025 07 31
//  Created by:

//  Purpose:

#include <utility>

#include "core/Page.hpp"

Core::Page::Page(std::string name, Page* parent) : m_name(std::move(name)), m_parent(parent) {}

void Core::Page::SetDesc(std::string desc) { m_desc = std::move(desc); }

Core::Page* Core::Page::GetParent() const { return m_parent; }
const std::string& Core::Page::GetName() const { return m_name; }

bool Core::Page::ContainsCommands() const { return !m_commandChildren.empty(); }
bool Core::Page::ContainsPages() const { return !m_pageChildren.empty(); }

const std::vector<std::unique_ptr<Core::Page>>& Core::Page::GetPages() const { return m_pageChildren; }
const std::vector<std::unique_ptr<Core::BaseCommand>>& Core::Page::GetCommands() const { return m_commandChildren; }

std::string Core::Page::DescendantsToString(uint16_t indent) const {
    std::ostringstream stringStream;

    // Print current page
    stringStream << Util::GenerateIndent(indent) << "Page: " << this->GetName() << "\n";

    // Print commands in this page
    if (this->ContainsCommands()) {
        stringStream << Util::GenerateIndent(indent + 1) << "Commands:\n";
        for (const auto &cmd: this->GetCommands()) {
            stringStream << Util::GenerateIndent(indent + 2) << "- " << cmd->GetName() << "\n";
        }
    }

    // Recurse into child pages
    if (this->ContainsPages()) {
        stringStream << Util::GenerateIndent(indent + 1) << "Child Pages:\n";
        for (const auto &page: this->GetPages()) {
            stringStream << page->DescendantsToString(indent + 2); // recursive call
        }
    }

    return stringStream.str();
}



