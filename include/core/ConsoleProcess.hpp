

// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

#pragma once
#include <string>
#include <windows.h>

namespace Core {
    class ConsoleProcess {
        PROCESS_INFORMATION pi;
        HANDLE hStdinRead, hStdinWrite = nullptr;
        std::string wTitle;

        public:
            explicit ConsoleProcess(std::string &wTitle);

            ~ConsoleProcess();

            bool Spawn(const std::string &pPath, const std::string &args = "");

            [[nodiscard]] bool IsRunning() const;

            void Kill();

            void Write(const std::string& msg) const;

            // void Write(std::string_view msg) const;
    };
}
