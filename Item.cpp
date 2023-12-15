//
// Created by Naomi on 12/15/2023.
//

#include "Item.h"

Item::Item(std::string lhs, std::vector<std::string> rhs, int dotPosition)
        : lhs(std::move(lhs)), rhs(std::move(rhs)), dotPosition(dotPosition) {}

bool Item::operator==(const Item& other) const {
    return lhs == other.lhs && rhs == other.rhs && dotPosition == other.dotPosition;
}

bool Item::operator<(const Item& other) const {
    return lhs < other.lhs || (lhs == other.lhs && rhs < other.rhs) ||
           (lhs == other.lhs && rhs == other.rhs && dotPosition < other.dotPosition);
}

bool Item::isComplete() const {
    return dotPosition == rhs.size();
}

