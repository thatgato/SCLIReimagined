
// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

//  Process.cpp

//  Created on: 2025 06 16
//  Created by: thatgato

//  Purpose: Abstract a windows.h API related process into a C++ class for later use

#include "core/Process.hpp"


namespace Core {
    Process::Process(std::string &wTitle) : wTitle(wTitle) {}

    Process::~Process() { Kill(); }

    bool Process::Spawn(const std::string &pPath, const std::string &args) {
        SECURITY_ATTRIBUTES saAttr  = {0};
        saAttr.nLength              = sizeof(SECURITY_ATTRIBUTES);
        saAttr.bInheritHandle       = TRUE;
        saAttr.lpSecurityDescriptor = nullptr;

        if (!CreatePipe(&hStdinRead, &hStdinWrite, &saAttr, 0))
            throw std::runtime_error("Stdin pipe creation failed");

        SetHandleInformation(hStdinWrite, HANDLE_FLAG_INHERIT, 0);

        STARTUPINFOA si = {0};
        si.cb           = sizeof(STARTUPINFOA);
        si.lpTitle      = const_cast<char *>(wTitle.c_str());
        si.dwFlags |= STARTF_USESTDHANDLES;
        si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        si.hStdError  = GetStdHandle(STD_ERROR_HANDLE);
        si.hStdInput  = hStdinRead;

        pi = {0};

        std::string cmdLine = pPath + " " + args;

        // Try to create the process
        if (!CreateProcessA(
                            nullptr,
                            cmdLine.data(),
                            nullptr,
                            nullptr,
                            TRUE,
                            CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
                            nullptr,
                            nullptr,
                            &si,
                            &pi
                           )) { return false; }
        return true;
    }

    bool Process::IsRunning() const {
        if (pi.hProcess == nullptr) return false;

        DWORD exitCode;
        GetExitCodeProcess(pi.hProcess, &exitCode);
        return exitCode == STILL_ACTIVE;
    }

    void Process::Kill() {
        if (pi.hProcess) {
            TerminateProcess(pi.hProcess, 0);
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            pi.hProcess = nullptr;
        }

        // Cleanup on the pipes
        if (hStdinRead) CloseHandle(hStdinRead);
        if (hStdinWrite) CloseHandle(hStdinWrite);
    }

    HANDLE Process::GetWriteHandle() const { return hStdinWrite; }
}
