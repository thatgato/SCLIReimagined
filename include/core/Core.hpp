
// Copyright (c) 2025. @thatgato
// This file is a part of SCLIReimagined, which is licensed under the GNU GPLv3 license.
// See the LICENSE file for more information.


#pragma once
#include <stack>
#include <memory>

namespace Core {
    class Application {
        //std::stack<std::weak_ptr<Page> > navStack;

        public:
            void Startup(int argc, char *argv[]);
    };
}
