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
 * @param accept 接受等级 -1: 不接受; 0,1,2...: 接受等级(0级最优先)
 * @return int  -1: 无转移; -2: 未知状态; 0: 进入下一状态;
 */
inline int glex_step(int* state, int c, int* accept){
    switch (*state){
    case 0:
        switch (c){
        case 119: *state = 16; *accept = 0; break;
        case 118: *state = 15; *accept = 0; break;
        case 105: *state = 14; *accept = 0; break;
        case 61: *state = 13; *accept = 3; break;
        case 57: *state = 12; *accept = 2; break;
        case 56: *state = 11; *accept = 2; break;
        case 55: *state = 10; *accept = 2; break;
        case 54: *state = 9; *accept = 2; break;
        case 53: *state = 8; *accept = 2; break;
        case 52: *state = 7; *accept = 2; break;
        case 51: *state = 6; *accept = 2; break;
        case 50: *state = 5; *accept = 2; break;
        case 49: *state = 4; *accept = 2; break;
        case 32: *state = 3; *accept = 1; break;
        case 10: *state = 2; *accept = 1; break;
        case 9: *state = 1; *accept = 1; break;
        default: return -1;
        } break;
    case 1:
        switch (c){
        default: return -1;
        } break;
    case 2:
        switch (c){
        default: return -1;
        } break;
    case 3:
        switch (c){
        default: return -1;
        } break;
    case 4:
        switch (c){
        case 57: *state = 12; *accept = 2; break;
        case 56: *state = 32; *accept = 2; break;
        case 55: *state = 31; *accept = 2; break;
        case 54: *state = 30; *accept = 2; break;
        case 53: *state = 29; *accept = 2; break;
        case 52: *state = 28; *accept = 2; break;
        case 51: *state = 27; *accept = 2; break;
        case 50: *state = 26; *accept = 2; break;
        case 49: *state = 25; *accept = 2; break;
        case 48: *state = 24; *accept = 2; break;
        default: return -1;
        } break;
    case 5:
        switch (c){
        case 57: *state = 12; *accept = 2; break;
        case 56: *state = 32; *accept = 2; break;
        case 55: *state = 31; *accept = 2; break;
        case 54: *state = 30; *accept = 2; break;
        case 53: *state = 29; *accept = 2; break;
        case 52: *state = 28; *accept = 2; break;
        case 51: *state = 27; *accept = 2; break;
        case 50: *state = 26; *accept = 2; break;
        case 49: *state = 25; *accept = 2; break;
        case 48: *state = 24; *accept = 2; break;
        default: return -1;
        } break;
    case 6:
        switch (c){
        case 57: *state = 12; *accept = 2; break;
        case 56: *state = 32; *accept = 2; break;
        case 55: *state = 31; *accept = 2; break;
        case 54: *state = 30; *accept = 2; break;
        case 53: *state = 29; *accept = 2; break;
        case 52: *state = 28; *accept = 2; break;
        case 51: *state = 27; *accept = 2; break;
        case 50: *state = 26; *accept = 2; break;
        case 49: *state = 25; *accept = 2; break;
        case 48: *state = 24; *accept = 2; break;
        default: return -1;
        } break;
    case 7:
        switch (c){
        case 57: *state = 12; *accept = 2; break;
        case 56: *state = 32; *accept = 2; break;
        case 55: *state = 31; *accept = 2; break;
        case 54: *state = 30; *accept = 2; break;
        case 53: *state = 29; *accept = 2; break;
        case 52: *state = 28; *accept = 2; break;
        case 51: *state = 27; *accept = 2; break;
        case 50: *state = 26; *accept = 2; break;
        case 49: *state = 25; *accept = 2; break;
        case 48: *state = 24; *accept = 2; break;
        default: return -1;
        } break;
    case 8:
        switch (c){
        case 57: *state = 12; *accept = 2; break;
        case 56: *state = 32; *accept = 2; break;
        case 55: *state = 31; *accept = 2; break;
        case 54: *state = 30; *accept = 2; break;
        case 53: *state = 29; *accept = 2; break;
        case 52: *state = 28; *accept = 2; break;
        case 51: *state = 27; *accept = 2; break;
        case 50: *state = 26; *accept = 2; break;
        case 49: *state = 25; *accept = 2; break;
        case 48: *state = 24; *accept = 2; break;
        default: return -1;
        } break;
    case 9:
        switch (c){
        case 57: *state = 12; *accept = 2; break;
        case 56: *state = 32; *accept = 2; break;
        case 55: *state = 31; *accept = 2; break;
        case 54: *state = 30; *accept = 2; break;
        case 53: *state = 29; *accept = 2; break;
        case 52: *state = 28; *accept = 2; break;
        case 51: *state = 27; *accept = 2; break;
        case 50: *state = 26; *accept = 2; break;
        case 49: *state = 25; *accept = 2; break;
        case 48: *state = 24; *accept = 2; break;
        default: return -1;
        } break;
    case 10:
        switch (c){
        case 57: *state = 12; *accept = 2; break;
        case 56: *state = 32; *accept = 2; break;
        case 55: *state = 31; *accept = 2; break;
        case 54: *state = 30; *accept = 2; break;
        case 53: *state = 29; *accept = 2; break;
        case 52: *state = 28; *accept = 2; break;
        case 51: *state = 27; *accept = 2; break;
        case 50: *state = 26; *accept = 2; break;
        case 49: *state = 25; *accept = 2; break;
        case 48: *state = 24; *accept = 2; break;
        default: return -1;
        } break;
    case 11:
        switch (c){
        case 57: *state = 12; *accept = 2; break;
        case 56: *state = 32; *accept = 2; break;
        case 55: *state = 31; *accept = 2; break;
        case 54: *state = 30; *accept = 2; break;
        case 53: *state = 29; *accept = 2; break;
        case 52: *state = 28; *accept = 2; break;
        case 51: *state = 27; *accept = 2; break;
        case 50: *state = 26; *accept = 2; break;
        case 49: *state = 25; *accept = 2; break;
        case 48: *state = 24; *accept = 2; break;
        default: return -1;
        } break;
    case 12:
        switch (c){
        case 57: *state = 12; *accept = 2; break;
        case 56: *state = 32; *accept = 2; break;
        case 55: *state = 31; *accept = 2; break;
        case 54: *state = 30; *accept = 2; break;
        case 53: *state = 29; *accept = 2; break;
        case 52: *state = 28; *accept = 2; break;
        case 51: *state = 27; *accept = 2; break;
        case 50: *state = 26; *accept = 2; break;
        case 49: *state = 25; *accept = 2; break;
        case 48: *state = 24; *accept = 2; break;
        default: return -1;
        } break;
    case 13:
        switch (c){
        default: return -1;
        } break;
    case 14:
        switch (c){
        case 102: *state = 23; *accept = 6; break;
        default: return -1;
        } break;
    case 15:
        switch (c){
        case 97: *state = 21; *accept = 0; break;
        default: return -1;
        } break;
    case 16:
        switch (c){
        case 104: *state = 17; *accept = 0; break;
        default: return -1;
        } break;
    case 17:
        switch (c){
        case 105: *state = 18; *accept = 0; break;
        default: return -1;
        } break;
    case 18:
        switch (c){
        case 108: *state = 19; *accept = 0; break;
        default: return -1;
        } break;
    case 19:
        switch (c){
        case 101: *state = 20; *accept = 5; break;
        default: return -1;
        } break;
    case 20:
        switch (c){
        default: return -1;
        } break;
    case 21:
        switch (c){
        case 114: *state = 22; *accept = 4; break;
        default: return -1;
        } break;
    case 22:
        switch (c){
        default: return -1;
        } break;
    case 23:
        switch (c){
        default: return -1;
        } break;
    case 24:
        switch (c){
        case 57: *state = 12; *accept = 2; break;
        case 56: *state = 32; *accept = 2; break;
        case 55: *state = 31; *accept = 2; break;
        case 54: *state = 30; *accept = 2; break;
        case 53: *state = 29; *accept = 2; break;
        case 52: *state = 28; *accept = 2; break;
        case 51: *state = 27; *accept = 2; break;
        case 50: *state = 26; *accept = 2; break;
        case 49: *state = 25; *accept = 2; break;
        case 48: *state = 24; *accept = 2; break;
        default: return -1;
        } break;
    case 25:
        switch (c){
        case 57: *state = 12; *accept = 2; break;
        case 56: *state = 32; *accept = 2; break;
        case 55: *state = 31; *accept = 2; break;
        case 54: *state = 30; *accept = 2; break;
        case 53: *state = 29; *accept = 2; break;
        case 52: *state = 28; *accept = 2; break;
        case 51: *state = 27; *accept = 2; break;
        case 50: *state = 26; *accept = 2; break;
        case 49: *state = 25; *accept = 2; break;
        case 48: *state = 24; *accept = 2; break;
        default: return -1;
        } break;
    case 26:
        switch (c){
        case 57: *state = 12; *accept = 2; break;
        case 56: *state = 32; *accept = 2; break;
        case 55: *state = 31; *accept = 2; break;
        case 54: *state = 30; *accept = 2; break;
        case 53: *state = 29; *accept = 2; break;
        case 52: *state = 28; *accept = 2; break;
        case 51: *state = 27; *accept = 2; break;
        case 50: *state = 26; *accept = 2; break;
        case 49: *state = 25; *accept = 2; break;
        case 48: *state = 24; *accept = 2; break;
        default: return -1;
        } break;
    case 27:
        switch (c){
        case 57: *state = 12; *accept = 2; break;
        case 56: *state = 32; *accept = 2; break;
        case 55: *state = 31; *accept = 2; break;
        case 54: *state = 30; *accept = 2; break;
        case 53: *state = 29; *accept = 2; break;
        case 52: *state = 28; *accept = 2; break;
        case 51: *state = 27; *accept = 2; break;
        case 50: *state = 26; *accept = 2; break;
        case 49: *state = 25; *accept = 2; break;
        case 48: *state = 24; *accept = 2; break;
        default: return -1;
        } break;
    case 28:
        switch (c){
        case 57: *state = 12; *accept = 2; break;
        case 56: *state = 32; *accept = 2; break;
        case 55: *state = 31; *accept = 2; break;
        case 54: *state = 30; *accept = 2; break;
        case 53: *state = 29; *accept = 2; break;
        case 52: *state = 28; *accept = 2; break;
        case 51: *state = 27; *accept = 2; break;
        case 50: *state = 26; *accept = 2; break;
        case 49: *state = 25; *accept = 2; break;
        case 48: *state = 24; *accept = 2; break;
        default: return -1;
        } break;
    case 29:
        switch (c){
        case 57: *state = 12; *accept = 2; break;
        case 56: *state = 32; *accept = 2; break;
        case 55: *state = 31; *accept = 2; break;
        case 54: *state = 30; *accept = 2; break;
        case 53: *state = 29; *accept = 2; break;
        case 52: *state = 28; *accept = 2; break;
        case 51: *state = 27; *accept = 2; break;
        case 50: *state = 26; *accept = 2; break;
        case 49: *state = 25; *accept = 2; break;
        case 48: *state = 24; *accept = 2; break;
        default: return -1;
        } break;
    case 30:
        switch (c){
        case 57: *state = 12; *accept = 2; break;
        case 56: *state = 32; *accept = 2; break;
        case 55: *state = 31; *accept = 2; break;
        case 54: *state = 30; *accept = 2; break;
        case 53: *state = 29; *accept = 2; break;
        case 52: *state = 28; *accept = 2; break;
        case 51: *state = 27; *accept = 2; break;
        case 50: *state = 26; *accept = 2; break;
        case 49: *state = 25; *accept = 2; break;
        case 48: *state = 24; *accept = 2; break;
        default: return -1;
        } break;
    case 31:
        switch (c){
        case 57: *state = 12; *accept = 2; break;
        case 56: *state = 32; *accept = 2; break;
        case 55: *state = 31; *accept = 2; break;
        case 54: *state = 30; *accept = 2; break;
        case 53: *state = 29; *accept = 2; break;
        case 52: *state = 28; *accept = 2; break;
        case 51: *state = 27; *accept = 2; break;
        case 50: *state = 26; *accept = 2; break;
        case 49: *state = 25; *accept = 2; break;
        case 48: *state = 24; *accept = 2; break;
        default: return -1;
        } break;
    case 32:
        switch (c){
        case 57: *state = 12; *accept = 2; break;
        case 56: *state = 32; *accept = 2; break;
        case 55: *state = 31; *accept = 2; break;
        case 54: *state = 30; *accept = 2; break;
        case 53: *state = 29; *accept = 2; break;
        case 52: *state = 28; *accept = 2; break;
        case 51: *state = 27; *accept = 2; break;
        case 50: *state = 26; *accept = 2; break;
        case 49: *state = 25; *accept = 2; break;
        case 48: *state = 24; *accept = 2; break;
        default: return -1;
        } break;
    default: return -2;
    }
    return 0;
}
