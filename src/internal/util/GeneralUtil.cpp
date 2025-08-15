
// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

//  GeneralUtil.cpp

//  Created on: 2025 08 01
//  Created by:

//  Purpose:

#include "util/GeneralUtil.hpp"

#include <charconv>
#include <iostream>

#include "../../../include/core/Logger.hpp"


namespace Internal {
    bool Util::TryParseInt(const std::string &str, int &outValue) {
        auto result = std::from_chars(str.data(), str.data() + str.size(), outValue);
        return result.ec == std::errc() && result.ptr == str.data() + str.size();
    }

    void Util::StrLower(std::string &outStr) {
        std::transform(outStr.begin(), outStr.end(), outStr.begin(),
                       [](unsigned char c) { return std::tolower(c); });
    }

    void Util::StrUpper(std::string &outStr) {
        std::transform(outStr.begin(), outStr.end(), outStr.begin(),
                       [](unsigned char c) { return std::toupper(c); });
    }

    std::vector<std::string> Util::StrSplit(const std::string &str, char delimiter) {
        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end   = str.find(delimiter);
        while (end != std::string::npos) {
            tokens.push_back(str.substr(start, end - start));
            start = end + 1;
            end   = str.find(delimiter, start);
        }

        tokens.push_back(str.substr(start));
        return tokens;
    }

    CmdArgParseResult Util::ParseAlreadySplitCmdArgs(const std::vector<std::string> &args) {
        CmdArgParseResult result;
        for (size_t i = 0; i < args.size(); ++i) {
            const std::string &a = args[i];

            if (a.rfind("--", 0) == 0) {
                // starts with --
                std::string optName = a.substr(2);
                std::string value;
                // Optionally consume next argument if it doesn't start with "-"
                if (i + 1 < args.size() && args[i + 1][0] != '-') { value = args[++i]; }
                LOG("Option: " + optName + ", value:" + value);
            } else if (a.rfind("-", 0) == 0) {
                // starts with -
                std::string flagName = a.substr(1);
                LOG("Flag: " + flagName);
            } else { LOG("Positional: " + a); }
        }
        return result;
    }

    std::string Util::GenerateIndent(uint16_t depth) {
        std::ostringstream stringStream;
        for (int i = 0; i < depth; ++i)
            stringStream << "  ";
        return stringStream.str();
    }
}
