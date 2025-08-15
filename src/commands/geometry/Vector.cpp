
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
    void Vector::init() {
        // TODO: Make subcommands here
    }

    void Vector::setup() { LOG("Vector cmd setup called"); }

    Core::ECommandResult Vector::tick(std::string &input) {
        LOG("Vector command executed with args "+ input);

        auto splitInput = Util::StrSplit(input, ' ');

        const std::string &subCmdName = splitInput[0];
        const std::vector<std::string> subCmdArgs(splitInput.begin() + 1, splitInput.end());

        auto res = Util::ParseAlreadySplitCmdArgs(subCmdArgs);


        return Core::ECommandResult::OK;
    }

    void Vector::exit() { LOG("Exitting vector cmd"); }
}


// Ok so the plan here is to support N-sized vectors.
// How?
// We will add a subcommand like "def"/"define" which will define and store a vector.
// btw here by vector I mean the mathematical vector, not the std::vector
// we will have these in a map, for example map["v1"] = vector(1,2,3)
// we can manipulate these by calling other commands such as "del", "cpy" or whatever later
// and then perform arithmetic on them with stuff like "add v1 v2" -> this will add the vectors stored in "v1" and "v2" together
// we could also add flags such as "add v1 v2 --s v3" which will save the addition into the v3 vector
