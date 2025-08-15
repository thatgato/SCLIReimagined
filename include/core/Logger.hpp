

// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

#pragma once
#include <string>

#include <mutex>
#include <fstream>
#include <unordered_map>

#include "Color.hpp"
#include "ConsoleProcess.hpp"


namespace Core {
    class Logger {
        public:
            Logger() = delete;

            enum class Level { TRACE, INFO, WARNING, ERR };

            // We don't really have to create separate logger objects, just make it static
            // and use a macro for extracting file names and function names

            static void Init(std::string logFilePath, bool createConsole = true);

            static void Log(std::string message, std::string fileName, std::string funcName, Level level,
                            bool overrideMsgColor);


            // static void Log(const std::string_view message, const std::string_view fileName,
            // const std::string_view funcName,
            // Level level = Level::INFO);

            // lol
            #define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)

            #define LOG(msg) Core::Logger::Log(msg, __FILENAME__, __FUNCTION__, Core::Logger::Level::TRACE, false)
            #define LOGI(msg) Core::Logger::Log(msg, __FILENAME__, __FUNCTION__, Core::Logger::Level::INFO, false)
            #define LOGW(msg) Core::Logger::Log(msg, __FILENAME__, __FUNCTION__, Core::Logger::Level::WARNING, false)
            #define LOGE(msg) Core::Logger::Log(msg, __FILENAME__, __FUNCTION__, Core::Logger::Level::ERR, false)

            #define LOGOW(msg) Core::Logger::Log(msg, __FILENAME__, __FUNCTION__, Core::Logger::Level::TRACE, true)
            #define LOGIOW(msg) Core::Logger::Log(msg, __FILENAME__, __FUNCTION__, Core::Logger::Level::INFO, true)
            #define LOGWOW(msg) Core::Logger::Log(msg, __FILENAME__, __FUNCTION__, Core::Logger::Level::WARNING, true)
            #define LOGEOW(msg) Core::Logger::Log(msg, __FILENAME__, __FUNCTION__, Core::Logger::Level::ERR, true)

        private:
            [[nodiscard]] static std::string getTimestamp();

            [[nodiscard]] static std::string levelToStr(Level lvl) noexcept;

            static std::ofstream logFileStream;
            static std::mutex mtx; // thread safe because who knows what will happen in the future
            static bool consoleEnabled;

            static std::unique_ptr<ConsoleProcess> consoleProcess;
            static std::unordered_map<Level, EColor> logLvlToColor;
            static std::unordered_map<Level, std::string> logLvlToStr;
    };
}
