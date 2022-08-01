/**
 * ///////////////////////////////////////////////////////////////////////////////
 * @file	InputParam.hpp
 * @brief	外部ファイルからパラメータを設定する
 *
 * @par templateの例外にある型以外は正しい値を帰してくれない。
 * modified https://github.com/kaityo256/param
 *
 * ///////////////////////////////////////////////////////////////////////////////
 */
/*
MIT License
Copyright (c) 2019 - present H. Watanabe
The latest version is available at
https://github.com/kaityo256/params

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

/* include header files */

/* end include header files*/

/* include standard files */
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>

/* end include standard files */

/* usingnamespace declaration(名前空間の宣言) */

/* end usingnamespace declaration*/

/* declaration MACRO */

/* end declaration MACRO */

/* prototype declaration */

/* end prototype declaration*/

/* declaration enumlation */

/* declaration namespace */

/* end declaration namespace */

namespace param {

typedef std::map<std::string, std::string> ptype;
class parameter {
   private:
    ptype params;
    bool valid;

    bool contains(std::string& key) const {
        return params.find(key) != params.end();
    }

    bool iequals(const string& a, const string& b) {
        return std::equal(
            a.begin(), a.end(), b.begin(), b.end(),
            [](char a, char b) { return tolower(a) == tolower(b); });
    }

   public:
    parameter(const std::string filename) : valid(true) {
        loadfromfile(filename);
    }

    explicit operator bool() const { return valid; };

    void loadfromfile(const std::string filename) {
        std::ifstream is(filename);
        if (is.fail()) {
            std::cerr << "Could not open file " << filename << std::endl;
            valid = false;
        }
        readfromstream(is);
    }

    void readfromstream(std::istream& is) {
        std::string line;
        while (getline(is, line)) {
            if (*(line.end() - 1) == 0x0d) line.pop_back();
            if (line.length() > 0 && line[0] == '#') {
                continue;
            }
            size_t index = line.find("=");
            if (std::string::npos != index) {
                std::string key   = line.substr(0, index);
                std::string value = line.substr(index + 1, line.length());
                params.insert(ptype::value_type(key, value));
            }
        }
    }
    void check_key(std::string& key) const {
        if (!contains(key)) {
            std::cerr << "No such key: " << key << std::endl;
            std::abort();
        }
    }

    template <class T>
    T get(std::string) {}

    template <class T>
    T get(std::string, T value) {
        return value;
    }
};

template <>
bool parameter::get<bool>(std::string key, bool value) {
    if (!contains(key)) {
        return value;
    }
    if (iequals(params[key], "yes") || iequals(params[key], "true") ||
        iequals(params[key], "1")) {
        // (std::stoi(params[key]) == 1)
        return true;
    } else {
        return false;
    }
}

template <>
bool parameter::get(std::string key) {
    check_key(key);
    return get<bool>(key, false);
}

template <>
int parameter::get(std::string key, int value) {
    if (!contains(key)) {
        return value;
    }
    return std::stoi(params[key]);
}

template <>
int parameter::get(std::string key) {
    check_key(key);
    return get<int>(key, 0);
}

template <>
double parameter::get(std::string key, double value) {
    if (!contains(key)) {
        return value;
    }
    return std::stod(params[key]);
}

template <>
double parameter::get(std::string key) {
    check_key(key);
    return get<double>(key, 0.0);
}

template <>
std::string parameter::get(std::string key, std::string value) {
    if (!contains(key)) {
        return value;
    }
    return params[key];
}

template <>
std::string parameter::get(std::string key) {
    check_key(key);
    return get<std::string>(key, "");
}

// template <>
// char *parameter::get(std::string key, char *value)
// {
//     if (!contains(key))
//     {
//         return value;
//     }
//     return params[key].c_str();
// }

// template <>
// char *parameter::get(std::string key)
// {
//     check_key(key);
//     return get<char *>(key, " ");
// }

}  // namespace param
