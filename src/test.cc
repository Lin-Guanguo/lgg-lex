#include <stdio.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include "glex_lib.h"


int main()
{
    FILE* f = fopen("codetext.txt", "r");
    glex l{f};
    int r;
    while( (r = l.next_match()) != -1){
        printf("%d %s\n", r, l.get_match().data());
    }
    printf("%d\n", r);
}