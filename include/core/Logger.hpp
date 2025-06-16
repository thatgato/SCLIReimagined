

// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

#pragma once
#include <string>

#include <windows.h>
#include <mutex>
#include <fstream>

namespace Core {
    class Logger {
        public:
            enum class Level { TRACE, INFO, WARNING, ERR };

            // We don't really have to create separate logger objects, just make it static
            // and use a macro for extracting file names and function names

            static void Init(std::string &logFilePath, bool createConsole = true);

            static void Log(const std::string &message, const std::string &fileName, const std::string &funcName,
                            Level level = Level::INFO);


            #define LOG(msg, level) Logger::Log(msg, __FILE__, __FUNCTION__, level)

            static std::ofstream logFileStream;
            static std::mutex mtx; // thread safe because who knows what will happen in the future
            static HANDLE hConsole;
            static bool consoleEnabled;

            [[nodiscard]] static std::string getTimestamp();

            [[nodiscard]] static std::string levelToStr(Level lvl) noexcept;
    };
}
