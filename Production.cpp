//
// Created by Oana on 12/10/2023.
//

#include "Production.h"
#include "Utils.h"

Production::Production(std::string value) {
    this->terms = Utils::splitString(value, ' ');
}

bool Production::operator==(const Production &rhs) const {
    bool value = terms == rhs.terms &&
                 pointIndex == rhs.pointIndex;
    return value;
}

bool Production::operator!=(const Production &rhs) const {
    return !(rhs == *this);
}

std::string Production::toString() const {
    std::string prod = "";
    for (const auto &item: this->terms) {
        prod += item + " ";
    }
    return prod;
}

std::string Production::getPointValue() const {
    return this->terms[this->pointIndex];
}

void Production::incrementPoint() {
    if (!isPointAtEnd())
        pointIndex++;
}

bool Production::isPointAtEnd() const {
    return pointIndex == terms.size();
}

Production::Production(const Production &production) {
    this->terms = production.terms;
    this->pointIndex = production.pointIndex;
}

const std::vector<std::string> &Production::getTerms() const {
    return terms;
}

std::ostream &operator<<(std::ostream &os, const Production &production) {
    for (int i = 0; i < production.terms.size(); i++) {
        if (production.pointIndex == i)
            os << ".";
        os << production.terms[i];
    }
    if (production.isPointAtEnd())
        os << ".";
    return os;
}
