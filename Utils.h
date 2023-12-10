//
// Created by Oana on 12/10/2023.
//

#ifndef LFTC_TEAM_UTILS_H
#define LFTC_TEAM_UTILS_H

#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <iostream>

class Utils {

public:
    static std::vector<std::string> splitString(const std::string &str, char delimiter);

    static std::set<std::string> splitStringToSet(const std::string &str, char delimiter);

    static std::string trim(const std::string &str);

    static void printSet(const std::set<std::string> &s);
};


#endif //LFTC_TEAM_UTILS_H
