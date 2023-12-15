//
// Created by Naomi on 12/15/2023.
//

// CanonicalCollection.cpp
#include <algorithm>
#include "CanonicalCollection.h"

void CanonicalCollection::addState(const std::map<std::string, std::vector<Production>> &state) {
    states.push_back(state);
}

const std::vector<std::map<std::string, std::vector<Production>>> &CanonicalCollection::getStates() const {
    return states;
}

bool CanonicalCollection::stateExists(const std::map<std::string, std::vector<Production>> &state) {
    for (const auto &item: this->states) {
        if (item == state) {
            return true;
        }
    }
    return false;
}
