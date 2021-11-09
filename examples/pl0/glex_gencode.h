/**
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
        NONE = 0,
        BLANK = 1,
        IDENT = 2,
        NUMBER = 3,
        COMMA = 4,
        SEMI = 5,
        ASSIGN = 6,
        EQ = 7,
        RP = 8,
        LP = 9,
        DIV = 10,
        MUL = 11,
        SUB = 12,
        PLUS = 13,
        WRITE = 14,
        READ = 15,
        CALL = 16,
        THEN = 17,
        IF = 18,
        DO = 19,
        WHILE = 20,
        END = 21,
        BEGIN = 22,
        PROC = 23,
        VAR = 24,
        CONST = 25,
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
