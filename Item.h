//
// Created by Naomi on 12/15/2023.
//

#ifndef LFTC_TEAM_ITEM_H
#define LFTC_TEAM_ITEM_H

#include <string>
#include <vector>

class Item {
public:
    std::string lhs;
    std::vector<std::string> rhs;
    int dotPosition;

    Item(std::string lhs, std::vector<std::string> rhs, int dotPosition);

    bool operator==(const Item& other) const;

    bool operator<(const Item& other) const;

    bool isComplete() const;
};

#endif //LFTC_TEAM_ITEM_H
