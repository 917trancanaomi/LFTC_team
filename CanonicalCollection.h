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
    std::vector<std::map<std::string, std::vector<Production>>> states;

    CanonicalCollection();

    CanonicalCollection(const CanonicalCollection &collection);

    void addState(const std::map<std::string, std::vector<Production>> &state);

    const std::vector<std::map<std::string, std::vector<Production>>> &getStates() const;

    bool stateExists(const std::map<std::string, std::vector<Production>> &state);

    CanonicalCollection &operator=(const CanonicalCollection &rhs);

};

#endif //LFTC_TEAM_CANONICALCOLLECTION_H
