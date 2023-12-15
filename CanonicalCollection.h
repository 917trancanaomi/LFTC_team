//
// Created by Naomi on 12/15/2023.
//
// CanonicalCollection.h
#ifndef LFTC_TEAM_CANONICALCOLLECTION_H
#define LFTC_TEAM_CANONICALCOLLECTION_H

#include <vector>
#include <map>
#include <string>
#include "Production.h"

class CanonicalCollection {
public:
    void addState(const std::map<std::string, std::vector<Production>>& state);
    const std::vector<std::map<std::string, std::vector<Production>>>& getStates() const;

    bool stateExists(const std::map<std::string, std::vector<Production>>& state);

    std::vector<std::map<std::string, std::vector<Production>>> states;
};

#endif //LFTC_TEAM_CANONICALCOLLECTION_H
