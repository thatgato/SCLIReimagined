

// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

#pragma once
#include <string>
#include <windows.h>

namespace Core {
    class Process {
        PROCESS_INFORMATION pi;
        HANDLE hStdinRead, hStdinWrite;
        std::string wTitle;

        public:
            explicit Process(const std::string &wTitle);

            ~Process();

            bool Spawn(const std::string &pPath, const std::string &args = "");

            bool IsRunning() const;

            void Kill();

            [[nodiscard]] HANDLE GetWriteHandle() const;
    };
}
