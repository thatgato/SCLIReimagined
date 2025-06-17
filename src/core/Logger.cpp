
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

namespace Core {
    std::ofstream Logger::logFileStream;
    HANDLE Logger::hConsole = nullptr;
    std::mutex Logger::mtx;
    bool Logger::consoleEnabled = false;

    const std::string conTitle                      = "SCLI LOGS";
    std::unique_ptr<Process> Logger::consoleProcess = std::make_unique<Process>(const_cast<std::string &>(conTitle));

    void Logger::Init(std::string logFilePath, bool createConsole) {
        // TODO File logging
        std::lock_guard<std::mutex> lock(mtx);


        // Console logging
        if (createConsole) {
            if (!consoleProcess->Spawn("cmd.exe", "/k type CON")) {
                throw std::runtime_error("Failed to spawn logger console");
            }

            consoleEnabled = true;
        }
    }

    void Logger::Log(const std::string message, const std::string fileName, const std::string funcName,
                     Level level) { writeToConsole(message); }

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

    void Logger::writeToConsole(const std::string &message) {
        if (!consoleProcess || !consoleProcess->IsRunning()) {
            std::cout << "Attempt to write to console process that is not running" << std::endl;
            return;
        }

        HANDLE hPipe = consoleProcess->GetWriteHandle();
        if (hPipe == INVALID_HANDLE_VALUE) {
            std::cout << "Invalid handle" << std::endl;
            return;
        }

        DWORD bytesWritten;
        WriteFile(hPipe, message.c_str(), message.size(), &bytesWritten, nullptr);
    }
}
