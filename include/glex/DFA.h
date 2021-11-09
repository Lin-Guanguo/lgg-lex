#pragma once

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include "Graph.h"
#include "NFA.h"

/**
 * @brief NFA -> DFA
 *
 */
class DFA
{
public:
    using NodeSet = std::unordered_set<int>;

    NFA nfa;
    Graph g;

    struct NodeSetHash
    {
        std::size_t operator()(const NodeSet& s) const noexcept;
    };

    /**
     * @brief NFA中的点集 -> DFA中的点
     */
    std::unordered_map<NodeSet, int, NodeSetHash> node_group;

    int start_node = 0;

    /**
     * @brief 从n0出发的epsilon闭包
     *
     * @param n0 出发点
     * @param highest_level 转移后闭包中level最高的点
     * @return NodeSet epsilon闭包包含的点
     */
    NodeSet epsilon_closure(int n0, int* highest_level);

    /**
     * @brief 从n0出发经过c转移后的epsilon闭包
     * 
     * @param closure epsilon闭包包含的点
     * @param c 转移输入
     * @param highest_level 转移后闭包中level最高的点
     * @return NodeSet 转移后的epsilon闭包包含的点
     */
    NodeSet epsilon_closure_delta(NodeSet& closure, int c, int* highest_level);

    DFA(NFA nfa_);

    void print();
};
