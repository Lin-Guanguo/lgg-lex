#include "DFA.h"

std::size_t DFA::NodeSetHash::operator()(const NodeSet& s) const noexcept
{
    std::size_t res = 0;
    for (auto i : s)
        res ^= ((i >> 16) ^ i) * 0x45d9f3b;
    return res;
}

DFA::NodeSet DFA::epsilon_closure(int n0, int* highest_level)
{
    *highest_level = 0;
    NodeSet search;
    std::stack<int> no_search;
    no_search.push(n0);
    while (!no_search.empty()) {
        int n = no_search.top(); no_search.pop();
        if (search.find(n) == search.end()) {
            search.insert(n);
            auto r = this->nfa.g.get_level(n);
            *highest_level = std::max(*highest_level, r);
            nfa.g.visit_edge_node_c(n, Graph::EPSILON, [&](Graph::edge_t& e) {
                no_search.push(e.to);
                });
        }
    }
    return search;
}

DFA::NodeSet DFA::epsilon_closure_delta(NodeSet& closure, int c, int* highest_level)
{
    *highest_level = -1;
    NodeSet search;
    std::stack<int> no_search;
    // c转移一步
    for (int n : closure) {
        nfa.g.visit_edge_node_c(n, c, [&](Graph::edge_t& e) {
            no_search.push(e.to);
            });
    }

    // Epsilon转移
    while (!no_search.empty()) {
        int n = no_search.top(); no_search.pop();
        if (search.find(n) == search.end()) {
            search.insert(n);
            auto r = this->nfa.g.get_level(n);
            *highest_level = std::max(*highest_level, r);
            nfa.g.visit_edge_node_c(n, Graph::EPSILON, [&](Graph::edge_t& e) {
                no_search.push(e.to);
                });
        }
    }
    return search;
}

DFA::DFA(NFA nfa_) : nfa(nfa_)
{
    int level;
    int node_cnt = 0;
    auto q = epsilon_closure(0, &level);
    node_group.emplace(q, node_cnt);
    g.set_level(node_cnt, level);
    node_cnt++;

    std::stack<NodeSet> work_list;
    work_list.push(q);
    while (!work_list.empty()) {
        q = work_list.top(); work_list.pop();
        int from = node_group[q];
        for (int c = 0; c < 255; ++c) {
            auto t = epsilon_closure_delta(q, c, &level);
            if (t.empty()) 
                continue;
            int to;
            if (node_group.find(t) == node_group.end()) {
                node_group.emplace(t, node_cnt);
                work_list.push(t);
                to = node_cnt;
                g.set_level(node_cnt, level);
                node_cnt++;
            }
            else {
                to = node_group.find(t)->second;
            }
            this->g.add_edge(from, to, c);
        }
    }
}

void DFA::print()
{
    this->g.print();
}