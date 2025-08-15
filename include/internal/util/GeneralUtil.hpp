

// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

#pragma once
#include <sstream>
#include <unordered_map>
#include <vector>


namespace Internal {
    struct CmdArgParseResult {
        std::vector<std::string> positionals;
        std::unordered_map<std::string, std::string> flags; // string value, can be empty for toggle flags
    };

    class Util {
        public:
            static bool TryParseInt(const std::string &str, int &outValue);

            static void StrLower(std::string &outStr);

            static void StrUpper(std::string &outStr);

            static std::vector<std::string> StrSplit(const std::string &str, char delimiter);

            // Looks through a vector of strings (already split input) to determine which members are normal command arguments and which are flags such as "--foo bar"
            // should not contain the initial command name (ex: "add 1 2" should be passed as ("1","2") into this, not ("add","1","2"))
            static CmdArgParseResult ParseAlreadySplitCmdArgs(const std::vector<std::string> &args);

            template<typename T>
            static std::tuple<bool, T> TryParseFromStr(const std::string &s) {
                std::istringstream iss(s);
                T value{};
                if (!(iss >> value)) {
                    return {false, T{}}; // failed, return default-constructed T
                }
                return {true, value};
            }

            static std::string GenerateIndent(uint16_t depth = 0);

        private:
    };
}

using Util              = Internal::Util;
using CmdArgParseResult = Internal::CmdArgParseResult;
