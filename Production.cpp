//
// Created by Oana on 12/10/2023.
//

#include "Production.h"
#include "Utils.h"

Production::Production(std::string value) {
    this->terms = Utils::splitString(value, ' ');
}

bool Production::operator==(const Production &rhs) const {
    return terms == rhs.terms &&
           pointIndex == rhs.pointIndex;
}

bool Production::operator!=(const Production &rhs) const {
    return !(rhs == *this);
}

std::string Production::toString() const {
    std::string prod = "";
    for (const auto &item: this->terms){
        prod += item + " ";
    }
    return prod;
}

std::string Production::getPointValue() const {
    return this->terms[this->pointIndex];
}
