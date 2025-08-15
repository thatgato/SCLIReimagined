
// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.

//  BaseCommand.hpp

//  Created on: 2025 07 31
//  Created by:

//  Purpose: 


#pragma once
#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <sstream>
#include <stdexcept>

#include "internal/util/GeneralUtil.hpp"


namespace Core {
    enum class ECommandResult {
        OK,
        FORCE_EXIT // not sure if we will need this as of rn
    };

    class Page; // needed because of circular reference
    class BaseCommand {
        public:
            explicit BaseCommand(std::string name, Page* parent = nullptr);

            virtual ~BaseCommand() = default;

            virtual void setup() = 0;

            virtual ECommandResult tick(std::string &input) = 0;

            virtual void exit() = 0;

            [[nodiscard]] const std::string& GetName() const;

            [[nodiscard]] Page* getParent() const;

        protected:
            std::string m_cmdName;
            Page* m_parent;


            // I'm going to put the code explanation here in comments because I did not understand this at first
            template<typename... Args> // template with ..., self-explanatory, variadic arguments
            std::function<void(const std::vector<std::string> &)>
            // ^^ we return a function that takes a vector of strings; this is the uniform callable type for all sub-commands
                makeCommand(std::function<void(Args...)> func) {
                // ^^ the function to wrap (usually just [this](...) {call the actual func here with (...)}
                return [func](const std::vector<std::string> &args) {
                    // ^^ copy the function and return this lambda that will validate all the stuff and do the parsing; finally calling the actual function

                    if (args.size() != sizeof...(Args)) {
                        // TODO: Switch this for LOGE() later when the actual logging .exe is done
                        std::cout << "Error: Expected " << sizeof...(Args)
                                << " arguments, got " << args.size() << "\n";
                        return;
                    }

                    size_t i     = 0;
                    bool allGood = true;

                    // Inner lambda that parses with error checking
                    auto parseWithCheck = [&]<typename T0>([[maybe_unused]] T0 typeTag) {
                        // fancy explicit template for type deduction:3
                        using T          = T0;
                        auto [ok, value] = Util::TryParseFromStr<T>(args[i++]);
                        if (!ok) {
                            allGood = false;
                            std::cout << "Error: Failed to parse argument #" << i << "\n";
                        }
                        return value;
                    };

                    // Only call func if all arguments parsed OK
                    if constexpr (sizeof...(Args) > 0) {
                        auto callIfValid = [&](auto &&... parsed) { if (allGood) func(parsed...); };
                        callIfValid(parseWithCheck(Args{})...);
                    }
                };
            }
    };
}
