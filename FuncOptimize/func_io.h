// EasyCpp - String : A Powerful C++ String Class
// Copyright (C) 2025  C14147
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

/**
 * @file EasyCpp/FuncOptimize/func_io.h
 * @brief This file provides a function to print formatted strings with custom separators and endings.
 */

#include <String/String.h>
#include <List/List.h>
#include <Packages/fmt/core.h>
#include <string>
#include <vector>

namespace easycpp {
    /**
     * @brief Prints formatted strings with custom separators and endings.
     * @param args The arguments to be printed.
     */
    template <typename... Args>
    void print(
        const Args&... objects, 
        const std::string& sep = " ", 
        const std::string& end = "\n"
    ) {
        // TODO
        return;
    }
}