

// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

#pragma once
#include <string>

#include <windows.h>
#include <mutex>
#include <fstream>

#include "core/ConsoleProcess.hpp"

namespace Core {
    class Logger {
        public:
            Logger() = delete;

            enum class Level { TRACE, INFO, WARNING, ERR };

            // We don't really have to create separate logger objects, just make it static
            // and use a macro for extracting file names and function names

            static void Init(std::string logFilePath, bool createConsole = true);

            static void Log(const std::string message, const std::string fileName, const std::string funcName,
                            Level level = Level::INFO);

            // static void Log(const std::string_view message, const std::string_view fileName,
            // const std::string_view funcName,
            // Level level = Level::INFO);


            #define LOG(msg) Core::Logger::Log(msg, __FILE__, __FUNCTION__, Core::Logger::Level::TRACE)
            #define LOG_INFO(msg) Core::Logger::Log(msg, __FILE__, __FUNCTION__, Core::Logger::Level::INFO)
            #define LOG_WARN(msg) Core::Logger::Log(msg, __FILE__, __FUNCTION__, Core::Logger::Level::WARNING)
            #define LOG_ERR(msg) Core::Logger::Log(msg, __FILE__, __FUNCTION__, Core::Logger::Level::ERR)

        private:
            [[nodiscard]] static std::string getTimestamp();

            [[nodiscard]] static std::string levelToStr(Level lvl) noexcept;

            static std::ofstream logFileStream;
            static std::mutex mtx; // thread safe because who knows what will happen in the future
            static bool consoleEnabled;

            static std::unique_ptr<ConsoleProcess> consoleProcess;
    };
}
