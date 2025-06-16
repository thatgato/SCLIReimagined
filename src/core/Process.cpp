
// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

//  Process.cpp

//  Created on: 2025 06 16
//  Created by: thatgato

//  Purpose: Abstract a windows.h API related process into a C++ class for later use

#include "core/Process.hpp"


namespace Core {
    Process::Process(std::string &wTitle) : wTitle(wTitle) {
        SECURITY_ATTRIBUTES saAttr;
        saAttr.nLength              = sizeof(SECURITY_ATTRIBUTES);
        saAttr.bInheritHandle       = TRUE;
        saAttr.lpSecurityDescriptor = NULL;

        if (!CreatePipe(&hStdinRead, &hStdinWrite, &saAttr, 0)) {
            throw std::runtime_error("Failed to create pipe for process instance");
        }
    }

    Process::~Process() { Kill(); }

    bool Process::Spawn(const std::string &pPath, const std::string &args) {
        STARTUPINFOA si;
        si.cb      = sizeof(STARTUPINFOA);
        si.lpTitle = const_cast<char *>(wTitle.c_str());
        si.dwFlags = STARTF_FORCEONFEEDBACK | STARTF_USESTDHANDLES;

        std::string cmdLine = pPath + " " + args;

        // Try to create the process
        if (!CreateProcessA(
                            nullptr,
                            cmdLine.data(),
                            nullptr,
                            nullptr,
                            TRUE,
                            CREATE_NEW_CONSOLE,
                            nullptr,
                            nullptr,
                            &si,
                            &pi
                           )) { return false; }
        return true;
    }

    bool Process::IsRunning() {
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
