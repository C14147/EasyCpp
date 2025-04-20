// EasyCpp - List : A Powerful C++ List Class
// Copyright (C) 2025  Li Zhengyi
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
 * @file EasyCpp/List/List.h
 * @brief This file implements a custom List class in C++.
 * The List class can store elements of multiple types using std::any and records the type information
 * of each element. It provides methods similar to Python's list data type.
 */

#include <iostream>
#include <vector>
#include <any>
#include <typeinfo>
#include <algorithm>
#include <optional>
#include <string>

/**
 * @class List
 * @brief A custom list class that can store elements of multiple types and record their type information.
 */
namespace easycpp {
    class List {
    private:
        std::vector<std::any> data;  // Vector to store the actual elements
        std::vector<const std::type_info*> types;  // Vector to store the type information of each element

    public:
        /**
         * @brief Default constructor. Initializes an empty list.
         */
        List() {}

        /**
         * @brief Copy constructor. Creates a new list with the same elements and type information as the given list.
         * @param other The list to be copied.
         */
        List(const List& other) : data(other.data), types(other.types) {}

        /**
         * @brief Get the number of elements in the list.
         * @return The size of the list.
         */
        size_t size() const {
            return data.size();
        }

        /**
         * @brief Check if the list is empty.
         * @return true if the list is empty, false otherwise.
         */
        bool empty() const {
            return data.empty();
        }

        /**
         * @brief Append an element of type T to the end of the list.
         * @tparam T The type of the element to be appended.
         * @param value The value of the element to be appended.
         */
        template<typename T>
        void append(const T& value) {
            data.push_back(std::any(value));
            types.push_back(&typeid(T));
        }

        /**
         * @brief Extend the list by appending all elements from another list.
         * @param other The list whose elements will be appended to this list.
         */
        void extend(const List& other) {
            data.insert(data.end(), other.data.begin(), other.data.end());
            types.insert(types.end(), other.types.begin(), other.types.end());
        }

        /**
         * @brief Insert an element of type T at the specified index.
         * @tparam T The type of the element to be inserted.
         * @param index The index at which the element will be inserted.
         * @param value The value of the element to be inserted.
         */
        template<typename T>
        void insert(size_t index, const T& value) {
            if (index <= data.size()) {
                data.insert(data.begin() + index, std::any(value));
                types.insert(types.begin() + index, &typeid(T));
            }
        }

        /**
         * @brief Remove the first occurrence of an element of type T with the given value.
         * @tparam T The type of the element to be removed.
         * @param value The value of the element to be removed.
         */
        template<typename T>
        void remove(const T& value) {
            auto it = std::find_if(data.begin(), data.end(), [&](const std::any& element) {
                return std::any_cast<T>(&element) && *std::any_cast<T>(&element) == value;
            });
            if (it != data.end()) {
                size_t index = std::distance(data.begin(), it);
                data.erase(it);
                types.erase(types.begin() + index);
            }
        }

        /**
         * @brief Remove and return the element at the specified index.
         * If no index is provided, remove and return the last element.
         * @param index An optional index of the element to be popped. Defaults to std::nullopt.
         * @return The popped element as a std::any object.
         * @throws std::out_of_range if the list is empty or the index is out of range.
         */
        std::any pop(std::optional<size_t> index = std::nullopt) {
            if (!index.has_value()) {
                if (data.empty()) {
                    throw std::out_of_range("List is empty, cannot pop.");
                }
                index = data.size() - 1;
            }
            if (index.value() < data.size()) {
                std::any value = data[index.value()];
                data.erase(data.begin() + index.value());
                types.erase(types.begin() + index.value());
                return value;
            }
            throw std::out_of_range("Index out of range");
        }

        /**
         * @brief Remove all elements from the list.
         */
        void clear() {
            data.clear();
            types.clear();
        }

