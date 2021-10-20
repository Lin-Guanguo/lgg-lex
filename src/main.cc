#include <stdio.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <stack>


using node_set = std::unordered_set<int>;
using node_map = std::unordered_map<int,int>;

/**
 * @brief NFA DFA用的图
 * 链式前向星存储
 */
class graph_t
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
     * @brief 每个点的接受rank，0为最高，-1为不接受
     * 
     */
    std::vector<int> accept_rank;    
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
    void add_edge(int start, int to, char c)
    {
        if (head.size() <= std::max(start, to)) {
            head.resize(std::max(start, to) + 1, -1);
            accept_rank.resize(std::max(start, to) + 1, -1);
        }
        edges.push_back({ head[start], to, c });
        head[start] = edges.size() - 1;
    }
    
    /**
     * @brief 获得点的rank
     * 
     * @param i 点序号
     * @return int rank
     */
    int get_rank(int i)
    {
        if(head.size() <= i){
            head.resize(i + 1, -1);
            accept_rank.resize(i + 1, -1);
        }
        return accept_rank[i];
    }

    /**
     * @brief 设置点的接受rank
     * 
     * @param i 点序号
     * @param r rank
     */
    void set_rank(int i, int r)
    {
        if(head.size() <= i){
            head.resize(i + 1, -1);
            accept_rank.resize(i + 1, -1);
        }
        accept_rank[i] = r;
    }

    /**
     * @brief 命令行打印图
     *
     */
    void print()
    {
        this->visit_all_edge([this](int i, edge_t& e) {
            printf("%d --[%c]-->%d: %d\n", i, e.c == -1 ? '#' : e.c, e.to, this->accept_rank[e.to]);
        });
    }
};

/**
 * @brief RE -> NFA
 *
 */
class nfa_t
{
public:
    std::vector<std::string> regexs;

    graph_t g;
    int start_node = 0;

    nfa_t(std::vector<std::string> regexs_) : regexs(regexs_)
    {
        std::stack<std::pair<int, char>> stack;
        std::vector<int> each_re_start;
        int node_cnt = 0;
        for(int rank = 0; rank < regexs.size(); ++rank){
            node_cnt++;
            each_re_start.push_back(node_cnt);
            auto& re = regexs[rank];
            int lp = 0;
            for (int i = -1; i <= (int)re.size(); ++i) {
                char c;
                // 简化编程实现，整体句子在()中
                if (i == -1)
                    c = '(';
                else if (i == re.size())
                    c = ')';
                else
                    c = re[i];

                if (c == '(') {
                    // 进入括号范围，入栈
                    stack.push({ node_cnt, c });
                }
                else if (c == '|') {
                    // |，入栈，并切断与前序的连接(node_cnt++)
                    stack.push({ node_cnt, c });
                    node_cnt++;
                }
                else if (c == ')') {
                    // 开始出栈, 清算括号和其中的|
                    std::vector<int> ors;
                    auto top = stack.top(); stack.pop();
                    while (top.second == '|') {
                        ors.push_back(top.first);
                        top = stack.top(); stack.pop();
                    }
                    lp = top.first;  // 处理 ( )*
                    for (int or_ : ors) {
                        // 左括号指向每个|后一个字符，每个|指向结尾
                        g.add_edge(lp, or_ + 1, g.EPSILON);
                        g.add_edge(or_, node_cnt, g.EPSILON);
                    }
                }
                else if (c == '*') {
                    g.add_edge(lp, node_cnt, g.EPSILON); // 跳过
                    g.add_edge(node_cnt, lp, g.EPSILON); // Loop
                    g.add_edge(node_cnt, node_cnt + 1, g.EPSILON);
                    node_cnt++;
                }
                else {
                    if (c == '\\'){
                        ++i;
                        c = re[i];
                    }
                    g.add_edge(node_cnt, node_cnt + 1, c);  // 正常推进
                    lp = node_cnt;  // 处理 c*
                    node_cnt++;
                }
            }
            g.set_rank(node_cnt, rank);
        }
        for(int i : each_re_start){
            g.add_edge(this->start_node, i, g.EPSILON);
        }
    }

    void print()
    {
        this->g.print();
    }
};

/**
 * @brief NFA -> DFA
 *
 */
class dfa_t
{
public:
    nfa_t nfa;
    graph_t g;

    struct set_hash
    {
        std::size_t operator()(const node_set& s) const noexcept
        {
            std::size_t res = 0;
            for (auto i : s)
                res ^= ((i >> 16) ^ i) * 0x45d9f3b;
            return res;
        }
    };

    /**
     * @brief NFA中的点集 -> DFA中的点
     * 
     */
    std::unordered_map<node_set, int, set_hash> node_group;

    int start_node = 0;

