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

CanonicalCollection::CanonicalCollection(const CanonicalCollection &collection) {
    this->states.clear();
    std::for_each(collection.states.begin(), collection.states.end(), [this](auto a) { this->states.push_back(a); });
}

CanonicalCollection::CanonicalCollection() {
    this->states.clear();
}

CanonicalCollection& CanonicalCollection::operator=(const CanonicalCollection &rhs) {
    this->states.clear();
    std::for_each(rhs.states.begin(), rhs.states.end(), [this](auto a) { this->states.push_back(a); });
    return *this;
}
