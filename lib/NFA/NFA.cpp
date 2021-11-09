#include "NFA.h"

NFA::NFA(std::vector<std::string> regexs_) : regexs(regexs_)
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
        g.set_level(node_cnt, regexs.size() - rank);
    }
    for(int i : each_re_start){
        g.add_edge(this->start_node, i, g.EPSILON);
    }
}

void NFA::print()
{
    this->g.print();
}