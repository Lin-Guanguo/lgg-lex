#include <cstdio>
#include "Graph.h"

void Graph::add_edge(int start, int to, char c)
{
    if (head.size() <= std::max(start, to)) {
        head.resize(std::max(start, to) + 1, -1);
        accept_level.resize(std::max(start, to) + 1, 0);
    }
    edges.push_back({ head[start], to, c });
    head[start] = edges.size() - 1;
}

/**
 * @brief 获得点的level
 * 
 * @param i 点序号
 * @return int level
 */
int Graph::get_level(int i)
{
    if(head.size() <= i){
        head.resize(i + 1, -1);
        accept_level.resize(i + 1, 0);
    }
    return accept_level[i];
}

/**
 * @brief 设置点的接受level
 * 
 * @param i 点序号
 * @param r level
 */
void Graph::set_level(int i, int r)
{
    if(head.size() <= i){
        head.resize(i + 1, -1);
        accept_level.resize(i + 1, 0);
    }
    accept_level[i] = r;
}

/**
 * @brief 命令行打印图
 *
 */
void Graph::print()
{
    this->visit_all_edge([this](int i, edge_t& e) {
        printf("%d --[%c]-->%d: %d\n", i, e.c == -1 ? '#' : e.c, e.to, this->accept_level[e.to]);
    });
}