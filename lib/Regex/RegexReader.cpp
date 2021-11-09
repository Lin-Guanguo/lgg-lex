#include "RegexReader.h"

namespace {

bool isBlank(char t){
    return t <= ' ';
}

} // namespace unname


RegexReader::RegexReader(std::istream& in)
{
    std::string buf;
    std::string rule;
    for(;;){
        buf.clear();
        std::getline(in, buf);
        auto i = buf.begin();
        // 跳过行首空白
        for(; i != buf.end() && isBlank(*i); ++i);
        // 读到空行停止
        if(i == buf.end())
            break;
        auto j = i;
        for(; !isBlank(*j); ++j);
        tokens.emplace_back(i, j);

        // 读到规则说明
        for(; *j != '"'; ++j);
        // 开始读规则
        rule.clear();
        for(++j; *j != '"'; ++j){
            if(*j == '\\'){
                ++j;
                switch(*j){
                case 'r': rule.push_back('\r'); break;
                case 'n': rule.push_back('\n'); break;
                case 't': rule.push_back('\t'); break;
                case '\\': rule.push_back('\\'); break;
                case ')': rule.append("\\)"); break;
                case '(': rule.append("\\("); break;
                case '|': rule.append("\\|"); break;
                case '*': rule.append("\\*"); break;
                default:
                    break;
                }
            }else{
                rule.push_back(*j);
            }
        }
        rules.push_back(std::move(rule));
    }
}

