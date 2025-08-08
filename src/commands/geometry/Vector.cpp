
// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

//  vector.cpp

//  Created on: 2025 08 01
//  Created by:

//  Purpose:

#include "commands/geometry/Vector.hpp"

#include "core/Logger.hpp"

namespace Commands::Geometry {
    void Vector::setup() { LOG("Vector cmd setup called"); }

    Core::ECommandResult Vector::tick(std::string &input) {
        LOG("Vector command executed with args "+ input);
        return Core::ECommandResult::OK;
    }

    void Vector::exit() { LOG("Exitting vector cmd"); }
}
