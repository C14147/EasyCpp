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
 * @file EasyCpp/String/String.h
 * @brief This file implements a custom String class that mimics some of the methods of Python's str type.
 *        It uses the fmt library for string formatting and follows ISO C++ 23 standards.
 */
#pragma once
#define _EASYCPP_STRING_VERSION "1.0.0"
#define STRING_FOMATER const char *
#define esb easycpp::String(
#define ese )

#include <iostream>
#include <cstring>
#include <algorithm>
#include <Packages/fmt/format.h>

namespace easycpp{
    /**
     * @class String
     * @brief A custom string class that provides similar functionality to Python's str type.
     */
    class String {
    private:
        char* data;
        size_t length;

    public:
        /**
         * @brief Default constructor. Initializes an empty string.
         */
        String() : data(nullptr), length(0) {}

        /**
         * @brief Parameterized constructor. Initializes the string with the given C-style string.
         * @param str A C-style string to initialize the object with.
         */
        String(const char* str) {
            if (str == nullptr) {
                length = 0;
                data = new char[1];
                data[0] = '\0';
            } else {
                length = std::strlen(str);
                data = new char[length + 1];
                std::strcpy(data, str);
            }
        }

        /**
         * @brief Copy constructor. Creates a new String object as a copy of another.
         * @param other The String object to copy from.
         */
        String(const String& other) {
            length = other.length;
            data = new char[length + 1];
            std::strcpy(data, other.data);
        }

        /**
         * @brief Destructor. Frees the memory allocated for the string.
         */
        ~String() {
            delete[] data;
        }

        /**
         * @brief Overloaded assignment operator. Assigns the value of another String object.
         * @param other The String object to assign from.
         * @return A reference to the modified String object.
         */
        String& operator=(const String& other) {
            if (this != &other) {
                delete[] data;
                length = other.length;
                data = new char[length + 1];
                std::strcpy(data, other.data);
            }
            return *this;
        }

        /**
         * @brief Overloaded assignment operator. Assigns the value of a C-style string.
         * @param str The C-style string to assign from.
         * @return A reference to the modified String object.
         */
        operator const char*() const {
            return data;
        }

        /**
         * @brief Overloaded conversion operator. Converts the String object to a std::string.
         * @return A std::string representation of the String object.
         */
        operator std::string() const {
            return std::string(data);
        }

        /**
         * @brief Returns the length of the string.
         * @return The length of the string.
         */
        size_t len() const {
            return length;
        }

        /**
         * @brief Converts the string to uppercase.
         * @return A new String object with all characters in uppercase.
         */
        String upper() const {
            String result(*this);
            for (size_t i = 0; i < length; ++i) {
                result.data[i] = std::toupper(result.data[i]);
            }
            return result;
        }

        /**
         * @brief Converts the string to lowercase.
         * @return A new String object with all characters in lowercase.
         */
        String lower() const {
            String result(*this);
            for (size_t i = 0; i < length; ++i) {
                result.data[i] = std::tolower(result.data[i]);
            }
            return result;
        }

        /**
         * @brief Checks if the string ends with the specified suffix.
         * @param suffix The suffix to check for.
         * @return true if the string ends with the suffix, false otherwise.
         */
        bool endswith(const String& suffix) const {
            if (suffix.length > length) return false;
            return std::strcmp(data + length - suffix.length, suffix.data) == 0;
        }

        /**
         * @brief Checks if the string starts with the specified prefix.
         * @param prefix The prefix to check for.
         * @return true if the string starts with the prefix, false otherwise.
         */
        bool startswith(const String& prefix) const {
            if (prefix.length > length) return false;
            return std::strncmp(data, prefix.data, prefix.length) == 0;
        }

        /**
         * @brief Finds the first occurrence of a substring in the string.
         * @param sub The substring to search for.
         * @return The index of the first occurrence of the substring, or -1 if not found.
         */
        int find(const String& sub) const {
            const char* pos = std::strstr(data, sub.data);
            if (pos == nullptr) return -1;
            return static_cast<int>(pos - data);
        }

        /**
         * @brief Formats the string using the fmt library.
         * @tparam Args The types of the arguments to be used for formatting.
         * @param args The arguments to be used for formatting.
         * @return A new String object with the formatted string.
         */
        template<typename... Args>
        String format(Args&&... args) const {
            std::string formatted = fmt::format(std::string(data), std::forward<Args>(args)...);
            return String(formatted.c_str());
        }

        /**
         * @brief Overloaded output stream operator. Prints the string to an output stream.
         * @param os The output stream to print to.
         * @param str The String object to print.
         * @return A reference to the output stream.
         */
        friend std::ostream& operator<<(std::ostream& os, const String& str) {
            os << str.data;
            return os;
        }

        /**
         * @brief Overloaded + operator. Concatenates two String objects.
         * @param other The String object to concatenate with.
         * @return A new String object containing the concatenated string.
         */
        String operator+(const String& other) const {
            size_t newLength = length + other.length;
            char* newData = new char[newLength + 1];
            std::strcpy(newData, data);
            std::strcat(newData, other.data);
            String result(newData);
            delete[] newData;
            return result;
        }

        /**
         * @brief Overloaded + operator. Concatenates a String object and a C-style string.
         * @param other The C-style string to concatenate with.
         * @return A new String object containing the concatenated string.
         */
        String operator+(const char* other) const {
            size_t otherLength = std::strlen(other);
            size_t newLength = length + otherLength;
            char* newData = new char[newLength + 1];
            std::strcpy(newData, data);
            std::strcat(newData, other);
            String result(newData);
            delete[] newData;
            return result;
        }
    };
}    
