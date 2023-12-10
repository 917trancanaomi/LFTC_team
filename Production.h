//
// Created by Oana on 12/10/2023.
//

#ifndef LFTC_TEAM_PRODUCTION_H
#define LFTC_TEAM_PRODUCTION_H


#include <vector>
#include <string>


class Production {
public:
    std::vector<std::string> terms;
    int pointIndex = 0;

    Production(){}

    Production(std::string value);

    bool operator==(const Production &rhs) const;

    bool operator!=(const Production &rhs) const;

    std::string toString() const;

    std::string getPointValue() const;


};


#endif //LFTC_TEAM_PRODUCTION_H
