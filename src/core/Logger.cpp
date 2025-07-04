
// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

//  Logger.cpp

//  Created on: 2025 06 14
//  Created by: thatgato

//  Purpose: Handles the logging events, such as taking an already created child process and then logging onto that process' console window, and saving some logs to files.


#include "core/Logger.hpp"
#include "core/Logger.hpp"
#include <chrono>
#include <iostream>
#include <fstream>
#include <ranges>

#include "core/LogMessages.hpp"

namespace Core {
    std::ofstream Logger::logFileStream;
    std::mutex Logger::mtx;
    bool Logger::consoleEnabled                            = false;
    std::unique_ptr<ConsoleProcess> Logger::consoleProcess = nullptr;


    std::unordered_map<Logger::Level, EColor> Logger::logLvlToColor = {
        {Logger::Level::INFO, EColor::WHITE},
        {Logger::Level::WARNING, EColor::ORANGE},
        {Logger::Level::ERR, EColor::RED},
        {Logger::Level::TRACE, EColor::GRAY},
    };
    std::unordered_map<Logger::Level, std::string> Logger::logLvlToStr = {
        {Logger::Level::INFO, "INFO"},
        {Logger::Level::WARNING, "WARN"},
        {Logger::Level::ERR, "ERR"},
        {Logger::Level::TRACE, "TRACE"},
    };

    void Logger::Init(std::string logFilePath, bool createConsole) {
        // TODO File logging
        std::lock_guard<std::mutex> lock(mtx);


        // Console logging
        if (createConsole) {
            const std::string conTitle = "SCLI LOGS";
            consoleProcess             = std::make_unique<ConsoleProcess>(const_cast<std::string &>(conTitle));
            if (!consoleProcess->Spawn("cmd.exe", "/Q /K")) {
                std::cout << "fuck" << std::endl;
                throw std::runtime_error("Failed to spawn logger console");
            }


            LOG(LogMsg::SpawnedConsole);
            LOG(LogMsg::InitSuccess);

            consoleEnabled = true;
        }
    }

    void Logger::Log(const std::string message, const std::string fileName, const std::string funcName,
                     Level level, bool overrideMsgColor = false) {
        std::string final = "echo ";

        if (overrideMsgColor) {
            final += "[" + logLvlToStr[level] + "] [" + fileName + "::" + funcName + "]: " + message;
        } else {
            final += CWRAP("[" + logLvlToStr[level] + "] [" + fileName + "::" + funcName + "]: " + message,
                           logLvlToColor[level]);
        }

        consoleProcess->Write(final);
    }

    // void Logger::Log(const std::string_view message, const std::string_view fileName, const std::string_view funcName,
    //                  Level level) { consoleProcess->Write(std::views::join(std::array{std::string_view {"echo "}, message})); }

    std::string Logger::getTimestamp() {
        auto now        = std::chrono::system_clock::now();
        auto clocktimet = std::chrono::system_clock::to_time_t(now);

        std::ostringstream oss;
        oss << std::put_time(std::localtime(&clocktimet), "%H:%M:%S") << std::setfill('0') << std::setw(2);

        return oss.str();
    }

    std::string Logger::levelToStr(Level lvl) noexcept {
        switch (lvl) {
            case Level::TRACE:
                return "TRACE";
            case Level::INFO:
                return "INFO";
            case Level::WARNING:
                return "WARNING";
            case Level::ERR:
                return "ERROR";
        }
        return "UNKNOWN";
    }
}
