/**
 * @file gen_code.c
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
 * @param accept 接受等级 -1代表不接受
 * @return int  -1: 无转移; -2: 未知状态; 0: 进入下一状态;
 */
int lgg_lex_step(int* state, int c, int* accept){
    int accept = 0;
    switch (*state){
    case 0:
        switch (c){
        case 40: *state = 1; *accept = 0; break;
        default: return -1;
        } break;
    case 1:
        switch (c){
        case 97: *state = 2; *accept = 0; break;
        default: return -1;
        } break;
    case 2:
        switch (c){
        case 98: *state = 2; *accept = 0; break;
        case 41: *state = 3; *accept = 1; break;
        default: return -1;
        } break;
    case 3:
        switch (c){
        default: return -1;
        } break;
    default: return -2;
    }
    return 0;
}