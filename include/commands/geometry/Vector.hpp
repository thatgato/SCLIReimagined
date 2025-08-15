

// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

#pragma once
#include <utility>

#include "core/BaseCommand.hpp"


namespace Commands::Geometry {
    class Vector : public Core::BaseCommand {
        public:
            explicit Vector(std::string name, Core::Page* parent)
                : BaseCommand(std::move(name), parent) {}

            void init() override;

            void setup() override;

            Core::ECommandResult tick(std::string &input) override;

            void exit() override;
    };
}
