
// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

//  BaseCommand.cpp

//  Created on: 2025 07 31
//  Created by:

//  Purpose: 


#include <utility>

#include "../../include/core/BaseCommand.hpp"

Core::BaseCommand::BaseCommand(std::string name, Page* parent)
    : m_cmdName(std::move(name)), m_parent(parent) {}

const std::string& Core::BaseCommand::getName() const { return m_cmdName; }
Core::Page* Core::BaseCommand::getParent() const { return m_parent; }
