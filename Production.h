//
// Created by Oana on 12/10/2023.
//

#ifndef LFTC_TEAM_PRODUCTION_H
#define LFTC_TEAM_PRODUCTION_H


#include <vector>
#include <string>


class Production {
    std::vector<std::string> terms;
    int pointIndex = 0;
public:

    Production(){}

    Production(std::string value);

    const std::vector<std::string> &getTerms() const;

    Production(const Production& production);

    bool operator==(const Production &rhs) const;

    bool operator!=(const Production &rhs) const;

    std::string toString() const;

    std::string getPointValue() const;

    void incrementPoint();

    bool isPointAtEnd() const;


};


#endif //LFTC_TEAM_PRODUCTION_H
