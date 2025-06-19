// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

#include <iostream>
#include <windows.h>
#include "core/Color.hpp"
#include "core/Core.hpp"
#include "core/Logger.hpp"

int main() {
    std::cout << "Application starting..." << std::endl;

    // Just to be sure!:)
    HANDLE hOut  = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    //Core::Application app;

    //app.Startup(argc, argv);

    // testing purposes

    std::cout << CWRAP("afkdsnf", EColor::RED) << std::endl;

    // TODO ONE OR BOTH OF THESE LINES CAUSE A COMPILE CRASH
    Core::Logger::Init("");
    Core::Logger::Log("What", "", "");

    std::cin.get();

    return 0;
}
