#include <stdio.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include "glex_gencode.h"


int main(int argc, const char** argv)
{
    if(argc <= 1)
    {
        printf("usage: pl0-lex [inputfile]");
        return 0;
    }
    FILE* f = fopen(argv[1], "r");
    glex l{f};
    int r;
    while( (r = l.next_match()) != -1){
        if(r == 1)
            continue;
        printf("%d %s\n", r, l.get_match().data());
    }
    printf("%d\n", r);
}