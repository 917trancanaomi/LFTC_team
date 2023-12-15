//
// Created by Naomi on 12/15/2023.
//
#include "State.h"

State::State(const std::set<Item>& items) : items(items) {}

std::set<std::string> State::getSymbolsAfterTheDot() const {
    std::set<std::string> symbols;

    for (const auto& i : items) {
        if (!i.isComplete())
            symbols.insert(i.rhs[i.dotPosition]);
    }

    return symbols;
}

bool State::operator==(const State& other) const {
    return items == other.items;
}