        /**
         * @brief Find the index of the first occurrence of an element of type T with the given value, starting from the specified index.
         * @tparam T The type of the element to be found.
         * @param value The value of the element to be found.
         * @param start The index from which to start the search. Defaults to 0.
         * @return The index of the found element.
         * @throws std::invalid_argument if the element is not found.
         */
        template<typename T>
        size_t index(const T& value, size_t start = 0) const {
            for (size_t i = start; i < data.size(); ++i) {
                if (*types[i] == typeid(T) && std::any_cast<T>(&data[i]) && *std::any_cast<T>(&data[i]) == value) {
                    return i;
                }
            }
            throw std::invalid_argument("Value not found");
        }

        /**
         * @brief Count the number of occurrences of an element of type T with the given value in the list.
         * @tparam T The type of the element to be counted.
         * @param value The value of the element to be counted.
         * @return The number of occurrences of the element.
         */
        template<typename T>
        size_t count(const T& value) const {
            size_t count = 0;
            for (size_t i = 0; i < data.size(); ++i) {
                if (*types[i] == typeid(T) && std::any_cast<T>(&data[i]) && *std::any_cast<T>(&data[i]) == value) {
                    ++count;
                }
            }
            return count;
        }

        /**
         * @brief Reverse the order of the elements in the list.
         */
        void reverse() {
            std::reverse(data.begin(), data.end());
            std::reverse(types.begin(), types.end());
        }

        std::string join(const std::string& separator) const {
            std::string result;
            for (size_t i = 0; i < data.size(); ++i) {
                if (i > 0) {
                    result += separator;
                }
                if (this->data[i].has_value()) {
                    if (this->types[i] == &typeid(int)) {
                        result += std::to_string(std::any_cast<int>(this->data[i]));
                    } else if (this->types[i] == &typeid(double)) {
                        result += std::to_string(std::any_cast<double>(this->data[i]));
                    } else if (this->types[i] == &typeid(std::string)) {
                        result += std::any_cast<std::string>(this->data[i]);
                    } else {
                        result += "(" ;
                        result += (this->types[i]->name());
                        result += " at " ;
                        result += std::to_string((long long)&this->data[i]);
                        result += ")";
                    } 
                } else result = "";
            }
            return result;
        }

        /**
         * @brief Get the element at the specified index and cast it to type T.
         * @tparam T The type to which the element will be cast.
         * @param index The index of the element to be retrieved.
         * @return The element at the specified index, cast to type T.
         * @throws std::bad_any_cast if the type of the element at the index does not match T.
         */
        template<typename T>
        T get(size_t index) const {
            if (index < data.size() && *types[index] == typeid(T)) {
                return std::any_cast<T>(data[index]);
            }
            throw std::bad_any_cast();
        }

        /**
         * @brief Overload the [] operator to access an element at the specified index.
         * @param index The index of the element to be accessed.
         * @return A reference to the element at the specified index.
         */
        std::any& operator[](size_t index) {
            return data[index];
        }

        /**
         * @brief Overload the [] operator for const objects to access an element at the specified index.
         * @param index The index of the element to be accessed.
         * @return A const reference to the element at the specified index.
         */
        const std::any& operator[](size_t index) const {
            return data[index];
        }

        /**
         * @brief Overload the << operator to print the list in a human-readable format.
         * @param os The output stream.
         * @param list The list to be printed.
         * @return The output stream after printing the list.
         */
        friend std::ostream& operator<<(std::ostream& os, const List& list) {
            os << "[";
            for (size_t i = 0; i < list.data.size(); ++i) {
                if (i > 0) {
                    os << ", ";
                }
                if (list.data[i].has_value()) {
                    if (list.types[i] == &typeid(int)) {
                        os << std::any_cast<int>(list.data[i]);
                    } else if (list.types[i] == &typeid(double)) {
                        os << std::any_cast<double>(list.data[i]);
                    } else if (list.types[i] == &typeid(std::string)) {
                        os << std::any_cast<std::string>(list.data[i]);
                    } else {
                        os << "(" <<list.types[i]->name() << " at " << &list.data[i]<<")";
                    }
                } else {
                    os << "";
                }
            }
            os << "]";
            return os;
        }
    };
};