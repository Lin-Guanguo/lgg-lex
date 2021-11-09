#pragma once

#include <vector>
#include <string>
#include <iostream>

class RegexReader
{
public:
    std::vector<std::string> tokens;
    std::vector<std::string> rules;

    RegexReader(std::istream& in);
};