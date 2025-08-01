// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

#include <iostream>
#include <windows.h>
#include "core/Color.hpp"
#include "core/Core.hpp"
#include "core/Logger.hpp"
#include "core/LogMessages.hpp"

int main(int argc, char** argv) {
    std::cout << "Application starting..." << std::endl;

    // Just to be sure!:)
    HANDLE hOut  = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);


    std::cout << LogMsg::SpawningConsole << std::endl;

    Core::Logger::Init("");

    LOG("Hello from logger!");
    LOG_WARN("Warn from logger!");
    LOG_ERR("Error from logger!");
    LOG(CWRAP("Hello from logger, with color overrides!", EColor::CYAN));

    Core::Application::Startup(argc, argv);

    std::cin.get();

    return 0;
}
