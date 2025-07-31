
// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

//  BaseCommand.cpp

//  Created on: 2025 07 31
//  Created by:

//  Purpose: 


#include <utility>

#include "../../include/core/BaseCommand.hpp"

BaseCommand::BaseCommand(std::string name, BaseCommand *parent)
    : cmdName(std::move(name)), parent(parent) {}

const std::string &BaseCommand::getName() const { return cmdName; }
BaseCommand *BaseCommand::getParent() const { return parent; }
