#pragma once

#include <vector>

/**
 * @brief NFA DFA用的图
 * 链式前向星存储
 */
class Graph
{
public:
    static constexpr char EPSILON = -1;
    struct edge_t
    {
        int next;   /**< @brief 下一条同起点的边 */
        int to;     /**< @brief 边终点 */
        char c;     /**< @brief 转换字母 EPSILON代表epsilon */
    };
    std::vector<edge_t> edges;    /**< @brief 链式前向星 */
    std::vector<int> head;     /**< @brief 链式前向星 */

    /**
     * @brief 每个点的接受level，0为不接受，越高接受优先级越高
     */
    std::vector<int> accept_level;    
public:
    /**
     * @brief 遍历一个起点出发的边
     *
     * @tparam F 遍历函数类型 (edge s)
     * @param n 边的起始点
     * @param f 遍历函数
     */
    template<typename F>
    void visit_edge_node(int n, F f)
    {
        int s = head[n];
        while (s != -1) {
            f(edges[s]);
            s = this->edges[s].next;
        }
    }

    /**
     * @brief 遍历一个起点出发的边, 满足转移输入为 c
     *
     * @tparam F F 遍历函数类型 (edge s))
     * @param n 边的起始点
     * @param c 转移输入
     * @param f 遍历函数
     */
    template<typename F>
    void visit_edge_node_c(int n, char c, F f)
    {
        int s = head[n];
        while (s != -1) {
            if (edges[s].c == c)
                f(edges[s]);
            s = this->edges[s].next;
        }
    }

    /**
     * @brief 遍历所有边
     *
     * @tparam F 遍历函数类型 (int n, edge s)
     * @param f 遍历函数
     */
    template<typename F>
    void visit_all_edge(F f)
    {
        for (int i = 0; i < head.size(); ++i) {
            int s = head[i];
            while (s != -1) {
                f(i, edges[s]);
                s = this->edges[s].next;
            }
        }
    }

    /**
     * @brief 添加边
     *
     * @param start 起点
     * @param to 终点
     * @param c 边值，转移字符
     */
    void add_edge(int start, int to, char c);
    
    /**
     * @brief 获得点的level
     * 
     * @param i 点序号
     * @return int level
     */
    int get_level(int i);

    /**
     * @brief 设置点的接受level
     * 
     * @param i 点序号
     * @param r level
     */
    void set_level(int i, int r);

    /**
     * @brief 命令行打印图
     *
     */
    void print();
};