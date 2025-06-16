
// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

//  Logger.cpp

//  Created on: 2025 06 14
//  Created by: thatgato

//  Purpose: Handles the logging events, such as taking an already created child process and then logging onto that process' console window, and saving some logs to files.


#include "core/Logger.hpp"
#include <chrono>

namespace Core {
    std::ofstream Logger::logFileStream;
    HANDLE Logger::hConsole = nullptr;
    std::mutex Logger::mtx;
    bool Logger::consoleEnabled = false;

    std::string Logger::getTimestamp() {
        auto now        = std::chrono::system_clock::now();
        auto clocktimet = std::chrono::system_clock::to_time_t(now);

        std::ostringstream oss;
        oss << std::put_time(std::localtime(&clocktimet), "%H:%M:%S") << std::setfill('0') << std::setw(2);

        return oss.str();
    }

    std::string Logger::levelToStr(Level lvl) {
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
    }

    void Logger::Init(std::string &logFilePath, bool createConsole) {}

    void Logger::Log(const std::string &message, const std::string &fileName, const std::string &funcName,
                     Level level) {}
}
