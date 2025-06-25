

// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

#pragma once
#include <string>
#include "core/Color.hpp"

// Pre-defined log messages for use later

namespace Core {
    class LogMessages {
        LogMessages() = delete;

        public:
            inline static const std::string InitSuccess     = "Logger initialized successfully!";
            inline static const std::string SpawningConsole = "Attempting to spawn console window...";
            inline static const std::string SpawnedConsole  = "Successfully spawned console window!";
    };
}

using LogMsg = Core::LogMessages;
