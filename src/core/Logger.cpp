
// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

//  Logger.cpp

//  Created on: 2025 06 14
//  Created by: thatgato

//  Purpose: Handles the logging events, such as taking an already created child process and then logging onto that process' console window, and saving some logs to files.


#include "core/Logger.hpp"
#include <chrono>
#include <iostream>
#include <fstream>

namespace Core {
    std::ofstream Logger::logFileStream;
    std::mutex Logger::mtx;
    bool Logger::consoleEnabled                            = false;
    std::unique_ptr<ConsoleProcess> Logger::consoleProcess = nullptr;


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
            consoleProcess->Write("prompt $e");
            consoleProcess->Write("cls");

            Logger::Log("AAAAAAAA", "", "");

            consoleEnabled = true;
        }
    }

    void Logger::Log(const std::string message, const std::string fileName, const std::string funcName,
                     Level level) {
        // std::ostringstream oss;
        // oss << "echo " << message;
        consoleProcess->Write("echo " + message);
    }

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
