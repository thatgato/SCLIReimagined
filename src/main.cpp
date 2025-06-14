// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

#include <iostream>
#include "core/Core.hpp"
#include <windows.h>

int main() {
    std::cout << "Application starting..." << std::endl;

    //Core::Application app;

    //app.Startup(argc, argv);

    // TODO Experiment with this snippet of code and the windows API
    // to create a child process with a separate console window in
    // order to create a logger on Core::Application::Startup()!

    HANDLE childStdoutWrite = nullptr;
    HANDLE childStdinRead   = nullptr;

    STARTUPINFOA si{};
    si.cb         = sizeof(STARTUPINFO);
    si.hStdError  = childStdoutWrite;
    si.hStdOutput = childStdoutWrite;
    si.hStdInput  = childStdinRead;
    si.dwFlags |= STARTF_USESTDHANDLES;
    PROCESS_INFORMATION pi{};

    std::string cmdLine = "cmd.exe";
    CreateProcessA(NULL, const_cast<char *>(cmdLine.c_str()), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL,
                   NULL, &si,
                   &pi);

    std::cin.get();
    TerminateProcess(pi.hProcess, 0);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}
