//
// Created by Oana on 12/16/2023.
//

#ifndef LFTC_TEAM_PARSEOUTPUT_H
#define LFTC_TEAM_PARSEOUTPUT_H

#include <string>
#include <vector>
#include <ostream>

struct Element {
    std::string info;
    int parent;
    int rightSibling;
};

class ParseOutput {
public:
    friend std::ostream &operator<<(std::ostream &os, const ParseOutput &output);

public:
    std::vector<Element> table;


};

std::ostream &operator<<(std::ostream &os, const ParseOutput &output) {
    os << "Parent-sibling table: \n";
    os << " INDEX  " << " | " << "  INFO  " << " | " << " PARENT " << " | " << "RIGHT SIBLING\n";
    for (int i = 0; i < output.table.size(); i++) {
        Element el = output.table[i];
        os << i << "         | " << el.info << "         | " << el.parent << "         | " << el.rightSibling << "\n";
    }
    return os;
}


#endif //LFTC_TEAM_PARSEOUTPUT_H
