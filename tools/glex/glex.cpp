#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "DFA.h"
#include "RegexReader.h"

void gen_code(FILE* cfile, FILE* hfile, Graph& g, std::vector<std::string> tokens)
{
    // code template
    constexpr auto code_head = R"(/**
* @file glex_gencode.cc
* @author generate by lgg-lex
* @brief 自动生成的lex程序
* @version 0.1
* @date 2021-10-14
* 
* @copyright Copyright (c) 2021
* 
*/

#include <stdio.h>
#include <assert.h>
#include <string>
#include <string_view>
#include "glex_gencode.h"

/**
 * @brief 状态转移函数
 * 
 * @param state 输入当前状态, 输出下一状态
 * @param c 转移字符
 * @param accept 接受等级 -1: 不接受; 0,1,2...: 接受等级(0级最优先)
 * @return int  -1: 无转移; -2: 未知状态; 0: 进入下一状态;
 */
int glex::glex_step(int* state, int c, int* accept){
switch (*state){)";
    constexpr auto state_case = R"(
case %d:
    switch (c){)";
    constexpr auto char_case = R"(
    case %d: *state = %d; *accept = %s; break;)";
    constexpr auto char_default = R"(
    default: return -1;
    } break;)";
    constexpr auto state_default = R"(
default: return -2;
}
return 0;
}

int glex::next_match() 
{
    match.clear();
    int state = 0;
    int accept;
    int c;
    int level = 0;      // 当前匹配最高等级的模式
    int level_off = 0;  // 对应读取字符数
    int cur_off = 0;

    fseek(file, fileoff, SEEK_SET);
    if((c = fgetc(file)) == EOF){
        return -1; // EOF退出
    };
    for(;;){
        ++cur_off;
        int step_r = glex_step(&state, (int)c, &accept);
        // step_r == 0:     合法转移 
        // step_r == -1:    非法转移
        // step_r == -2:    理论上不存在
        if (step_r == 0){
            if (accept >= level){
                level = accept;
                level_off = cur_off;
            }
            match.push_back(c);
            if((c = fgetc(file)) == EOF){
                break; // EOF退出
            };
        }else{
            assert(step_r == -1);
            break; // 非法转移
        }
    }
    if (level == 0){
        // 全部不能匹配则至少跳过一个字符
        if (match.size() == 0) {
            match.push_back(c);
        }
        // 跳过不能匹配的字符
        fileoff += match.size();
        return -2;
    }
    fileoff += level_off;
    return level;
}
)";
    fprintf(cfile, code_head);
    for(int n = 0; n < g.head.size(); ++n){
        fprintf(cfile, state_case, n);
        g.visit_edge_node(n, [&](Graph::edge_t& e){
            fprintf(cfile, char_case, (int)e.c, e.to, 
                g.accept_level[e.to] == 0 ? "NONE" : tokens[tokens.size() - g.accept_level[e.to]].data());
        });
        fprintf(cfile, char_default);
    }
    fprintf(cfile, state_default);

    constexpr auto header_head = R"(/**
 * @file glex_gencode.h
 * @author generate by lgg-lex
 * @brief 自动生成的lex程序
 * @version 0.1
 * @date 2021-10-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <string>
#include <string_view>

/**
 * @brief glex类
 * 
 */
class glex
{
    FILE* file;
    long fileoff = 0l;
    std::string match;
public:
    enum Token{
        NONE = 0,)";
    constexpr auto header_enum = R"(
        %s = %d,)";
    constexpr auto header_class = R"(
    };

    glex(FILE* file_) : file(file_) { };

    /**
     * @brief 状态转移函数
     * 
     * @param state 输入当前状态, 输出下一状态
     * @param c 转移字符
     * @param accept 接受等级 -1: 不接受; 0,1,2...: 接受等级(0级最优先)
     * @return int  -1: 无转移; -2: 未知状态; 0: 进入下一状态;
     */
    static int glex_step(int* state, int c, int* accept);

    /**
     * @brief 获得上一次调用next_match()匹配的字符串
     * 
     * @return const std::string_view 
     */
    const std::string_view get_match() { return match; }

    /**
     * @brief 调用该函数获取下一个匹配, 至少匹配一个字符
     * 
     * @return int  -1: EOF; 
     *              -2: No Match Input, skip longest valid prefix
     */
    int next_match();
};
)";
    fprintf(hfile, header_head);
    for(int i = tokens.size() - 1; i >= 0; --i){
        fprintf(hfile, header_enum, tokens[i].data() , (int)tokens.size() - i);
    }
    fprintf(hfile, header_class);
}

int main(int argc, char** argv)
{
    if(argc != 2){
        printf("usage ./glex [rulefile]\n");
        return -1;
    }
    auto ifs = std::ifstream{argv[1]};
    auto r = RegexReader(ifs);

    auto n = NFA(r.rules);
    n.print();
    printf("\n\n");

    auto d = DFA(n);
    d.print();
    printf("\n\n"); 
    
    FILE* cf = fopen("glex_gencode.cc", "w");
    FILE* hf = fopen("glex_gencode.h", "w");
    gen_code(cf, hf, d.g, r.tokens);
    fclose(cf);
    fclose(hf);
    return 0;
}