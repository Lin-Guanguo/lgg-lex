#include <stdio.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include "glex_gencode.h"


int main()
{
    FILE* f = fopen("test_rule_program.pl0", "r");
    glex l{f};
    int r;
    while( (r = l.next_match()) != -1){
        if(r == 1)
            continue;
        printf("%d %s\n", r, l.get_match().data());
    }
    printf("%d\n", r);
}