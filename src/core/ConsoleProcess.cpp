
// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

//  Process.cpp

//  Created on: 2025 06 16
//  Created by: thatgato

//  Purpose: Abstract a windows.h API related process into a C++ class for later use

#include "core/ConsoleProcess.hpp"

#include <iostream>
#include <ranges>

namespace Core {
    ConsoleProcess::ConsoleProcess(std::string &wTitle) : pi(), hStdinRead(nullptr), wTitle(wTitle) {}

    ConsoleProcess::~ConsoleProcess() { Kill(); }

    bool ConsoleProcess::Spawn(const std::string &pPath, const std::string &args) {
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

        pi = {nullptr};

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

        this->Write("prompt $e");
        this->Write("cls");
        return true;
    }

    bool ConsoleProcess::IsRunning() const {
        if (pi.hProcess == nullptr) return false;

        DWORD exitCode;
        GetExitCodeProcess(pi.hProcess, &exitCode);
        return exitCode == STILL_ACTIVE;
    }

    void ConsoleProcess::Kill() {
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

    void ConsoleProcess::Write(const std::string &msg) const {
        if (!this->IsRunning()) {
            std::cout << "Attempt to write to console process that is not running" << std::endl;
            return;
        }

        DWORD bytesWritten;
        std::string msgWithNewline = msg + "\r\n";
        WriteFile(
                  this->hStdinWrite,
                  msgWithNewline.c_str(),
                  static_cast<DWORD>(msgWithNewline.size()),
                  &bytesWritten,
                  nullptr
                 );
        FlushFileBuffers(this->hStdinWrite);
    }

    // void ConsoleProcess::Write(std::string_view msg) const { figure out how to make this thing work........
    //     if (!this->IsRunning()) {
    //         std::cout << "Attempt to write to console process that is not running" << std::endl;
    //         return;
    //     }
    //
    //     DWORD bytesWritten;
    //     std::string_view msgWithNewline = std::views::join(std::array { msg, std::string_view {"\r\n"} });
    //     BOOL success               = WriteFile(
    //                                            this->hStdinWrite,
    //                                            msgWithNewline.data(),
    //                                            static_cast<DWORD>(msgWithNewline.size()),
    //                                            &bytesWritten,
    //                                            NULL
    //                                           );
    //     // std::cout << "MSg info" << std::endl;
    //     // std::cout << msgWithNewline << std::endl;
    //     // std::cout << success << std::endl;
    //     FlushFileBuffers(this->hStdinWrite);
    // }
}
