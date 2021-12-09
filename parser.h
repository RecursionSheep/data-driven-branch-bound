#pragma once

#include <iostream>
#include <fstream>

#include "milp.h"

class MilpParser {
public:
    MilpParser();
    ~MilpParser();
    MilpInstance* parse(std::istream& in);
};
