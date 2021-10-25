/**
 * @file glex_lib.h
 * @author Lin guanguo (lin.guanguo@foxmail.com)
 * @brief glex配套文件, 和生成代码一起使用，使用时只需要include本文件 
 * @version 0.1
 * @date 2021-10-24
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
 * @brief glex类
 * 
 */
class glex
{
    FILE* file;
    long fileoff = 0l;
    std::string match;
public:
    glex(FILE* file_) : file(file_)
    {

    };

    /**
     * @brief 获得上一次调用next_match()匹配的字符串
     * 
     * @return const std::string_view 
     */
    const std::string_view get_match()
    {
        return match;
    }

    /**
     * @brief 调用该函数获取下一个匹配, 至少匹配一个字符
     * 
     * @return int  -1: EOF; 
     *              -2: No Match Input, skip longest valid prefix
     */
    int next_match() 
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

};