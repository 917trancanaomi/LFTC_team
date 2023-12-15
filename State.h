//
// Created by Naomi on 12/15/2023.
//

#ifndef LFTC_TEAM_STATE_H
#define LFTC_TEAM_STATE_H

#include "Item.h"
#include <set>

class State {
public:
    std::set<Item> items;

    State(const std::set<Item>& items);

    std::set<std::string> getSymbolsAfterTheDot() const;

    bool operator==(const State& other) const;
};

#endif //LFTC_TEAM_STATE_H
