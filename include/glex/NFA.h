#pragma once

#include <vector>
#include <stack>
#include <string>
#include "Graph.h"

class NFA
{
public:
    std::vector<std::string> regexs;

    Graph g;
    int start_node = 0;

    NFA(std::vector<std::string> regexs_);

    void print();
};