    /**
     * @brief 从n0出发的epsilon闭包
     *
     * @param n0 出发点
     * @param highest_rank 转移后闭包中rank最高的点
     * @return node_set epsilon闭包包含的点
     */
    node_set epsilon_closure(int n0, int* highest_rank)
    {
        *highest_rank = -1;
        node_set search;
        std::stack<int> no_search;
        no_search.push(n0);
        while (!no_search.empty()) {
            int n = no_search.top(); no_search.pop();
            if (search.find(n) == search.end()) {
                search.insert(n);
                auto r = this->nfa.g.get_rank(n);
                if( r != -1) {
                    if (*highest_rank == -1)
                        *highest_rank = r;
                    else
                        *highest_rank = std::min(*highest_rank, r);
                }
                nfa.g.visit_edge_node_c(n, graph_t::EPSILON, [&](graph_t::edge_t& e) {
                    no_search.push(e.to);
                    });
            }
        }
        return search;
    }

    /**
     * @brief 从n0出发经过c转移后的epsilon闭包
     * 
     * @param closure epsilon闭包包含的点
     * @param c 转移输入
     * @param highest_rank 转移后闭包中rank最高的点
     * @return node_set 转移后的epsilon闭包包含的点
     */
    node_set epsilon_closure_delta(node_set& closure, int c, int* highest_rank)
    {
        *highest_rank = -1;
        node_set search;
        std::stack<int> no_search;
        // c转移一步
        for (int n : closure) {
            nfa.g.visit_edge_node_c(n, c, [&](graph_t::edge_t& e) {
                no_search.push(e.to);
                });
        }

        // Epsilon转移
        while (!no_search.empty()) {
            int n = no_search.top(); no_search.pop();
            if (search.find(n) == search.end()) {
                search.insert(n);
                auto r = this->nfa.g.get_rank(n);
                if( r != -1){
                    if (*highest_rank == -1)
                        *highest_rank = r;
                    else
                        *highest_rank = std::min(*highest_rank, r);
                }
                nfa.g.visit_edge_node_c(n, graph_t::EPSILON, [&](graph_t::edge_t& e) {
                    no_search.push(e.to);
                    });
            }
        }

        return search;
    }

    dfa_t(nfa_t nfa_) : nfa(nfa_)
    {
        int rank;
        int node_cnt = 0;
        auto q = epsilon_closure(0, &rank);
        node_group.emplace(q, node_cnt);
        g.set_rank(node_cnt, rank);
        node_cnt++;

        std::stack<node_set> work_list;
        work_list.push(q);
        while (!work_list.empty()) {
            q = work_list.top(); work_list.pop();
            int from = node_group[q];
            for (int c = 0; c < 255; ++c) {
                auto t = epsilon_closure_delta(q, c, &rank);
                if (t.empty()) 
                    continue;
                int to;
                if (node_group.find(t) == node_group.end()) {
                    node_group.emplace(t, node_cnt);
                    work_list.push(t);
                    to = node_cnt;
                    g.set_rank(node_cnt, rank);
                    node_cnt++;
                }
                else {
                    to = node_group.find(t)->second;
                }
                this->g.add_edge(from, to, c);
            }
        }
    }

    void print()
    {
        this->g.print();
    }

    void gen_code(FILE* file)
    {
        // code template
        constexpr auto code_head = R"(/**
 * @file %s
 * @author generate by lgg-lex
 * @brief 自动生成的lex程序
 * @version 0.1
 * @date 2021-10-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

/**
 * @brief 状态转移函数
 * 
 * @param state 输入当前状态, 输出下一状态
 * @param c 转移字符
 * @param accept 接受等级 -1: 不接受; 0,1,2...: 接受等级(0级最优先)
 * @return int  -1: 无转移; -2: 未知状态; 0: 进入下一状态;
 */
int lgg_lex_step(int* state, int c, int* accept){
    switch (*state){)";
        constexpr auto state_case = R"(
    case %d:
        switch (c){)";
        constexpr auto char_case = R"(
        case %d: *state = %d; *accept = %d; break;)";
        constexpr auto char_default = R"(
        default: return -1;
        } break;)";
        constexpr auto state_default = R"(
    default: return -2;
    }
    return 0;
})";

        fprintf(file, code_head, "gen_code.c");
        for(int n = 0; n < g.head.size(); ++n){
            fprintf(file, state_case, n);
            g.visit_edge_node(n, [&](graph_t::edge_t& e){
                fprintf(file, char_case, (int)e.c, e.to, this->g.accept_rank[e.to]);
            });
            fprintf(file, char_default);
        }
        fprintf(file, state_default);
    }
};

void test_dfa()
{
    {
        auto n = nfa_t({
            {"\\(ab*\\)"}, {"1235"}, {"h"}
            });
        n.print();
        printf("\n\n");
        auto d = dfa_t(n);
        d.print();
        printf("\n\n"); 
        
        FILE* f = fopen("gen_code.c", "w");
        d.gen_code(f);
        fclose(f);
    }
}

int main()
{
    test_dfa();
}